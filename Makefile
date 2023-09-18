CC = clang
CFLAGS = -Wall -Wextra

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

MODULES = placeholder
SRC_MOD = $(addprefix $(SRC_DIR)/, $(MODULES))
OBJ_MOD_DB = $(addprefix $(OBJ_DIR)/debug/, $(MODULES))
OBJ_MOD_RL = $(addprefix $(OBJ_DIR)/release/, $(MODULES))

SRC = $(foreach smod, $(SRC_MOD), $(wildcard $(smod)/*.c))
OBJ_DB = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/debug/%.o, $(SRC))
OBJ_RL = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/release/%.o, $(SRC))
INC = $(addprefix -I , $(SRC_MOD))

BIN = losh

all: debug

debug: $(BIN_DIR)/debug/$(BIN)
release: $(BIN_DIR)/release/$(BIN)

# Debug compilation
$(BIN_DIR)/debug/$(BIN): $(OBJ_DB) | $(BIN_DIR)/debug
	$(CC) $(SRC_DIR)/main.c $< $(INC) $(CFLAGS) -g -O0 -o $@

$(OBJ_DB): $(SRC) | $(OBJ_MOD_DB)
	$(CC) -c $< $(INC) $(CFLAGS) -g -O0 -o $@

$(BIN_DIR)/debug:
	@mkdir -p $@

$(OBJ_MOD_DB):
	@mkdir -p $@

# Release compilation
$(BIN_DIR)/release/$(BIN): $(OBJ_RL) | $(BIN_DIR)/release
	$(CC) $(SRC_DIR)/main.c $< $(INC) $(CFLAGS) -O3 -o $@

$(OBJ_RL): $(SRC) | $(OBJ_MOD_RL)
	$(CC) -c $< $(INC) $(CFLAGS) -O3 -o $@

$(BIN_DIR)/release:
	@mkdir -p $@

$(OBJ_MOD_RL):
	@mkdir -p $@

run: $(BIN_DIR)/debug/$(BIN)
	@./$<

runr: $(BIN_DIR)/release/$(BIN)
	@./$<

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(BIN_DIR)
