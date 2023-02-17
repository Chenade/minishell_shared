#include "minishell.h"

extern int	exit_status;

int	check_type(int type)
{
	if (type == DELIM || type == OUTPUT || type == INPUT \
	|| type == APPEN || type == PIPE)
		return (1);
	return (0);
}

int	syntax_check_next_sub(t_prompt *prompt, t_token *token)
{
	if (token->type >= OUTPUT && token->type <= DELIM)
	{
		if (token->prev->type >= OUTPUT && token->prev->type <= DELIM)
		{
			print_error(SYNT, NULL, NULL);
			exit_status = 258;
			return (0);
		}
		if (!token->next)
		{
			print_error(SYNT, NULL, NULL);
			exit_status = 258;
			return (0);
		}
	}
	return (1);
}

int	syntax_check_next(t_prompt *prompt, t_token *token)
{
	if (token->type == PIPE)
	{
		if (token->prev->type >= OUTPUT && token->prev->type <= PIPE)
		{
			print_error(SYNT, NULL, NULL);
			return (0);
		}
		else if (!token->next)
		{
			print_error(SYNT, NULL, NULL);
			exit_status = 258;
			return (0);
		}
	}
	else if (!syntax_check_next_sub(prompt, token))
		return (0);
	return (1);
}

int	check_syntax(t_prompt *prompt, t_token *token)
{
	if (!token->next && check_type(token->type))
	{
		if (token->type == PIPE)
			print_error(PIPERR, NULL, NULL);
		else
			print_error(SYNT, NULL, NULL);
		exit_status = 258;
		return (0);
	}
	while (token->next)
	{
		token = token->next;
		if (check_type(token->type))
			if (!syntax_check_next(prompt, token))
				return (0);
	}
	// if (!paren_syntax_check(prompt))
	// 	return (0);
	return (1);
}