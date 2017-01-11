/**
 * @file libducklet.c
 * @author John Christopher McAlpine
 * @date 2015-04-08
 * @brief 
 * @detail
 * @todo
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <assert.h>

#include "libducklet.h"

#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define KRST  "\033[0m"

int get_is_fresh(ducklet_resource_t *res, ducklet_site_t *site)
{
        struct stat attr;
        int status;
        time_t temp_mt, res_mt;
        char url[128];
        sprintf(url, "%s/%s", site->root_dir, res->template_file);
        status = stat(url, &attr);
        if (status == -1) {
                if (errno == ENOENT) {
                        printf(KRED "ERROR" KRST ": "
                               "no template file found\n");
                        return -1;
                } else if (errno == EACCES) {
                        printf(KRED "ERROR" KRST ": "
                               "permission denied for template file\n");
                        return -1;
                }
        }
        temp_mt = attr.st_mtime;
        sprintf(url, "%s/%s", site->root_dir, res->resource_file);
        status = stat(url, &attr);
        if (status == -1) {
                if (errno == ENOENT) {
                        printf(KYEL "WARNING" KYEL ": "
                               "no resource file found\n");
                        return 0;
                } else if (errno == EACCES) {
                        printf(KRED "ERROR" KRST ": "
                               "permission denied for resource file\n");
                        return -1;
                }
        }
        res_mt = attr.st_mtime;
        if (res_mt >= temp_mt)
                return 1;
        else
                return 0;
}

ducklet_site_t* get_site(char *root)
{
        size_t rootlen = strlen(root);
        size_t LEN = 16384;
        ducklet_site_t *rval = malloc(sizeof(ducklet_site_t));
        char *buffer = NULL;
        char linebuf[64];
        char *resource_flag = NULL;
        if (root[strlen(root) - 1] == '/') {
                root[strlen(root) - 1] = '\0';
                --rootlen;
        }
        { /* perkele */
                DIR *rootdir = opendir(root);
                if (rootdir)
                        closedir(rootdir);
                else if (errno == ENOENT)
                        exit(1);
                else
                        exit(1);
        }
        char *conf_file = NULL;
        FILE *conf = NULL;
        conf_file = malloc((strlen(root) + 16 + 1) * sizeof(char));
        conf_file = strncpy(conf_file, root, rootlen);
        assert(conf_file);
        strncat(conf_file, "/ducklet.conf", 16);
        conf = fopen(conf_file, "r");
        if (!conf) {
                if (errno == ENOENT)
                        return NULL;
                        //return init_site(root);
                else
                        exit(1);
        }
        buffer = malloc(LEN * sizeof(char));
        resource_flag = buffer;
        buffer[0] = buffer[1] = '\0';
        while (fgets(linebuf, 64, conf) != NULL)
                strncat(buffer, linebuf, 64);
        rval->root_dir = get_parameter(buffer, "Document-Root");
        //char *tmp = strdup(rval->root_dir);

        printf("read docroot from config file \"%s\"\n", rval->root_dir);
        rval->resources = NULL;
        rval->num_resources = 0;
        char *startloc = NULL;
        char *stoploc = NULL;
        char *desc = NULL;
        while ((resource_flag = strstr(resource_flag, "__resource__")) != NULL) {
                resource_flag++;
                startloc = strstr(resource_flag, "{{") + 2;
                stoploc  = strstr(startloc, "}}");
                while (*startloc == ' ' || *startloc == '\n' || *startloc == '\r')
                        startloc++;
                desc = strndup(startloc, stoploc - startloc + 1);
                assert(desc);
                ducklet_resource_t res;
                res.resource_name = malloc(256 * sizeof(char));
                sscanf(strchr(resource_flag, '"') + 1, "%[^\"]", res.resource_name);
                //printf("Name: " KBLU "%s\n" KRST, res.resource_name);
                rval->resources = realloc(rval->resources,
                                            (++(rval->num_resources))  *
                                            sizeof(ducklet_resource_t));
                res.template_file = get_parameter(desc, "Template-File");
                res.resource_file = get_parameter(desc, "Resource-File");
                res.intermediate_file = get_parameter(desc, "Intermediate-File");
                res.compilation_command = get_parameter(desc, "Compilation-Command");
                res.data_type = get_parameter(desc, "Data-Type");
                res.run_command = get_parameter(desc, "Run-Command");
                char *tmp = get_parameter(desc, "Is-Executable");
                res.is_executable = atoi(tmp);

                rval->resources[rval->num_resources - 1] = res;

                free(tmp);
                free(desc);
        }
        free(buffer);
        free(conf_file);
        fclose(conf);
        return rval;
}

/*static char* scan_directory(DIR *d)
{
        struct dirent *ent;
        size_t LEN = 64;
        char *rval = malloc(LEN * sizeof(char));
        memset(rval, '\0', LEN * sizeof(char));
        while((ent = readdir(d)) != NULL) {
                if (strlen(ent->d_name) + strlen(rval) + 1 > LEN)
                        realloc(rval, (LEN = LEN * 2) * sizeof(char));
                if (ent->d_type == DT_DIR) {
                        strcat(rval, "Directory: ");
                        strcat(rval, ent->d_name);
                        strcat(rval, "\n");
                } else {
                        strcat(rval, "Resource: ");
                        strcat(rval, ent->d_name);
                        strcat(rval, "\n");
                }
        }
}*/

/*ducklet_site_t* init_site(char *root)
{
        size_t rootlen = strlen(root);
        FILE *conf = NULL;
        char *conf_file;
        DIR *rootdir = NULL;
        if (root[strlen(root) - 1] == '/') {
                root[strlen(root) - 1] = '\0';
                --rootlen;
        }
        rootdir = opendir(root);
        if (errno == ENOENT)
                mkdir(root, S_IRWXU);
        else if (rootdir == NULL)
                exit(1);
        conf_file = malloc((strlen(root) + 16) * sizeof(char));
        strncpy(conf_file, root, rootlen);
        strncat(conf_file, "/ducklet.conf", 16);
        conf = fopen(conf_file, "w");
        
        fprintf(conf, "Root-Directory: %s\r\n", root);
        
        closedir(rootdir);
}*/
