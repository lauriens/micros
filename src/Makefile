TARGET=pid teste1
SRCS=$(TARGET).c

FLAGS=-Wall -g -MMD
INCLUDE=-I. -I../include
LIBDIR=-L../lib -L../libQuanser
LIBS=-lgalileo2 -lv1

CC=$(CROSS_COMPILE)gcc
CFLAGS=$(FLAGS) $(INCLUDE)
LDFLAGS=$(LIBDIR) $(LIBS)

all: $(TARGET)

$(TARGET): $(SRCS:.c=.o) ../lib/libgalileo2.a ../lib/libv1.a
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(SRCS:.c=.d)

clean:
	rm -f *~ *.bak *.o *.d

distclean: clean
	rm -f $(TARGET)
