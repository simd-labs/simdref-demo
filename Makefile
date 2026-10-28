CC ?= cc
CFLAGS ?= -O2 -Wall -Wextra
override CFLAGS += -mavx2 -mfma -mpopcnt

demo: main.o intrinsics.o inline_asm.o sum.o
	$(CC) -o $@ $^

%.o: %.s
	$(CC) -c -o $@ $<

check: demo
	./demo

clean:
	rm -f demo *.o

.PHONY: check clean
