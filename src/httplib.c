/**
 * @file libhttp.c
 * @author John Christopher McAlpine
 * @date 2015-04-06
 * @brief 
 * @detail
 * @todo
 */

#include "httplib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>

#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define KRST  "\033[0m"

char* get_parameter(char *head, char *param)
{
        char *tmp = NULL;
        ptrdiff_t dist = 0;
        size_t LEN = 64;
        char *rval = NULL;
        char *delim = CRLF;

        if (strstr(head, CRLF) == NULL)
                delim = "\n";

        tmp = strstr(head, param);
        if (tmp == NULL) {
                //printf(KRED "ERROR " KRST "failed to find %s.\n", param);
                return NULL;
        }
        tmp = tmp + strlen(param) + 2; // + 2 because ": " won't be included in
                                       // the parameter name
        //if (strchr(tmp, '\n') < strstr(tmp, CRLF) || strstr(tmp, CRLF) == NULL)
        //        dist = strchr(tmp, '\n') - tmp;
        //else
                dist = strstr(tmp, delim) - tmp;
        if (dist > (strlen(tmp) + 1) * sizeof(char)) {
                dist = strstr(tmp, "\0") - tmp;
                free(rval);
                rval = malloc((strlen(tmp) + 1) * sizeof(char));
                strncpy(rval, tmp, strlen(tmp) + 1);
                return rval;
        }
        /*if (rval == NULL) {
                printf(KRED "ERROR" KRST " malloc failed (size = %u) ",
                                (uint)((dist + 1) * sizeof(char)));
                if (errno == ENOMEM)
                        printf("(ENOMEM)");
                printf(".\n");
                return NULL;
        }*/
        char *r = strndup(tmp, dist + 1);
        r[dist] = '\0';
        return r;
}

http_request_t get_http_request(char *req)
{

        http_request_t rval;
        rval.header = req;
        rval.body = strstr(req, "\r\n\r\n") + 4;
        *(rval.body - 4) = '\0';

        rval.user_agent = get_parameter(rval.header, "User-Agent");
        rval.content_type = get_parameter(rval.header, "Content-Type");
        rval.host = get_parameter(rval.header, "Host");

        { /// I can't believe I'm actually using this...
                char *tmp = get_parameter(rval.header, "Content-Length");
                char *tmp2 = NULL;
                ptrdiff_t dist = 0;

                if (tmp == NULL)
                        rval.content_length = 0;
                else
                        rval.content_length = (size_t)atol(tmp);
                free(tmp);

                dist = strstr(req, CRLF) - req;
                tmp = malloc((dist + 1) * sizeof(char));
                strncpy(tmp, req, dist);
                tmp2 = strtok(tmp, " \r\n");
                if (strcmp(tmp2, "GET") == 0)
                        rval.rtype = GET;
                else if (strcmp(tmp2, "POST") == 0)
                        rval.rtype = POST;

                tmp2 = strtok(NULL, " \r\n");
                rval.item = malloc((strlen(tmp2) + 1) * sizeof(char));
                strcpy(rval.item, tmp2);

                free(tmp);
        }
        return rval;
}

void free_http_request(http_request_t *req)
{
        /* [header] and [body] should both be references to a string allocated
         * elsewhere in the program
         */
        free(req->user_agent);
        free(req->item);
        free(req->host);
        free(req->content_type);
        return;
}

char* build_http_response(http_request_t *req, http_status_e status)
{
        char *rval = malloc(1024 * sizeof(char));
        char *http_version = "HTTP/1.1";
        char *stat = NULL;

        rval[0] = '\0';

        switch (status) {
        case STATUS_OK:
                stat = "200 OK";
                break;
        case STATUS_BAD_REQUEST:
                stat = "400";
                break;
        case STATUS_FORBIDDEN:
                stat = "403";
                break;
        default:
                stat = "200 OK";
        }
        
        sprintf(rval, "%s %s" CRLF
                      "Server: Ducklet" CRLF
                      "Content-Type: %s" CRLF CRLF,
                      http_version, stat, req->content_type);
        return realloc(rval, (strlen(rval) + 1) * sizeof(char));
}

void print_http_request(http_request_t req)
{
        printf("HTTP Request:\n");
        printf(KRST "\tUser-Agent: " KRED "%s\n"
               KRST "\tContent-Length: " KRED "%u\n"
               KRST "\tresource requested: " KRED "%s\n"
               KRST "\trequest type: " KRED "%s\n"
               KRST "\tContent-Type: " KRED "%s\n"
               KRST "\tHost: " KRED "%s\n" KRST,
               req.user_agent,
               (uint) req.content_length,
               req.item,
               req.rtype == GET ? "GET" : "POST",
               req.content_type,
               req.host);
        return;
}
