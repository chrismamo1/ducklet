#define _GNU_SOURCE
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sched.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>

#include "httplib.h"
#include "libducklet.h"
#include "ducklettypes.h"

#define STACK_SIZE 10000

typedef struct _handler_thread_t {
        pid_t pid;
        char *stack;
} handler_thread_t;

typedef struct _get_request_t {
        char *key;
        char *val;
} getreq_t;

typedef void sigfunc(int);

void handlesignals(int sig);

int handle_request(void *arg);

int listenfd;

void cleanup_main();

ducklet_site_t **sites;

int main(int argc, char *argv[])
{
        if (argc < 2) {
                printf("Usage: ducklet [site root]\n");
                exit(1);
        }

        signal(SIGINT, &handlesignals);
        listenfd = 0;
        struct sockaddr_in serv_addr; 
        const size_t len = 1024;
        size_t num_sites = argc - 1;
        sites = malloc(num_sites * sizeof(ducklet_site_t*));
        char buffer[len];
        time_t ticks;
        int nconns = 0;
        handler_thread_t conns[64];
        int i, j, k;

        for (i = 0; i < argc - 1; i++) {
                sites[i] = get_site(argv[i + 1]);
        }

        listenfd = socket(AF_INET, SOCK_STREAM | O_NONBLOCK, 0);
        memset(&serv_addr, '0', sizeof(serv_addr));
        memset(buffer, '\0', len); 

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr.sin_port = htons(5000);

        bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
        
        listen(listenfd, 10);

        while(1)
        {
                pid_t pid;
                int status;
                ticks = time(NULL);
                ticks--;
                int connfd = accept4(listenfd, (struct sockaddr*)NULL, NULL, SOCK_NONBLOCK);
                if (connfd != -1) {
                        printf(KWHT "Incoming connection, creating thread...");
                        connection_t *conn = malloc(sizeof(connection_t));
                        conn->connfd = connfd;
                        conn->listenfd = listenfd;
                        conn->site = sites[0];

                        char *child_stack = malloc(STACK_SIZE);
                        char *stack_top = child_stack + STACK_SIZE;
                        pid = clone(handle_request, stack_top, 0
                                    , (void*)conn);
                        if (pid != -1) {
                                handler_thread_t thr;
                                thr.pid = pid;
                                thr.stack = child_stack;
                                conns[nconns] = thr;
                                nconns++;
                        } else
                                printf(KYEL "WARNING " KRST "Failure creating handler\n");
                } else
                        usleep(50);

                for (i = 0; i < nconns; i++) {
                        if ((pid = waitpid(-1, &status, WNOHANG | __WALL | __WCLONE)) > 0) {
                                printf(KYEL);
                                if (WIFEXITED(status)) {
                                        //printf("WIFEXITED\n");
                                        //printf("\tEXIT STATUS %d\n", WEXITSTATUS(status));
                                } if (WIFSIGNALED(status)) {
                                        if (WCOREDUMP(status)) {
                                                printf("WIFSIGNALED\n");
                                                printf("\tTERMINATION SIGNAL %d\n", WTERMSIG(status));
                                                printf("\tWCOREDUMP\n");
                                        }
                                }
                                if (WIFSTOPPED(status)) {
                                        //printf("WIFSTOPPED\n");
                                        //printf("\tSTOP SIGNAL %d\n", WSTOPSIG(status));
                                } if (WIFCONTINUED(status)) {
                                        //printf("WIFCONTINUED\n");
                                        printf(KRST);
                                        continue;
                                }
                                printf(KRST);
                                for (j = 0; conns[j].pid != pid; j++)
                                        if (j >= nconns) {
                                                printf(KRED "This should never happen.\n" KRST);
                                                exit(1);
                                        }
                                free(conns[j].stack);
                                for (k = j; k < nconns - 1; k++)
                                        conns[k] = conns[k + 1];
                                nconns--;
                        } else if (pid < 0) { // error
                                printf(KRED);
                                switch (errno) {
                                case ECHILD:
                                        printf("ECHILD\n");
                                        break;
                                case EINTR:
                                        printf("EINTR\n");
                                        break;
                                case EINVAL:
                                        printf("EINVAL\n");
                                        break;
                                default:
                                        printf("Unable to handle this error.\n");
                                        break;
                                }
                                printf(KRST);
                        } else
                                ; // no threads were finished

                }
        }
        cleanup_main();
        return 0;
}

