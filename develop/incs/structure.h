/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 05:25:47 by jischoi           #+#    #+#             */
/*   Updated: 2023/02/26 05:25:49 by jischoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_request
{
	int					id;
	char				*str;
	int					str_len;
	char				*cmd;
	char				**tab;
	int					nbr_token;
	t_token				*token;
	int					pid;
}				t_request;

typedef struct s_here_doc
{
	char				*delim;
	int					pipefd[2];
}				t_here_doc;

typedef struct s_prompt
{
	char				**envp;
	char				*clean;
	int					nbr_request;
	int					nbr_here_doc;
	int					pipefd[2];
	int					prev_pipefd;
	int					fork_i;
	struct s_here_doc	*here_docs;
	struct s_request	*requests;
}			t_prompt;

typedef struct s_parse
{
	int				double_quote;
	int				single_quote;
	int				is_pipe;
	int				has_semico;
	int				infile;
	int				outfile;
}				t_parse;

#endif
