# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmenasse <cmenasse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/15 20:15:43 by cmenasse          #+#    #+#              #
#    Updated: 2022/06/12 21:56:10 by ykuo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	libft.a

SRCS 		=	ft_abs.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strchr.c\
				ft_strlen.c  ft_strrchr.c ft_toupper.c ft_isalpha.c ft_isdigit.c\
				ft_memcpy.c ft_strncmp.c ft_tolower.c ft_strlcpy.c ft_strlcat.c\
				ft_strnstr.c ft_atoi.c ft_memset.c ft_bzero.c ft_memchr.c\
				ft_memcpy.c ft_memmove.c ft_memcmp.c ft_strdup.c ft_calloc.c\
				ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c\
				ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c\
				ft_putnbr_fd.c get_next_line.c ft_printf.c ft_put.c ft_puthex.c\
				ft_min.c ft_max.c ft_swap.c

BONUS_SRCS	=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
				ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS		=	$(SRCS:.c=.o)

BONUS_OBJS	=	$(BONUS_SRCS:.c=.o)

CC 			=	cc

CFLAGS		=	-Wall -Wextra -Werror

RM 			=	rm -f

Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

.c.o:		
		@echo ${Y}Compiling [$@]...${X}
		@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
		@printf ${UP}${CUT}

all:		$(NAME)

$(NAME):	$(OBJS) $(BONUS_OBJS)
		@ar rc $(NAME) $(OBJS) $(BONUS_OBJS)

bonus:		$(OBJS) $(BONUS_OBJS)
		ar rc $(NAME) $(OBJS) $(BONUS_OBJS)

clean:		
		@$(RM) $(OBJS) $(BONUS_OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: 	all clean fclean re