void cleanup_main()
{
        close(listenfd);
        int i, j;
        for (j = 0; j < 1; j++) {
                for (i = 0; i < sites[j]->num_resources; i++) {
                        free(sites[j]->resources[i].resource_name);
                        free(sites[j]->resources[i].template_file);
                        free(sites[j]->resources[i].resource_file);
                        free(sites[j]->resources[i].intermediate_file);
                        free(sites[j]->resources[i].compilation_command);
                }
                free(sites[j]->resources);
        }
}

void handlesignals(int sig)
{
        if (sig == SIGINT) {
                printf("Waiting for child processes to close...\n");
                waitpid(-1, NULL, __WALL | __WCLONE);
                printf("Closing all open files...\n");
                cleanup_main();
                close(listenfd);
                printf("Done.\nGoodbye.\n");
                exit(0);
        }
        return;
}

int handle_request(void *arg)
{
        //clock_t response_start_time = clock();
        const size_t LEN = 4096;
        char *buffer = malloc(LEN * sizeof(char));;
        char *item_requested = NULL;
        char *response_header = NULL;
        char command[512];
        connection_t conn = *((connection_t*)arg);
        http_request_t req;
        FILE *f = NULL;
        FILE *poutput = NULL;
        int i;
        int status = 0;
        size_t nread = 0;
        ducklet_resource_t *res = NULL;
        
        printf(KGRN "RESPONDING\n" KRST);

        nread = read(conn.connfd, buffer, LEN - 1);

        req = get_http_request(buffer);
        
        shutdown(conn.connfd, SHUT_RD); /* Need to put shutdown a bit later in
                                           the code so I don't kill my buffer */

        item_requested = req.item + 1;

        for (i = 0; i < conn.site->num_resources; i++) {
                if (strcmp(
                                item_requested,
                                conn.site->resources[i].resource_name
                           ) == 0)
                        break;
        }
        if (i >= conn.site->num_resources) {
                printf(KRED "ERROR" KRST ": "
                       "could not find requested resource\n");
                goto SHUTDOWN_HANDLER;
        } else {
                res = &(conn.site->resources[i]);
                int freshness = get_is_fresh(res, conn.site);
                if (freshness == 1) {
                } else if (freshness == -1) {
                        printf(KRED "ERROR" KRST ": "
                               "freshness validation failed and I'm too lazy to"
                               " write a 404/internal error handler at the"
                               " moment\n");
                        goto SHUTDOWN_HANDLER;
                } else if (freshness == 0) {
                        sprintf(command,"cd %s && duckletc %s > %s/%s && %s"
                                        " && rm %s/%s",
                                                conn.site->root_dir,
                                                res->template_file,
                                                conn.site->root_dir,
                                                res->intermediate_file,
                                                res->compilation_command,
                                                conn.site->root_dir,
                                                res->intermediate_file);
                        poutput = popen(command, "r");
                        if (!poutput) {
                                printf(KRED "ERROR" KRST ":"
                                        " failed to regenerate intermediate"
                                        " file\n");
                                goto SHUTDOWN_HANDLER;
                        }
                        pclose(poutput);
                }
                printf("POST message body: " KBLU "\"%s\"\n" KRST,
                                req.body);
                sprintf(command, "export ducklet_post=\"%s\" && cd %s && %s", req.body, conn.site->root_dir,
                                                res->run_command);
        }
        
        fflush(NULL);
TRY_AGAIN:
        f = popen(command, "r");

        if (f == NULL)
                printf(KRED "POPEN failed\n");

        response_header = build_http_response(&req, STATUS_OK);
        write(conn.connfd, response_header, strlen(response_header));

        printf(KBLU);
        
        while ((nread = fread(buffer, sizeof(char), LEN, f)) != 0)
                write(conn.connfd, buffer, nread);

        printf(KRST);

        printf("\n");

        status = pclose(f);

        if (status == -1) {
                printf(KRED "pclose failed\n" KRST);
        } else if (status > 0) {
                goto TRY_AGAIN;
                printf("pclose returned %d\n", status);
        }

SHUTDOWN_HANDLER:
        shutdown(conn.connfd, SHUT_WR);
        close(conn.connfd);
        free(arg);

        printf(KGRN "Done responding. No errors.\n" KRST);

        /*printf("Response completed in %lf seconds.\n",
                (double)(clock() - response_start_time) /
                (double)CLOCKS_PER_SEC);*/
        //cleanup_main();
        return 0;
}
