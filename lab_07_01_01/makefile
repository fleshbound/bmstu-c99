CFLAGS := -std=c99 -Wall -Werror -pedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -Wno-error=unused-function -I./inc/
TST_FLAGS := -lcheck -lm -lpthread -lsubunit -lrt
CC := gcc # компилятор

OUT_DIR := ./out
SRC_DIR := ./src
UNIT_DIR := ./unit_tests

TEST_OBJS := $(patsubst $(UNIT_DIR)/%.c,$(OUT_DIR)/%.o,$(wildcard $(UNIT_DIR)/*.c))
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OUT_DIR)/%.o,$(wildcard $(SRC_DIR)/*.c))
OBJS := $(filter-out $(OUT_DIR)/main.o,$(OBJS))

RM_FILES := $(OUT_DIR)/* *.txt *.bin *.out *.o *.exe

.PHONY: release debug make_out_dir func cov gcov

debug: CFLAGS += -g3 -O0
debug: app.exe

release: CFLAGS += -g0 -O3 -DNDEBUG
release: app.exe

make_out_dir:
	mkdir -p $(OUT_DIR)

func: gcov
	./func_tests/scripts/func_tests.sh -USE_VALGRIND

unit: unit_tests.exe
	valgrind --tool=memcheck --log-file=tmp1.txt ./unit_tests.exe

app.exe: $(OBJS) $(OUT_DIR)/main.o
	$(CC) $(CFLAGS) $(OBJS) $(OUT_DIR)/main.o -o $@

unit_tests.exe: $(OBJS) $(TEST_OBJS)
	$(CC) $^ $(TST_FLAGS) -o $@

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

#$(OUT_DIR)/%.d: $(SRC_DIR)/%.c
#	$(CC) -M $(SRC_DIR)/%.c > $@

$(OUT_DIR)/%.o: $(UNIT_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	$(RM) $(RM_FILES) 

gcov: CFLAGS += -O0 -g --coverage -dumpbase ''
gcov: app.exe

cov : gcov
	./collect_coverage.sh

#include $(OUT_DIR)/$(SRCS:.c=.d)
