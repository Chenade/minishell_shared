/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   structure.h										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ykuo <marvin@42.fr>						+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/02/18 00:25:36 by ykuo			  #+#	#+#			 */
/*   Updated: 2023/02/18 00:25:37 by ykuo			 ###   ########.fr	   */
/*																			*/
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

typedef struct s_prompt
{
	char				*clean;
	int					nbr_request;
	char				**envp;
	t_token				*token;
	pid_t				pid;
	int					pipefd[2];
	int					prev_pipefd;
	struct s_request	*requests;
}			t_prompt;

typedef struct s_parse
{
	int				double_quote;
	int				single_quote;
	int				is_pipe;
	int				infile;
	int				outfile;
}				t_parse;

#endif
