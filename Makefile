NAME			= minishell
CC				= cc
CFLAGS			= -Wall -Werror -Wextra
LIBFT_DIR		= libft
LIBFT			= $(LIBFT_DIR) -I$(LIBFT_DIR)/includes
OBJ_DIR			= obj

SRC				= main.c

OBJ				= $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) -L$(LIBFT_DIR) -lm -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR)/includes -c $< -o $@

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
