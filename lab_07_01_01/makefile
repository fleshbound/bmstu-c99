SRC_DIR := ./src
INC_DIR := ./inc
OUT_DIR := ./out
UNIT_DIR := ./unit_tests
FUNC_DIR := ./func_tests

CC := gcc
CFLAGS := -std=c99 -I$(INC_DIR) -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla
UNIT_FLAGS := -lcheck -lm -lpthread -lsubunit -lrt

APP := app.exe
UNIT_APP := unit_tests.exe

ifeq ($(mode), debug)
    CFLAGS += -g3 -O0
endif

ifeq ($(mode), release)
    CFLAGS += -g0 -O3
endif

SRCS := $(wildcard $(SRC_DIR)/*.c)
#OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OUT_PATH)/%.o)
#UNIT_SRCS := $(wildcard $(UNIT_DIR)/*.c)
#UNIT_OBJS := $(UNIT_SRCS:$(UTEST_DIR)/%.c=$(OUT_PATH)/%.o)
UNIT_OBJS := $(patsubst $(UNIT_DIR)/%.c,$(OUT_DIR)/%.o,$(wildcard $(UNIT_DIR)/*.c))
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OUT_DIR)/%.o,$(wildcard $(SRC_DIR)/*.c))
OBJS := $(filter-out $(OUT_DIR)/main.o,$(OBJS))

.PHONY : build unit clean make_outdir

release: $(APP)

func: 
	$(FUNC_DIR)/scripts/func_tests.sh -USE_VALGRIND

unit: $(UNIT_APP)

$(APP): make_outdir $(OBJS) $(OUT_DIR)/main.o
	@$(CC) $(CFLAGS) $(OBJS) $(OUT_DIR)/main.o $(UNIT_FLAGS) -o $@

$(UNIT_APP): make_outdir $(OBJS) $(UNIT_OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(UNIT_OBJS) $(UNIT_FLAGS) -o $@

make_outdir:
	@mkdir -p $(OUT_DIR)

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/check_%.o: $(UNIT_DIR)/check_%.c
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -rf $(OUT_DIR) *.exe *.txt *.bin

