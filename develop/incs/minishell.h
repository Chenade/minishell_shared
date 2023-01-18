/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <ykuo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:14:04 by ykuo              #+#    #+#             */
/*   Updated: 2022/11/13 16:14:05 by ykuo             ###   ########.fr       */
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
# include "libft.h"

# define 	READ	0
# define 	WRITE	1
# define	CHILD	0

# define EMPTY 0
# define CMD 1
# define ARG 2
# define OPTN 3
# define INPUT 4 // <
# define OUTPUT 5 // >
# define DELIM 6 // <<
# define APPEN 7 // >>
# define PIPE 8
# define END 9


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
	t_list	*cmds;
	char	*full_cmd;
	char	**envp;
	pid_t	pid;
	int 	exit_status;
}			t_prompt;


#endif
