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

typedef struct s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;
}				t_sig;

// typedef struct s_tokens
// {
// 	char			*str;
// 	int				type;
// }				t_tokens;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_request
{
	char				*str;
	int					str_len;
	char				**tab;
	int					nbr_token;
	int					input_fd;
	int					output_fd;
	struct s_tokens		*token;
}				t_request;

typedef struct s_prompt
{
	char				*clean;
	int					nbr_request;
	t_token				*token;
	char				**envp;
	pid_t				pid;
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
