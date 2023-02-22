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
# include <linux/ioctl.h>
# include "libft.h"

# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <limits.h>
# include <errno.h>
# include <defines.h>

# include "defines.h"
# include "structure.h"

#define TIOCSTI     0x5412

extern int	g_exit_status;

/* TEMP */
void		print_token(t_token *token);
int			print_env(char **envp);

/* ERROR */
void		exit_minishell(t_prompt *prompt, int status);
int			print_error(int err_type, char *cmd, char *param);
int         print_syntax_error(t_parse data);
int         print_fd_error(char *path, char *cmd);
int         print_redirect_error(int type, char *path);

/* UTILS - free */
void		free_pp(char **pp);
void	    ft_close(int fd);
void	    free_all(t_prompt *p);

/* UTILS - init */
void	    init_envp(t_prompt *prompt, char *str, char **argv);
void	    init_prompt(char **argv, char **envp, t_prompt *prompt);

/* UTILS - matrix */
char		**dup_matrix(char **m);
int			get_matrixlen(char **m);

/* UTILS - token */
t_token	    *ft_token_last(t_token *token);
t_token	    *token_create(t_token *token);
void	    ft_token_add_back(t_token **token, t_token *new);

/* UTILS - utils */
void        push_str(char *str);
int	        is_sep(char s);
int	        is_quot(char s);
int			token_countcmd(t_token *token);
int			ft_strchr_int(const char *s, int c);

/* TOKEN */
t_token	    *fill_token(t_request *request);
int	        fill_request(char *cmd, t_prompt *prompt);

/* PARSE */
int	        env_key_len(char *out);
int	        insert_str(char *new_out, int *nout_i, char *str, int len);
void	    parse_cmd(char *cmd, char **envp);
int	        pre_check(char *out, t_prompt *prompt);
char	    *expansion(char *out, char **envp);
int         post_parse(t_request *request, int index);

/* PARSE - exit_status */
int	        exit_strlen(void);
int         expand_exit(char *new_out, int nout_i);

/* ENV */
char		*get_env(char *var, char **envp, int n);
char		**set_env(char *var, char *value, char **envp, int n);

/* INIT */
void	    init_envp(t_prompt *prompt, char *str, char **argv);
void	    init_prompt(char **argv, char **envp, t_prompt *prompt);

/* MAIN & SIGNAL */
void	    set_signal(void);
int			main(int argc, char **argv, char **envp);

/* parsing fix*/
int         reset_bool(t_parse *data, int init);
int         check_quote(t_parse *data, char c);

/* CMD - process */
int         redirection(t_request *request, t_prompt *prompt);
int			process(t_prompt *prompt);

/* exec bin func*/
int         exec_bin(t_request *request, t_prompt *prompt);

/* builtin  utils*/
int         is_builtin(char	*cmd);
int         ft_print(char *str, int	fd);
int			del_envp(int index, t_token *token, t_prompt *prompt);
int			add_envp(char *str, t_prompt *prompt);
int			in_envp(char *token, t_prompt *prompt);
int			update_oldpwd(t_prompt *prompt);

/* CMD - builtin */
int         ft_pwd(t_request *request, t_prompt *prompt);
int         ft_cd(t_request *request, t_prompt *prompt);
int         ft_echo(t_request *request, t_prompt *prompt);
int         ft_export(t_request *request, t_prompt *prompt);
int         ft_unset(t_request *request, t_prompt *prompt);

#endif
