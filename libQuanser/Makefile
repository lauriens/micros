TARGET=libv1.a
SRCS=libv1.c

FLAGS=-O2 -Wall -MMD
INCLUDE=-I. -I../include
LIBDIR=
LIBS=

CC=$(CROSS_COMPILE)gcc
CCAR=$(CROSS_COMPILE)ar
CFLAGS=$(FLAGS) $(INCLUDE)
LDFLAGS=$(LIBDIR) $(LIBS)
CCARFLAGS=-crvs

all: $(TARGET)

$(TARGET): $(SRCS:.c=.o)
	$(CCAR) $(CCARFLAGS) $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(SRCS:.c=.d)

clean:
	rm -f *~ *.bak *.o *.d

distclean: clean
	rm -f $(TARGET) 
