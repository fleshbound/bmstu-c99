CFLAGS := -std=c99 -Wall -Werror -pedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla
OBJS := movies.o mov_proc.o argch.o # объектные файлы
CC := gcc # компилятор
SRCS := $(wildcard *.c) # все c-файлы

debug: CFLAGS += -g3 -O0
debug: app.exe unit_tests.exe

release: CFLAGS += -g0 -O3 -DNDEBUG
release: app.exe #unit_tests.exe

func: 
	./func_tests/scripts/func_tests.sh

unit: 
	./unit_tests.exe

app.exe: $(OBJS) main.o
	$(CC) $^ -o $@

unit_tests.exe: $(OBJS) test.o
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.d: %.c
	$(CC) -M $< > $@

clean:
	$(RM) *.o *.exe *.d

include $(SRCS:.c=.d)

.PHONY: clean debug release unit func

