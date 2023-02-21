/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jischoi <jischoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:14:04 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/18 04:20:08 by jischoi          ###   ########.fr       */
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

# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <limits.h>
# include <errno.h>
# include <defines.h>

# include "defines.h"
# include "structure.h"

extern t_sig	g_sig;

/* temp */
void		print_token(t_token *token);
int			print_env(char **envp);

/* error */
void		exit_minishell(t_prompt *prompt, int status);
int			print_error(int err_type, char *cmd, char *param);

/* utils */
void	ft_token_add_back(t_token **token, t_token *new);
t_token	    *ft_token_last(t_token *token);
int	        is_sep(char s);
void	    init_envp(t_prompt *prompt, char *str, char **argv);
void	    init_prompt(char **argv, char **envp, t_prompt *prompt);
void		free_pp(char **pp);
int			token_countcmd(t_token *token);
int			ft_strchr_int(const char *s, int c);
char		**dup_matrix(char **m);
int			get_matrixlen(char **m);
// char		**extend_matrix(char **in, char *newstr);

/* free */
void		free_matrix(char ***m);
void		free_token(t_token **token);
void		free_all(t_prompt *p);
// void	    free_readline(char **out, t_prompt *prompt);
void		ft_close(int fd);

/* token */
int	        fill_request(char *cmd, t_prompt *prompt);
t_token	    *fill_token(t_request *request);

/* env */
char		*get_env(char *var, char **envp, int n);
char		**set_env(char *var, char *value, char **envp, int n);

/* main, init */
void		mini_getpid(t_prompt *p);
int			main(int argc, char **argv, char **envp);

/* cmd process */
int	        env_key_len(char *out);
int			process(t_prompt *prompt);
t_token		*move_to(t_token *pre, int index);

/* parsing fix*/
void	    parse_cmd(char *cmd, char **envp);
int         pre_check(char *out, t_prompt *prompt);
char		*expansion(char *out, char **envp);
int			redirect_input(t_prompt *prompt);
int			redirect_input2(t_prompt *prompt);
int			redirect_output(t_prompt *prompt);

void	    ft_token_clear(t_token *token);
t_token	    *ft_token_new(void *content, int type);
void	    ft_token_add_back(t_token **token, t_token *new);
t_token	    *ft_token_last(t_token *token);

/* parsing fix*/
int         reset_bool(t_parse *data, int init);
int         check_quote(t_parse *data, char c);
// int         separate_pipe(char *out, t_prompt *prompt);

/* builtin  utils*/
int         ft_print(char *str, int	fd);
int			del_envp(int index, t_token *token, t_prompt *prompt);
int			add_envp(char *str, t_prompt *prompt);
int			in_envp(char *token, t_prompt *prompt);
int			update_oldpwd(t_prompt *prompt);

/* builtin  func*/
int         ft_pwd(t_request *request, t_prompt *prompt);
int         ft_cd(t_request *request, t_prompt *prompt);
int         ft_echo(t_request *request, t_prompt *prompt);
int         ft_export(t_request *request, t_prompt *prompt);
int         ft_unset(t_request *request, t_prompt *prompt);

/* exec bin func*/
int         exec_bin(t_request *request, t_prompt *prompt);

#endif
