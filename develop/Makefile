###############################################################################
#                                                                             #
#                              Basic Config                                   #
#                                                                             #
###############################################################################

NAME		=	minishell

RM			=	rm -rf

CC			=	cc

CFLAGS		=	-Wall -Werror -Wextra 
CFLAGS		+=	-I $(INCS_DIR) -I $(LIBFT_DIR) 
CFLAGS		+=	-g3 -MMD

# CFLAGS		= 	-I $(INCS_DIR) -I $(LIBFT_DIR)  -g3 -MMD

LFLAGS		= 	-L . -lmlx_Linux -lX11 -lXext -lm -I ${MLX_DIR}

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

SRCS_UTL	=	utils/init.c \
				utils/free.c \
				utils/matrix.c \
				utils/token.c \
				utils/print.c \
				utils/env.c \
				utils/error.c \
				utils/utils.c \
				signal.c 

SRCS_PAR	=	parse/pre_check.c \
				parse/expansion.c \
				parse/post_parse.c \
				parse/parse_cmd.c \
				parse/turn_sep.c \
				parse/parse_utils.c

SRCS_TOK	=	token/fill_token.c \
				token/request.c

SRCS_CMD	=	cmd/process.c \
				cmd/redirect.c \
				cmd/here_doc.c \
				cmd/builtin_cd.c \
				cmd/builtin_echo.c \
				cmd/builtin_export.c \
				cmd/builtin_utils.c \
				cmd/exec.c \
				cmd/exit.c

SRCS		=	$(SRCS_UTL)
SRCS		+=	$(SRCS_PAR)
SRCS		+=	$(SRCS_TOK)
SRCS		+=	$(SRCS_CMD)
SRCS		+=	main.c

OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

###############################################################################
#                                                                             #
#                                   COMMAND                                   #
#                                                                             #
###############################################################################

# all:			norminette $(NAME)
all:			$(NAME)

$(LIBFT):
				@$(MAKE) -C $(LIBFT_DIR) all
				mv $(LIBFT_DIR)/$(LIBFT) .
				$(MAKE) -C $(LIBFT_DIR) fclean
				@echo ${GREEN}"===== Libft Compile Successfully =====\n"${X}

$(NAME):		$(LIBFT) $(OBJS)
				${CC} ${OBJS} ${CFLAGS} -lreadline $(LIBFT) -o $@
				@echo ${GREEN}"===== Minishell Compile Successfully =====\n"${X}
				@echo ${Y}"Huge thanks to: "${X}
				@echo ${Y}"    Aboudjel (Master of parsing),"${X}
				@echo ${Y}"    Mgamil (Master of execution),"${X}
				@echo ${Y}"    Aweaver, Yatang, Amattei\n"${X}
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


correction:		fclean clear
				@echo ${Y}"\n===== minishell norminette check! ====="${X}
				norminette $(SRCS_DIR) $(INCS_DIR)
				@echo ${GREEN}"===== minishell norminette check Successfully! =====\n"${X}
				make all


project:		clean $(OBJS)
				${CC} ${OBJS} ${CFLAGS} -lreadline $(LIBFT) -o $(NAME)
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
				valgrind -s --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes -s ./minishell

re:				fclean all

.PHONY:			all clean fclean re run project