#ifndef _LIBDUCKLET_H
#define _LIBDUCKLET_H

#include "httplib.h"
#include "ducklettypes.h"

struct _ducklet_resource_t {
        char *template_file;
        char *resource_file;
        char *intermediate_file;
        char *compilation_command;
        char *data_type;
        char *run_command;
        char *resource_name;
        int is_executable;
} ;

struct _ducklet_site_t {
        char *root_dir;
        ducklet_resource_t *resources;
        size_t num_resources;
} ;

int get_is_fresh(ducklet_resource_t *res, ducklet_site_t *site);

ducklet_site_t* get_site(char *root);

ducklet_site_t* init_site(char *root);

#endif
