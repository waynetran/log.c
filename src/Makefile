CC = gcc
CFLAGS = -g -c -Wall -std=c99 -D_BSD_SOURCE
LDFLAGS= -lm
OBJS = log.o
TESTOBJS = main.o
OUT = liblog.c.a

RM = rm -f
MKDIR = mkdir -p

all: $(OUT) test

$(OUT): $(OBJS)
	ar rcs $@ $(OBJS)
	cp $(OUT) ../lib

test: $(OUT) $(TESTOBJS)
	$(CC) -o $@ $(TESTOBJS) $(OUT) $(LDFLAGS)
	mv test ../test

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $<

$(TESTOBJS): %.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	$(RM) $(OBJS) $(TESTOBJS) *~ "#*" test

distclean: clean
	$(RM) $(OUT)

.PHONY: all clean
