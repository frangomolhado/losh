CC = clang
CFLAGS = -std=c17 -Wall -Wextra
DBFLAGS = $(CFLAGS) -g3 -Og
RLFLAGS = $(CFLAGS) -D_FORTIFY_SOURCE=2 -O3

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ_DB = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/debug/%.o, $(SRC))
OBJ_RL = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/release/%.o, $(SRC))
BIN = losh

.PHONY: all
all: debug

.PHONY: clean
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: format
format:
	@clang-format src/*.c -style=file -i

.PHONY: gdb
gdb:
	@gdb $(BIN_DIR)/debug/$(BIN)

# Debug compilation
.PHONY: debug
debug: debug_dirs $(BIN_DIR)/debug/$(BIN)

$(BIN_DIR)/debug/$(BIN): $(OBJ_DB)
	$(CC) $(OBJ_DB) $(DBFLAGS) -o $@

$(OBJ_DIR)/debug/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< $(DBFLAGS) -o $@

.PHONY: debug_dir
debug_dirs: $(OBJ_DIR)/debug $(BIN_DIR)/debug

$(OBJ_DIR)/debug:
	@mkdir -p $@

$(BIN_DIR)/debug:
	@mkdir -p $@

.PHONY: run
run: debug
	@./$(BIN_DIR)/debug/$(BIN)

# Release compilation
.PHONY: release
release: release_dirs $(BIN_DIR)/release/$(BIN)

$(BIN_DIR)/release/$(BIN): $(OBJ_RL)
	$(CC) $(OBJ_RL) $(RLFLAGS) -o $@

$(OBJ_DIR)/release/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< $(RLFLAGS) -o $@

.PHONY: release_dirs
release_dirs: $(OBJ_DIR)/release $(BIN_DIR)/release

$(OBJ_DIR)/release:
	@mkdir -p $@

$(BIN_DIR)/release:
	@mkdir -p $@

.PHONY: runr
runr: release
	@./$(BIN_DIR)/release/$(BIN)
