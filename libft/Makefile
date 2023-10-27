# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/28 13:30:35 by lhasmi            #+#    #+#              #
#    Updated: 2023/10/27 17:15:11 by lhasmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAG = -Wall -Wextra -Werror -O3

NAME = libft.a
SRC =	free_argv.c\
		ft_atoi.c\
		ft_bzero.c\
		ft_calloc.c\
		ft_error.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_itoa.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memset.c\
		ft_openfile.c\
		ft_printf.c\
		ft_putchar_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_putstr_fd.c\
		pf_convert_chr.c\
		pf_convert_hex.c\
		pf_convert_nbr.c\
		pf_convert_str.c\
		ft_split.c\
		ft_strcat.c\
		ft_strchr.c\
		ft_strcpy.c\
		ft_strdup.c\
		ft_striteri.c\
		ft_strjoin.c\
		ft_strlcat.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_strmapi.c\
		ft_strncmp.c\
		ft_strncpy.c\
		ft_strnstr.c\
		ft_strtok.c\
		ft_strrchr.c\
		ft_strtrim.c\
		ft_substr.c\
		ft_tolower.c\
		get_next_line.c\
		ft_toupper.c

BONUSSRC = ft_lstnew.c\
			ft_lstadd_front.c
OBJ = $(SRC:.c=.o)
BONUSOBJ = $(BONUSSRC:.c=.o)

all: $(NAME)

%.o:	%.c
	cc -c $(FLAG) $^ -o $@

$(NAME): $(OBJ)
	ar -crs $(NAME) $(OBJ)

bonus: $(BONUSOBJ) $(OBJ)
	ar -crs $(NAME) $(OBJ) $(BONUSOBJS)

clean:
	rm -rf $(OBJ) $(BONUSOBJ)
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, do
