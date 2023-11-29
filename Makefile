SRCS_STATIC = static_main.c
SRCS_DYNAMIC = dynamic_main.c
LIBSRCS = open.c close.c set.c get.c do_snapshot.c do_recovery.c

TARG_STATIC = kvs_static
TARG_DYNAMIC = kvs_dynamic

CC = gcc
OPTS = -Wall -g
LIBS_STATIC = -L. -lkvs
LIBS_DYNAMIC = -L. -lkvs -ldl

OBJS_STATIC = $(SRCS_STATIC:.c=.o)
OBJS_DYNAMIC = $(SRCS_DYNAMIC:.c=.o)
LOBJS = $(LIBSRCS:.c=.o)
LARS_STATIC = libkvs.a
LARS_DYNAMIC = libkvs.so

all: static dynamic

static: $(TARG_STATIC)

dynamic: $(TARG_DYNAMIC)

$(TARG_STATIC) : $(OBJS_STATIC) $(LARS_STATIC)
	$(CC) -o $(TARG_STATIC) $(OBJS_STATIC) $(LIBS_STATIC) 

$(TARG_DYNAMIC) : $(OBJS_DYNAMIC) $(LARS_DYNAMIC)
	$(CC) -o $(TARG_DYNAMIC) $(OBJS_DYNAMIC) $(LIBS_DYNAMIC) 

$(LARS_STATIC) : $(LOBJS)
	ar rs $(LARS_STATIC) $(LOBJS)

$(LARS_DYNAMIC) : $(LOBJS)
	$(CC) -shared -fPIC -o $(LARS_DYNAMIC) $(LIBSRCS)

%.o: %.c
	$(CC) $(OPTS) -c $< -o $@

clean:
	rm -f $(OBJS_STATIC) $(OBJS_DYNAMIC) $(LOBJS) $(LARS_STATIC) $(LARS_DYNAMIC) $(TARG_STATIC) $(TARG_DYNAMIC)
