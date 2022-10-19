DEBUGDIR = Debug/
RELEASEDIR = Release/


ifeq ($(MODE), DEBUG)
	DEBUGFLAGS = -Wall -Wextra -g #-fsanitize=address
	EXECDIR = $(DEBUGDIR)
else
	RELEASEFLAGS = -D NDEBUG
	EXECDIR = $(RELEASEDIR)
endif

ifndef PACKAGEMANAGER
	PACKAGEMANAGER = apt
endif


SRCDEPENDENCIES =
PKGDEPENDENCIES = build-essential valgrind

CC = g++ -std=c++11
CFLAGS = -c $(DEBUGFLAGS) $(RELEASEFLAGS)
LDFLAGS = $(DEBUGFLAGS)
BUILDDIR = $(EXECDIR)
SRCDIR =

EXECNAME = stack


#----------------------------------BUILDING--------------------------------------------------
all: mkdir main
	$(CC) $(LDFLAGS) $(BUILDDIR)main.o $(BUILDDIR)libstack.o $(BUILDDIR)libstack_config.o -o $(EXECDIR)$(EXECNAME)
	
mkdir:
	mkdir -p $(BUILDDIR) $(EXECDIR)
	
main: libstack libstack_config
	$(CC) $(CFLAGS) $(SRCDIR)main.cpp -o $(BUILDDIR)main.o


#----------------------------------libstack---------------------------------------------------
libstack:
	$(CC) $(CFLAGS) $(SRCDIR)stack.cpp -o $(BUILDDIR)libstack.o


#----------------------------------libstack_config--------------------------------------------
libstack_config:
	$(CC) $(CFLAGS) $(SRCDIR)config.cpp -o $(BUILDDIR)libstack_config.o


#----------------------------------INSTALLING DEPENDENCIES------------------------------------
install-dependencies-src:
	cd .. && git clone $(SRCDEPENDENCIES)

install-dependencies-pkg:
	sudo $(PACKAGEMANAGER) install $(PKGDEPENDENCIES)

install-dependencies-all: install-dependencies-src install-dependencies-pkg


#----------------------------------RUNNING----------------------------------------------------
run:
	./$(EXECDIR)$(EXECNAME)

rund:
	valgrind --leak-check=full ./$(EXECDIR)$(EXECNAME)


#-----------------------------------CLEANING--------------------------------------------------
clean:
	rm -rf $(RELEASEDIR) $(DEBUGDIR) $(BUILDDIR)
