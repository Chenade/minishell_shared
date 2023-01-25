/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:14:04 by ykuo              #+#    #+#             */
/*   Updated: 2023/01/25 15:44:31 by jischoi          ###   ########.fr       */
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
	char	**envp;
	pid_t	pid;
	int 	exit_status;
}			t_prompt;

void	print_token(t_token *token);
void	fill_type(t_token *token, int separator);
t_token *fill_nodes(char **args);


void	*print_error(int err_type, char *param);

int		ft_strchr_int(const char *s, int c);
void	free_pp(char **pp);
void	free_matrix(char ***m);
char	**extend_matrix(char **in, char *newstr);
void	print_env(char **envp);
int		get_matrixlen(char **m);
char	**ft_dup_matrix(char **m);

void	*check_args(char *out, t_prompt *p);

char	*get_env(char *var, char **envp, int n);
char	**set_env(char *var, char *value, char **envp, int n);


int	main(int argc, char **argv, char **envp);


#endif
