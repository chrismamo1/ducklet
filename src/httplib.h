#ifndef _LIBHTTP_H
#define _LIBHTTP_H

#include <stdio.h>

#include "libducklet.h"
#include "ducklettypes.h"

#define CRLF "\r\n"

typedef enum {GET, POST, HEAD} http_request_type;
typedef enum {
        STATUS_OK = 200,
        STATUS_BAD_REQUEST = 400,
        STATUS_FORBIDDEN = 403,
} http_status_e;

struct _http_request_t {
        char *header;
        char *body;
        http_request_type rtype;
        char *user_agent;
        char *item; ///< The file requested
        size_t content_length;
        char *host;
        char *content_type;
} ;

struct _connection_t {
        int connfd;
        int listenfd;
        ducklet_site_t *site;
} ;

char *get_parameter(char *head, char *param);

http_request_t get_http_request(char *req);

char *build_http_response(http_request_t *req, http_status_e status);

void print_http_request(http_request_t req);

#endif
