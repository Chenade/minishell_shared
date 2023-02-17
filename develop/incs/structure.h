#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;
}				t_sig;

typedef struct s_token
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
	int		output_fd;
	int		input_fd;
	char	*result;
	char	**envp;
	int		has_pipe;
	pid_t	pid;
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
