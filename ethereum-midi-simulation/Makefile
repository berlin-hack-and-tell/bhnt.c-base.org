INCLUDE = ./include/
LIBS = ./lib/
LIBDIR = ./lib/
BINDIR = ./bin/
SRCDIR = ./src/
BUILDDIR = ./build/

all: shared midi

shared:
	$(CC) -Wall -I$(INCLUDE) -o $(BUILDDIR)lash_debug_log_lib.o -fPIC -c $(SRCDIR)lib/lash_debug_log.c
	$(CC) -shared -Wl,-soname,liblashdebug.so.0 -o $(LIBDIR)liblashdebug.so $(BUILDDIR)lash_debug_log_lib.o
	
midi:
	$(CC) -Wall -g -I$(INCLUDE) -gdwarf-2 -g3 -c $(SRCDIR)instruction.c -o $(BUILDDIR)instruction.o
	$(CC) -Wall -g -I$(INCLUDE) -gdwarf-2 -g3 -c $(SRCDIR)http.c -o $(BUILDDIR)http.o
	$(CC) -Wall -g -I$(INCLUDE) -gdwarf-2 -g3 -c $(SRCDIR)midi.c -o $(BUILDDIR)midi.o
	$(CC) -Wall -g -I$(INCLUDE) -gdwarf-2 -g3 -c $(SRCDIR)main.c -o $(BUILDDIR)main.o
	$(CC) -Wall -g -o -I$(INCLUDE) -L$(LIBS) -o $(BINDIR)midinetworksim $(BUILDDIR)main.o $(BUILDDIR)midi.o $(BUILDDIR)instruction.o $(BUILDDIR)http.o -lasound -llashdebug

clean:
	rm $(BUILDDIR)* -rf
	rm $(BINDIR)* -rf
	rm $(LIBDIR)* -rf
