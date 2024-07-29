CC ?= gcc
LD ?= ld

CFLAGS ?=  -std=c89 -Wall -Wextra -Werror -Isrc -fno-strict-aliasing -fno-wrapv -g3 -O0 -rdynamic -g 
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

.PHONY: run-scripts

run-scripts:
	@echo "Making all scripts executable..."
	@chmod +x scripts/*.sh
	@echo "Executing all scripts except scripts/cloc.sh..."
	@for script in scripts/*.sh; do \
		if [ "$$script" != "scripts/cloc.sh" ]; then \
			echo "Executing $$script..."; \
			$$script; \
		fi \
	done
	@echo "Clearing the screen..."
	@clear
	@echo "Executing scripts/cloc.sh..."
	@scripts/cloc.sh

.PHONY: clean
clean:
	@rm -rf $(BIN_DIR) $(BUILD_DIR) $(OBJ_DIR)

.PHONY: run
run: $(TARGET)
	@$(TARGET)