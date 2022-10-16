CFLAGS := -std=c99 -Wall -Werror -pedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -Wno-error=unused-function
TST_FLAGS := -lcheck -lm -lpthread -lsubunit -lrt
OBJS := process.o argch.o # объектные файлы
CC := gcc # компилятор
SRCS := $(wildcard *.c) # все c-файлы

debug: CFLAGS += -g3 -O0
debug: app.exe

release: CFLAGS += -g0 -O3 -DNDEBUG
release: app.exe

func: 
	./func_tests/scripts/func_tests.sh -USE_VALGRIND

unit: unit_tests.exe
	valgrind --tool=memcheck --log-file=tmp1.txt ./unit_tests.exe

app.exe: $(OBJS) main.o
	$(CC) $^ -o $@

unit_tests.exe: $(OBJS) test.o
	$(CC) $^ $(TST_FLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.d: %.c
	$(CC) -M $< > $@

clean:
	$(RM) *.o *.exe *.d *.txt

include $(SRCS:.c=.d)

.PHONY: clean debug release unit func

