# Definitions de macros

CC     = g++
CXXFLAGS = -Wall -std=c++11
CFILES = helloworld.c
OFILES = $(CFILES:.cc=.o)

# Definition de la premiere regle

prog: $(OFILES)
	$(CC) $(OFILES) -o HelloWorld

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.c~ *.h~ HelloWorld
