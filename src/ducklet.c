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

typedef struct _get_request_t {
        char *key;
        char *val;
} getreq_t;

typedef void sigfunc(int);

void handlesignals(int sig);

int handle_request(int connfd, int listenfd);

int listenfd;

void cleanup_main();

ducklet_site_t *site;

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
        char buffer[len];
        time_t ticks;
        int c, port = -1;

        while ((c = getopt(argc, argv, "p:")) != -1) {
                switch (c) {
                case 'p':
                        port = atoi(optarg);
                        break;
                case '?':
                        fprintf(stderr, "unrecognized option '%c'\n", optopt);
                        exit(1);
                default:
                        abort();
                }
        }

        if (port == -1) {
                fprintf(stderr, "please provide a port number\n");
                exit(1);
        }

        site = get_site(argv[argc - 1]);

        listenfd = socket(AF_INET, SOCK_STREAM | O_NONBLOCK, 0);
        memset(&serv_addr, '0', sizeof(serv_addr));
        memset(buffer, '\0', len); 

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr.sin_port = htons(port);

        bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
        
        listen(listenfd, 10);

        while(1)
        {
                ticks = time(NULL);
                ticks--;
                int connfd = accept4(listenfd, (struct sockaddr*)NULL, NULL, SOCK_NONBLOCK);
                if (connfd != -1) {
                        printf(KWHT "Handling incoming connection...");

                        handle_request(connfd, listenfd);
                } else
                        usleep(50);
        }
        cleanup_main();
        return 0;
}

void cleanup_main()
{
        close(listenfd);
        int i;
        for (i = 0; i < site->num_resources; i++) {
                free(site->resources[i].resource_name);
                free(site->resources[i].template_file);
                free(site->resources[i].resource_file);
                free(site->resources[i].intermediate_file);
                free(site->resources[i].compilation_command);
                free(site->resources[i].data_type);
                free(site->resources[i].run_command);
        }
        free(site->resources);
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

int handle_request(int connfd, int listenfd)
{
        //clock_t response_start_time = clock();
        const size_t LEN = 4096;
        size_t len = LEN;
        size_t contents = 0;
        char *buffer = malloc(LEN * sizeof(char));
        char *bufferpos = buffer;
        char *item_requested = NULL;
        char *response_header = NULL;
        char command[512];
        http_request_t req;
        FILE *f = NULL;
        FILE *poutput = NULL;
        int i;
        int status = 0;
        ssize_t nread = 0;
        ducklet_resource_t *res = NULL;
        
        printf(KGRN "RESPONDING\n" KRST);

        nread = read(connfd, buffer, LEN - 1);
        if (nread == -1) {
                fprintf(stderr, "failure reading http request from socket\n");
                goto REQ_FAILURE;
        }
        contents += nread;

        while ((nread = read(connfd, bufferpos, LEN)) > 0) {
                contents += nread;
                len = len * 2;
                buffer = realloc(buffer, len);
                /* we don't want requests larger than 16 MB */
                if (contents > 0x100000)
                        goto REQ_FAILURE;
        }

        printf("Read HTTP request %lu bytes long\n", contents);

        buffer[contents] = '\0';

        req = get_http_request(buffer);
        
        shutdown(connfd, SHUT_RD); /* Might need to put shutdown a bit later in
                                      the code so I don't kill my buffer */

        item_requested = req.item + 1;

        for (i = 0; i < site->num_resources; i++) {
                if (strcmp(
                                item_requested,
                                site->resources[i].resource_name
                           ) == 0)
                        break;
        }
        if (i >= site->num_resources) {
                printf(KRED "ERROR" KRST ": "
                       "could not find requested resource\n");
                goto SHUTDOWN_HANDLER;
        } else {
                res = &(site->resources[i]);
                int freshness = get_is_fresh(res, site);
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
                                                site->root_dir,
                                                res->template_file,
                                                site->root_dir,
                                                res->intermediate_file,
                                                res->compilation_command,
                                                site->root_dir,
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
                sprintf(command, "export ducklet_post=\"%s\" && cd %s && %s", req.body, site->root_dir,
                                                res->run_command);
        }
        
        fflush(NULL);
TRY_AGAIN:
        f = popen(command, "r");

        if (f == NULL)
                printf(KRED "POPEN failed\n");

        response_header = build_http_response(&req, STATUS_OK);
        write(connfd, response_header, strlen(response_header));

        printf(KBLU);
        
        while ((nread = fread(buffer, sizeof(char), LEN, f)) != 0)
                write(connfd, buffer, nread);

        printf(KRST);

        printf("\n");

        status = pclose(f);

        if (status == -1) {
                printf(KRED "pclose failed\n" KRST);
        } else if (status > 0) {
                goto TRY_AGAIN;
                printf("pclose returned %d\n", status);
        }

        printf(KGRN "Done responding. No errors.\n" KRST);

SHUTDOWN_HANDLER:
        free_http_request(&req);
REQ_FAILURE:
        free(buffer);
        free(response_header);
        shutdown(connfd, SHUT_WR);
        close(connfd);

        /*printf("Response completed in %lf seconds.\n",
                (double)(clock() - response_start_time) /
                (double)CLOCKS_PER_SEC);*/
        //cleanup_main();
        return 0;
}
