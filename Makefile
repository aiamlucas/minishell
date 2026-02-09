CC				= cc
CFLAGS			= -Wall -Werror -Wextra
NAME			= minishell
LIBFT_DIR		= libft
LIBFT			= $(LIBFT_DIR)/libft.a
OBJ_DIR			= obj

TEST_LEXER_BIN		= test-lexer.bin

ifeq ($(DEBUG),1)
CFLAGS += -g -O0
$(info Adding debug flags: -g -O0)
endif

SRC_DIR			= src
SRC				= main.c
SRC				+= readline/readline_loop.c
SRC				+= tokenizer/tokenizer.c
SRC				+= tokenizer/token-utils.c
SRC				+= parser/command-utils.c
SRC				+= parser/redir-utils.c
SRC				+= parser/env-utils.c
SRC				+= parser/parser.c
SRC				+= debug/debug_print.c
SRC				+= execution/builtin_utils.c
SRC				+= execution/execute_command.c
SRC				+= execution/execute_pipeline.c
SRC				+= execution/pipeline_child.c
SRC				+= execution/path_utils.c
SRC				+= execution/pipeline_helpers.c
SRC				+= execution/redirections.c
SRC				+= execution/execution_utils.c
SRC				+= builtins/builtin_cd.c
SRC				+= builtins/builtin_echo.c
SRC				+= builtins/builtin_env.c
SRC				+= builtins/builtin_export.c
SRC				+= builtins/builtin_pwd.c
SRC				+= builtins/builtin_unset.c
SRC				+= builtins/builtin_exit.c
SRC				+= builtins/helpers.c
SRC				+= signals/signal_handler.c
SRC				+= signals/signals_utils.c
SRC				+= expansion/expand_tokens.c

TEST_DIR		= tests
TEST_SRC		= test-lexer-main.c
TEST_SRC		+= test-utils.c
TEST_SRC		+= test-lexer.c

OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
TEST_OBJ = $(addprefix $(TEST_DIR)/, $(TEST_SRC:.c=.o))

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) bonus -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)
	@echo "minishell compiled successfully"

# so that make can find the source files
vpath %.c $(SRC_DIR) $(SRC_DIR)/tokenizer $(SRC_DIR)/parser \
          $(SRC_DIR)/builtins $(SRC_DIR)/execution \
          $(SRC_DIR)/readline $(SRC_DIR)/debug $(SRC_DIR)/signals \
		  $(SRC_DIR)/expansion

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iinc -I$(LIBFT_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)


########################
# Tests rules
$(TEST_DIR):
	@mkdir -p $(TEST_DIR)

$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	@$(CC) $(CFLAGS) -I$(TEST_DIR) -Iinc -I$(LIBFT_DIR) -c $< -o $@


$(TEST_LEXER_BIN): $(TEST_OBJ) $(OBJ_DIR)/tokenizer.o \
                   $(OBJ_DIR)/token-utils.o $(LIBFT)
	$(CC) $(CFLAGS) $(TEST_OBJ) $(OBJ_DIR)/tokenizer.o \
		$(OBJ_DIR)/token-utils.o -L$(LIBFT_DIR) -lft -o $(TEST_LEXER_BIN)
	@echo "test-lexer compiled successfully"

test-lexer: $(TEST_LEXER_BIN)

run-test-lexer: test-lexer
	@./$(TEST_LEXER_BIN)

run-test-lexer-valgrind: test-lexer
	@valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --suppressions=readline.supp \
		./$(TEST_LEXER_BIN)

test-clean:
	@rm -f $(TEST_OBJ)
	@rm -f $(TEST_LEXER_BIN)
########################

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean test-clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re run-test-lexer run-test-lexer-valgrind test-clean
