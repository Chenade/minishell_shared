/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:14:04 by ykuo              #+#    #+#             */
/*   Updated: 2023/01/25 16:04:27 by jischoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include "libft.h"

# define 	READ	0
# define 	WRITE	1
# define	CHILD	0

enum	token_type
{ 
	EMPTY = 0,
	CMD = 1,
	ARG = 2,
	ENV_DEF = 3,
	ENV_VAL = 4,
	OPTN = 5,
	INPUT = 6, // <
	OUTPUT = 7, // >
	DELIM = 8, // <<
	APPEN = 9, // >>
	PIPE = 10
};

enum	e_mini_error
{
	QUOTE = 1,
	WCHAR = 2,
	NDIR = 3,
	NPERM = 4,
	NCMD = 5,
	DUPERR = 6,
	FORKERR = 7,
	PIPERR = 8,
	MEM = 9,
	IS_DIR = 10,
	NOT_DIR = 12
};

typedef struct	s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_prompt
{
	t_token	*token;
	t_list	*env;
	char	*result;
	char	**envp;
	pid_t	pid;
	int 	exit_status;
}			t_prompt;

/* temp */
void		print_token(t_token *token);
void		print_env(char **envp);

/* error */
void		*print_error(int err_type, char *param);

/* utils */
int			ft_strchr_int(const char *s, int c);
char		**dup_matrix(char **m);
// void		free_pp(char **pp);
void		free_matrix(char ***m);
// char		**extend_matrix(char **in, char *newstr);
int			get_matrixlen(char **m);

/* token */
void		fill_type(t_token *token, int separator);
t_token 	*fill_nodes(char **args);

/* parser */
void		*check_args(char *out, t_prompt *p);

/* env */
char		*get_env(char *var, char **envp, int n);
char		**set_env(char *var, char *value, char **envp, int n);

/* main, init */
int			main(int argc, char **argv, char **envp);

t_token		*move_to(t_token *pre, int index);
int 		process(t_prompt *prompt);
int			ft_echo(int i, t_prompt *prompt);
#endif
