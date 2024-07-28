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

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC := $(call rwildcard,src,*.c)
SRC := $(filter-out src/system%,$(SRC))
ifeq ($(OS),Windows_NT)
SRC += $(call rwildcard,src/system/windows,*.c)
else
SRC += $(call rwildcard,src/system/unix,*.c)
endif

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

.PHONY: iwyu
iwyu:
	@for file in $(shell find src -name "*.c"); do \
		include-what-you-use $(CFLAGS) $$file; \
	done

.PHONY: clean
clean:
	@rm -rf $(BIN_DIR) $(BUILD_DIR) $(OBJ_DIR)

.PHONY: run
run: $(TARGET)
	@$(TARGET)