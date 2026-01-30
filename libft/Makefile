# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/26 17:38:30 by lbueno-m          #+#    #+#              #
#    Updated: 2025/12/24 15:29:56 by lbueno-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

ifeq ($(DEBUG),1)
CFLAGS += -g -O0
endif

# Core libft functions
SRC = ft_atoi.c
SRC += ft_safe_atoi.c
SRC += ft_atof.c
SRC += ft_bzero.c
SRC += ft_calloc.c
SRC += ft_isalnum.c
SRC += ft_isalpha.c
SRC += ft_isascii.c
SRC += ft_isdigit.c
SRC += ft_isprint.c
SRC += ft_isspace.c
SRC += ft_memchr.c
SRC += ft_memcmp.c
SRC += ft_memcpy.c
SRC += ft_memmove.c
SRC += ft_memset.c
SRC += ft_strchr.c
SRC += ft_strdup.c
SRC += ft_strlcat.c
SRC += ft_strlcpy.c
SRC += ft_strlen.c
SRC += ft_strncmp.c
SRC += ft_strnstr.c
SRC += ft_strrchr.c
SRC += ft_strtrim.c
SRC += ft_tolower.c
SRC += ft_toupper.c
SRC += ft_strjoin.c
SRC += ft_split.c
SRC += ft_itoa.c
SRC += ft_putchar_fd.c
SRC += ft_putstr_fd.c
SRC += ft_putnbr_fd.c
SRC += ft_putendl_fd.c
SRC += ft_strmapi.c
SRC += ft_striteri.c
SRC += ft_substr.c
SRC += ft_realloc.c
SRC += ft_atol.c
SRC += ft_strcmp.c

# ft_printf functions
SRC += ft_printf/src/ft_printf.c
SRC += ft_printf/src/dispatcher.c
SRC += ft_printf/src/handlers/handle_char.c
SRC += ft_printf/src/handlers/handle_hex.c
SRC += ft_printf/src/handlers/handle_int.c
SRC += ft_printf/src/handlers/handle_percent.c
SRC += ft_printf/src/handlers/handle_pointer.c
SRC += ft_printf/src/handlers/handle_string.c
SRC += ft_printf/src/handlers/handle_unsigned.c
SRC += ft_printf/src/helpers/ft_putchar_len.c
SRC += ft_printf/src/helpers/ft_puthex_len.c
SRC += ft_printf/src/helpers/ft_putnumber_len.c
SRC += ft_printf/src/helpers/ft_putpointer_len.c
SRC += ft_printf/src/helpers/ft_putstr_len.c
SRC += ft_printf/src/helpers/ft_putunsigned_len.c

OBJ = $(SRC:.c=.o)

# BONUS
BONUS_SRC = ft_lstnew.c
BONUS_SRC += ft_lstadd_front.c
BONUS_SRC += ft_lstadd_back.c
BONUS_SRC += ft_lstsize.c
BONUS_SRC += ft_lstlast.c
BONUS_OBJ = $(BONUS_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
	@echo "libft.a compiled"

bonus: $(OBJ) $(BONUS_OBJ)
	ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)
	@echo "libft.a with bonus functions compiled"

%.o: %.c
	$(CC) $(CFLAGS) -Ift_printf -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
