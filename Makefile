
CC ?= gcc
AR ?= ar

CFLAGS ?= -O3 -std=gnu11
LDFLAGS ?= -L. -lhptl

OBJS := hptl.o
LIBRARY := hptl.a

all: $(OBJS) $(LIBRARY)

.PHONY: all clean

%.o: %.c
	$(CC) $< -o$@ -c $(CFLAGS)

$(TARGET): library $(OBJS)
	$(CC) -o$(TARGET) $(OBJS) $(LDFLAGS) $(CFLAGS)

$(LIBRARY): $(OBJS)
	$(AR) rcs libhptl.a $(OBJS)

clean:
	rm -r $(OBJS)
	rm -r $(LIBRARY)
