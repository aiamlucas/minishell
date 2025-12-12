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
SRC				+= tokenizer/tokenizer.c
SRC				+= tokenizer/token-utils.c


OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)
	@echo "minishell compiled successfully"

# so that make can find the source files
vpath %.c $(SRC_DIR) $(SRC_DIR)/tokenizer $(SRC_DIR)/parser $(SRC_DIR)/builtins $(SRC_DIR)/execution $(SRC_DIR)/readline

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
