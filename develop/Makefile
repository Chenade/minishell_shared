###############################################################################
#                                                                             #
#                              Basic Config                                   #
#                                                                             #
###############################################################################

NAME		=	minishell

RM			=	rm -rf

CC			=	cc

CFLAGS		=	-Wall -Werror -Wextra
CFLAGS		+=	-I $(INCS_DIR) -I $(LIBFT_DIR) -I ${MLX_DIR}
CFLAGS		+=	-g3 -MMD

LFLAGS		= 	-L . -lmlx_Linux -lX11 -lXext -lm

CLIBS		=	-L . -lft

Y			= "\033[33m"
R			= "\033[31m"
GREEN		= "\033[92m"
BLUE		= "\033[94m"
X			= "\033[0m"
UP			= "\033[A"
CUT			= "\033[K"

###############################################################################
#                                                                             #
#                               Libs Config                                   #
#                                                                             #
###############################################################################

LIBFT		=	libft.a

LIBS_DIR	=	libs

LIBFT_DIR	=	$(LIBS_DIR)/libft

###############################################################################
#                                                                             #
#                                  Variable                                   #
#                                                                             #
###############################################################################

SRCS_DIR	=	srcs

INCS_DIR	=	incs

OBJS_DIR	=	objs

SRCS_GEN	=	general.c

SRCS		=	$(SRCS_GEN)
SRCS		+=	main.c

OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

###############################################################################
#                                                                             #
#                                   COMMAND                                   #
#                                                                             #
###############################################################################

all:			$(NAME)

$(LIBFT):
				@$(MAKE) -C $(LIBFT_DIR) all
				mv $(LIBFT_DIR)/$(LIBFT) .
				$(MAKE) -C $(LIBFT_DIR) fclean
				@echo ${GREEN}"Libft Compile Successfully\n"${X}

$(NAME):		$(LIBFT) $(OBJS)
				${CC} ${OBJS} ${CFLAGS} $(LIBFT) -o $@
				@echo ${GREEN}"Minishell Compile Successfully"${X}
				@echo ${BLUE}"Command: ./minishell or make run\n"${X}

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -c $< -o $@

clear:
				clear
				@echo "/****************************************************************************/"
				@echo "/*                                                                          */"
				@echo "/*                                                       :::      ::::::::  */"
				@echo "/*  minishell  <Common Core>                           :+:      :+:    :+:  */"
				@echo "/*                                                   +:+ +:+         +:+    */"
				@echo "/*  By:                                            +#+  +:+       +#+       */"
				@echo "/*     ykuo <marvin@42.fr>                       +#+#+#+#+#+   +#+          */"
				@echo "/*     jsichoi <marvin@42.fr>                         #+#    #+#            */"
				@echo "/*                                                   ###   ########.fr      */"
				@echo "/*                                                                          */"
				@echo "/****************************************************************************/"


norminette:		clear
				@echo ${Y}"\n=====minishell norminette check!====="${X}
				norminette $(SRCS_DIR) $(INCS_DIR)
				@echo ${GREEN}"=====minishell norminette check Successfully!=====\n"${X}


project:		clean $(OBJS)
				${CC} ${OBJS} ${CFLAGS} $(LIBFT) -o $(NAME)
				@echo ${GREEN}"Minishell Compile Successfully"${X}
				@echo ${BLUE}"Command: ./minishell or make run\n"${X}

clean:
				$(RM) $(OBJS_DIR)

fclean:			clean
				$(RM) $(LIBFT)
				@echo ${GREEN}"Lib Clean Successfully\n"${X}
				$(RM) $(NAME)
				@echo ${GREEN}"minishell Clean Successfully\n"${X}

run:			$(NAME)
				clear
				valgrind --leak-check=full --show-leak-kinds=all ./minishell
				# valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-fds=yes -s ./minishell

re:				fclean all

.PHONY:			all clean fclean re run project