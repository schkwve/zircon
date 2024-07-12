CC ?= gcc
LD ?= ld

CFLAGS ?= -std=c89 -Wall -Wextra -Werror -O3 -Isrc -fno-strict-aliasing -fno-wrapv
LDFLAGS ?=

BIN_DIR := bin
OBJ_DIR := build
SRC_DIR := src
DESTDIR ?= /usr/local/bin

TARGET_NAME := zircon
TARGET := $(BIN_DIR)/$(TARGET_NAME)

SRC := $(shell find src -name '*.c' -type f)
OBJ := $(SRC:%.c=$(OBJ_DIR)/%.o)

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(@D)
	@printf "  LD $(notdir $@)\n"
	@$(CC) $(LDFLAGS) $(OBJ) -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@printf "  CC $<\n"
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: install
install: $(TARGET)
	@install -m 755 $(TARGET) $(DESTDIR)

.PHONY: format
format:
	@clang-format -i $(shell find src -name "*.c" -o -name "*.h")

.PHONY: lint
lint:
	@clang-tidy $(shell find src -name "*.c" -o -name "*.h") -- $(CFLAGS)

.PHONY: clean
clean:
	@rm -rf $(BIN_DIR) $(BUILD_DIR) $(OBJ_DIR)
