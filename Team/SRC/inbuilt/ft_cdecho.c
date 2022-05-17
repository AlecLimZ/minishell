/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cdecho.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:08:21 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/17 14:21:20 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cdirectory2(char **args)
{
	char	*tmp;

	tmp = args[1];
	if (ft_strchr(args[1], '\\'))
		tmp = ft_rmslash(args[1]);
	if (chdir(tmp) != 0)
	{
		printf("minishell: cd: %s no such file or directory\n", tmp);
		g_ret = ERROR;
	}
	if (ft_strchr(args[1], '\\'))
		free(tmp);
}

void	ft_cdirectory(char **args, t_prompt *prompt)
{
	char	*pwd;
	char	*dir;
	char	*tmp;
	char	*arr;

	pwd = ft_getpwd();
	ft_oldpwd(prompt);
	if (args[1][ft_strlen(args[1]) - 1] == '\\')
	{
		arr = ft_rmslash(args[1]);
		tmp = ft_strjoin(arr, " ");
		free(arr);
		dir = ft_strjoin(tmp, args[2]);
		if (chdir(dir) != 0)
		{
			printf("minishell: cd: %s: no such file or directory\n", dir);
			g_ret = ERROR;
		}
		free(tmp);
		free(dir);
	}
	else
		ft_cdirectory2(args);
}

static void	ft_cd2(char **args, t_prompt *prompt)
{
	char	*tmp;

	tmp = ft_genvp("OLDPWD", prompt);
	if (!tmp)
	{
		ft_putendl_fd("OLDPWD not set", 2);
		g_ret = ERROR;
		return ;
	}
	ft_oldpwd(prompt);
	if (!ft_strcmp(args[1], "-"))
		ft_putendl_fd(tmp, 1);
	chdir(tmp);
	free(tmp);
}

int	ft_cd(t_cmd *cmd, t_prompt *prompt)
{
	char	**args;
	char	*tmp;

	args = cmd->args;
	g_ret = SUCCESS;
	if (!args[1] || !ft_strcmp(args[1], "~") || !ft_strcmp(args[1], "--")
		|| args[1][0] == '#')
		ft_home(prompt);
	else if (ft_tablen(args) > 1 && args[1][0] != '-' && args[1][0] != '~')
		ft_cdirectory(args, prompt);
	else if (!ft_strcmp(args[1], "-") || !ft_strcmp(args[1], "~-"))
		ft_cd2(args, prompt);
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
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!ft_n(args[1]))
		ft_putstr_fd("\n", STDOUT);
	return (g_ret);
}
