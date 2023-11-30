SRCS_BASELINE = baseline_main.c
SRCS_CUSTOM = custom_main.c

LIBSRCS_BASELINE = baseline_open.c baseline_snapshot.c baseline_recovery.c close.c set.c
LIBSRCS_CUSTOM= custom_open.c custom_snapshot.c custom_recovery.c close.c set.c  

TARG_BASELINE = kvs_baseline
TARG_CUSTOM = kvs_custom

CC = gcc
OPTS = -Wall -g
LIBS_BASELINE= -L. -lkvsb
LIBS_CUSTOM = -L. -lkvsc


OBJS_BASELINE = $(SRCS_BASELINE:.c=.o)
OBJS_CUSTOM = $(SRCS_CUSTOM:.c=.o)

LOBJS_BASELINE = $(LIBSRCS_BASELINE:.c=.o)
LOBJS_CUSTOM = $(LIBSRCS_CUSTOM:.c=.o)

LARS_BASELINE = libkvsb.a
LARS_CUSTOM = libkvsc.a

all: baseline custom

baseline: $(TARG_BASELINE)

custom: $(TARG_CUSTOM)

$(TARG_BASELINE) : $(OBJS_BASELINE) $(LARS_BASELINE)
	$(CC) -o $(TARG_BASELINE) $(OBJS_BASELINE) $(LIBS_BASELINE) 

$(TARG_CUSTOM) : $(OBJS_CUSTOM) $(LARS_CUSTOM)
	$(CC) -o $(TARG_CUSTOM) $(OBJS_CUSTOM) $(LIBS_CUSTOM) 

$(LARS_BASELINE) : $(LOBJS_BASELINE)
	ar rs $(LARS_BASELINE) $(LOBJS_BASELINE)

$(LARS_CUSTOM) : $(LOBJS_CUSTOM)
	ar rs $(LARS_CUSTOM) $(LOBJS_CUSTOM)
	
%.o: %.c
	$(CC) $(OPTS) -c $< -o $@

clean_custom:
	rm -f $(OBJS_CUSTOM) $(LOBJS_CUSTOM) $(LARS_CUSTOM) $(TARG_CUSTOM)

clean_baseline:
	rm -f $(OBJS_BASELINE) $(LOBJS_BASELINE) $(LARS_BASELINE) $(TARG_BASELINE)

clean: clean_custom clean_baseline

