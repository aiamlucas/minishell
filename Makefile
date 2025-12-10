CC				= cc
#CFLAGS			= -Wall -Werror -Wextra
NAME			= minishell

LIBFT_DIR		= libft
LIBFT			= $(LIBFT_DIR) -I$(LIBFT_DIR)/includes
OBJ_DIR			= obj

ifeq ($(DEBUG),1)
CFLAGS += -g -O0
$(info Adding debug flags: -g -O0)
endif

SRC_DIR			= src
SRC					= $(SRC_DIR)/main.c
# for new files add them as:
# SRC += new_file.c

OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) -L$(LIBFT_DIR) -lft -lreadline -lm -o $(NAME)
	@echo "minishell compiled successfully"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
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
