CC				= cc
CFLAGS			= -Wall -Werror -Wextra
NAME			= minishell
LIBFT_DIR		= libft
LIBFT			= $(LIBFT_DIR)/libft.a
OBJ_DIR			= obj

ifeq ($(DEBUG),1)
CFLAGS += -g -O0
$(info Adding debug flags: -g -O0)
endif

SRC_DIR			= src
SRC				= main.c
SRC				+= readline/readline_loop.c
SRC				+= readline/validate_input.c
SRC				+= readline/process_input.c
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
SRC				+= builtins/builtin_export_utils.c
SRC				+= builtins/builtin_pwd.c
SRC				+= builtins/builtin_unset.c
SRC				+= builtins/builtin_exit.c
SRC				+= builtins/builtin_helpers.c
SRC				+= signals/signal_handler.c
SRC				+= signals/signals_utils.c
SRC				+= expansion/expand_tokens.c
SRC				+= expansion/expand_length.c
SRC				+= expansion/expand_variable_helpers.c
SRC				+= expansion/quote_removal.c
SRC				+= expansion/expand_copy_value.c
SRC				+= heredoc/heredoc.c
SRC				+= heredoc/heredoc_read.c
SRC				+= heredoc/heredoc_expand.c
SRC				+= heredoc/heredoc_utils.c


OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) bonus -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)
	@echo "minishell compiled successfully"

vpath %.c $(SRC_DIR) $(SRC_DIR)/tokenizer $(SRC_DIR)/parser \
          $(SRC_DIR)/builtins $(SRC_DIR)/execution \
          $(SRC_DIR)/readline $(SRC_DIR)/debug $(SRC_DIR)/signals \
		  $(SRC_DIR)/expansion $(SRC_DIR)/builtins $(SRC_DIR)/heredoc

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iinc -I$(LIBFT_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
