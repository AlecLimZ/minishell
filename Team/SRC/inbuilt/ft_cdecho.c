/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cdecho.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:08:21 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/08 23:53:21 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cdirectory2(char **args, char *pwd)
{
	char	*fpwd;
	char	*tmp;

	tmp = args[1];
	if (ft_strchr(args[1], '\\'))
		tmp = ft_rmslash(args[1]);
	if (!ft_strnstr(pwd, tmp, ft_strlen(pwd)))
	{
		printf("minishell: cd: string not in pwd: %s\n", tmp);
		g_ret = ERROR;
	}
	else
	{
		fpwd = ft_strjoin(ft_getparentdir(pwd, tmp), args[2]);
		if (chdir(fpwd) != 0)
		{
			printf("minishell: cd: no such file or directory: %s\n", fpwd);
			g_ret = ERROR;
		}
		free(fpwd);
	}
	if (ft_strchr(args[1], '\\'))
		free(tmp);
}

void	ft_cdirectory(char **args, t_prompt *prompt)
{
	char	*pwd;
	char	*dir;
	char	*tmp;
	char	**arr;

	pwd = ft_getpwd();
	if (args[1][ft_strlen(args[1]) - 1] == '\\')
	{
		arr = ft_split(args[1], '\\');
		tmp = ft_strjoin(arr[0], " ");
		dir = ft_strcat(tmp, args[2]);
		ft_oldpwd(prompt);
		if (chdir(dir) != 0)
		{
			printf("minishell: cd: no such file or directory: %s\n", dir);
			g_ret = ERROR;
		}
		free(tmp);
		free(arr[0]);
		free(arr);
	}
	else
		ft_cdirectory2(args, pwd);
}

static void	ft_cd2(char **args, t_prompt *prompt)
{
	char	*tmp;

	if (!ft_strcmp(args[1], "-") || !ft_strcmp(args[1], "~-"))
	{
		if (!ft_getenv("OLDPWD", prompt))
		{
			ft_putendl_fd("OLDPWD not set", 2);
			g_ret = ERROR;
		}
		tmp = prompt->our_env[ft_findenv("OLDPWD", prompt)] + 7;
		ft_oldpwd(prompt);
		chdir(tmp);
	}
	else
	{
		ft_oldpwd(prompt);
		tmp = ft_rmslash(args[1]);
		if (chdir(tmp) != 0)
		{
			printf("minishell: cd: no such file or directory: %s\n", tmp);
			g_ret = ERROR;
		}
		free(tmp);
	}
}

int	ft_cd(t_cmd *cmd, t_prompt *prompt)
{
	char	**args;

	args = cmd->args;
	g_ret = SUCCESS;
	if (ft_tablen(args) > 3)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		g_ret = ERROR;
	}
	else if (ft_tablen(args) == 3)
		ft_cdirectory(args, prompt);
	else if (!args[1] || !ft_strcmp(args[1], "~") || !ft_strcmp(args[1], "--"))
	{
		if (!ft_getenv("HOME", prompt))
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			g_ret = ERROR;
		}
		ft_oldpwd(prompt);
		chdir(ft_getenv("HOME", prompt));
	}
	else
		ft_cd2(args, prompt);
	return (g_ret);
}

int	ft_echo(t_cmd *cmd)
{
	int		i;
	char	**args;

	g_ret = SUCCESS;
	args = cmd->args;
	if (!args[1])
		return (g_ret);
	i = 1;
	if (args[1] && ft_n(args[1]))
		while (i < ft_tablen(args) && ft_n(args[i]) != 0)
			i++;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT);
		if (ft_strlen(args[i]) && args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!ft_n(args[1]))
		ft_putstr_fd("\n", STDOUT);
	return (g_ret);
}
