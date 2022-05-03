/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cdecho.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:08:21 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/03 17:39:34 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cdirectory(char **args, t_prompt *prompt)
{
	char	*pwd;
	char	*dir;
	char	**tmp;
	char	*fpwd;

	pwd = ft_getpwd();
	if (args[1][ft_strlen(args[1]) - 1] == '\\')
	{
		tmp = ft_split(args[1], '\\');
		dir = ft_strcat(ft_strjoin(tmp[0], " "), args[2]);
		ft_oldpwd(prompt);
		if (chdir(dir) != 0)
			printf("minishell: cd: no such file or directory: %s\n", dir);
	}
	else if (!ft_strnstr(pwd, ft_rmslash(args[1]), ft_strlen(pwd)))
		printf("minishell: cd: string not in pwd: %s\n", ft_rmslash(args[1]));
	else
	{
		fpwd = ft_strjoin(ft_getparentdir(pwd, args[1]), args[2]);
		if (chdir(fpwd) != 0)
			printf("minishell: cd: no such file or directory: %s\n", fpwd);
	}
}

void	ft_oldpwd(t_prompt *prompt)
{
	char	*oldpwd;
	int		pos;
	char	*tmp;

	oldpwd = ft_getpwd();
	pos = ft_findenv("OLDPWD", prompt);
	tmp = ft_strjoin("OLDPWD", "=");
	prompt->our_env[pos] = ft_strjoin(tmp, oldpwd);
	free(tmp);
}

static void	ft_cd2(char **args, t_prompt *prompt)
{
	char	*tmp;

	if (!ft_strcmp(args[1], "-") || !ft_strcmp(args[1], "~-"))
	{
		if (!ft_getenv("OLDPWD", prompt))
			ft_putendl_fd("OLDPWD not set", 2);
		tmp = prompt->our_env[ft_findenv("OLDPWD", prompt)] + 7;
		ft_oldpwd(prompt);
		chdir(tmp);
	}
	else
	{
		ft_oldpwd(prompt);
		tmp = ft_rmslash(args[1]);
		if (chdir(tmp) != 0)
			printf("minishell: cd: no such file or directory: %s\n", tmp);
		free(tmp);
	}
}

int	ft_cd(t_cmd *cmd, t_prompt *prompt)
{
	char	**args;

	args = cmd->args;
	if (ft_tablen(args) > 3)
		ft_putendl_fd("minishell: cd: too many arguments", 2);
	else if (ft_tablen(args) == 3)
		ft_cdirectory(args, prompt);
	else if (!args[1] || !ft_strcmp(args[1], "~") || !ft_strcmp(args[1], "--"))
	{
		if (!ft_getenv("HOME", prompt))
			ft_putendl_fd("minishell: cd: HOME not set", 2);
		ft_oldpwd(prompt);
		chdir(ft_getenv("HOME", prompt));
	}
	else
		ft_cd2(args, prompt);
	return (1);
}

int	ft_echo(t_cmd *cmd)
{
	int		i;
	char	**args;

	args = cmd->args;
	if (!args[1])
		return (1);
	i = 0;
	if (args[1] && ft_n(args[1]))
		i = 1;
	while (args[++i])
	{
		ft_putstr_fd(args[i], STDOUT);
		if (args[i + 1])
			write(1, " ", 1);
	}
	if (!ft_n(args[1]))
		ft_putstr_fd("\n", STDOUT);
	return (1);
}
