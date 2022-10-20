.PHONY : build utest stat clean outdir

EXEC := app.exe
UTEST_EXEC := unit_tests.exe
STAT_EXEC := stat.exe

SRC_PATH := ./src
INC_PATH := ./inc
OUT_PATH := ./out

UTEST_PATH := ./unit_tests
FTEST_PATH := ./func_tests
STAT_PATH := ./stat

CC := gcc
CFLAGS := -std=gnu99 -I$(INC_PATH) -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla
LD_FLAGS := `pkg-config --cflags --libs check`

ifeq ($(mode), debug)
    CFLAGS += -g3
endif

ifeq ($(mode), release)
    CFLAGS += -O3
endif

SRCS := $(wildcard $(SRC_PATH)/*.c)
OBJS := $(SRCS:$(SRC_PATH)/%.c=$(OUT_PATH)/%.o)

UTEST_SRCS := $(wildcard $(UTEST_PATH)/*.c)
UTEST_OBJS := $(UTEST_SRCS:$(UTEST_PATH)/%.c=$(OUT_PATH)/%.o)

STAT_SRCS := $(wildcard $(STAT_PATH)/*.c)
STAT_OBJS := $(STAT_SRCS:$(STAT_PATH)/%.c=$(OUT_PATH)/%.o)

build: $(EXEC)

utest: $(UTEST_EXEC)

stat: $(STAT_EXEC)

$(EXEC): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^ $(LD_FLAGS)

$(UTEST_EXEC) : $(filter-out $(OUT_PATH)/main.o, $(OBJS)) $(UTEST_OBJS)
	@$(CC) $(CFLAGS) -o $@ $^ $(LD_FLAGS)

$(STAT_EXEC) : $(filter-out $(OUT_PATH)/main.o, $(OBJS)) $(STAT_OBJS)
	@$(CC) $(CFLAGS) -o $@ $^ $(LD_FLAGS)

outdir:
	@mkdir -p $(OUT_PATH)

${OUT_PATH}/%.o : ${SRC_PATH}/%.c outdir
	@$(CC) $(CFLAGS) -c $< -o $@

$(OUT_PATH)/check_%.o : $(UTEST_PATH)/check_%.c outdir
	@$(CC) $(CFLAGS) -o $@ -c $<

$(OUT_PATH)/stat_%.o : $(STAT_PATH)/stat_%.c outdir
	@$(CC) $(CFLAGS) -o $@ -c $<

$(INC_PATH)/%.h:

clean:
	@rm -f $(EXEC) $(UTEST_EXEC) $(STAT_EXEC) ${OUT_PATH}/*
	@rm -rf $(OUT_PATH)

