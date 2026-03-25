CC=gcc
CFLAGS=I.
DEPS = logger.h
OBJ = logger.c validate.c

%.o : %.c $@ (DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

loggermake: $(OBJ)
	$(CC) -o $@ $^ $(CCFLAGS)
