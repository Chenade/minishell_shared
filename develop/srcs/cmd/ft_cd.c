#include "minishell.h"

int	update_oldpwd(t_prompt *prompt)
{
	int		index;
	char	*val;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		val = ft_strjoin("OLD_PWD=", cwd);
		index = in_envp(val, prompt);
		if (index > 0)
			prompt->envp[index] = val;
		else
			add_envp(val, prompt);
		free (val);
		return (0);
	}
}

int	ft_cd(int i, t_prompt *prompt)
{
	int		cd_ret;
	t_token	*token;
	char	*dest;

	token = move_to(prompt->token, i);
	if (ft_strcmp(token->str, "cd") == 0)
		dest = get_env("HOME", prompt->envp, 1);
	else if (ft_strcmp(token->str, "-") == 0)
	{
		dest = get_env("OLD_PWD", prompt->envp, 1);
		if (!dest)
		{
			print_error(OP_NS, "cd", NULL);
			return (-1);
		}
	}
	else
		dest = token->str;
	update_oldpwd(prompt);
	cd_ret = chdir(dest);
	if (cd_ret < 0)
		print_error(NDIR, "cd", token->str);
	return (cd_ret);
}
