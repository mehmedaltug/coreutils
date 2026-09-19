SRC_DIR := src
TEST_DIR := test
OUT_DIR := out
CFILES := $(wildcard $(SRC_DIR)/*.c)
TARGETS := $(patsubst $(SRC_DIR)/%.c,out/%,$(CFILES))

PY_TEST_FILES := $(wildcard $(TEST_DIR)/*.py)
PY_TEST_RUNNERS := $(patsubst $(TEST_DIR)/%.py,testpy-%,$(PY_TEST_FILES))

C_TEST_FILES := $(wildcard $(TEST_DIR)/*.c)
C_TEST_RUNNERS := $(patsubst $(TEST_DIR)/%.c,testc-%,$(C_TEST_FILES))

CC := gcc
CFLAGS := -Wall -Wextra -g -O0 -Ilib
PY := python3

.PHONY: all test clean

all: $(TARGETS)

test: py_tests | c_tests

py_tests: $(PY_TEST_RUNNERS)

c_tests: $(C_TEST_RUNNERS)

$(OUT_DIR)/%: $(SRC_DIR)/%.c | $(OUT_DIR)/
	$(CC) $(CFLAGS) $< -o $@

testc-%: $(TEST_DIR)/%.c | $(OUT_DIR)/
	$(CC) $(CFLAGS) $< -o $(OUT_DIR)/$@
	$(OUT_DIR)/$@
	@echo ""

testpy-%: $(TEST_DIR)/%.py
	$(PY) $<
	@echo ""

%: $(SRC_DIR)/%.c | $(OUT_DIR)/
	$(CC) $(CFLAGS) $< -o $(OUT_DIR)/$@

$(OUT_DIR)/:
	mkdir -p $(OUT_DIR)/$(TEST_DIR)

clean:
	rm -rf $(OUT_DIR)
