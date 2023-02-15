# Flags for the compiler
CFLAGS =  -Wall -Werror -pedantic
CFLAGS += -Wstrict-prototypes -Wmissing-prototypes
CFLAGS += -Wmissing-declarations
CFLAGS += -Wshadow -Wpointer-arith -Wcast-qual
LDFLAGS = -levent

PROGRAMS = example01

# Rule to compile all programs
all: $(PROGRAMS)

# Rules to compile each individual program
example01: example01.c
	$(CC) $(CFLAGS) example01.c -o example01 $(LDFLAGS)

# Rule to clean up object files and executables
clean:
	rm -f $(PROGRAMS)
