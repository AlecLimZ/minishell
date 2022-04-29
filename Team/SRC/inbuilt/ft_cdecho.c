/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cdecho.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:08:21 by leng-chu          #+#    #+#             */
/*   Updated: 2022/04/29 21:14:51 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_cmd *cmd)
{
	char	**args;

	args = cmd->args;
	if (args[0] && args[1])
		ft_putendl_fd("minishell: cd: too many arguments", 2);
	else if (!args[1] || !ft_strcmp(args[1], "~") || !ft_strcmp(args[1], "--"))
	{
		if (!getenv("HOME"))
			ft_putendl_fd("minishell: cd: HOME not set", 2);
		chdir(getenv("HOME"));
		return (1);
	}
	else if (!ft_strcmp(args[1], "-") || !ft_strcmp(args[1], "~-"))
	{
		if (!getenv("OLDPWD"))
			ft_putendl_fd("OLDPWD not set", 2);
		chdir(getenv("OLDPWD"));
	}
	else
		chdir(args[1]);
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
	if (args[1] && ft_N(args[1]))
		i = 1;
	while (args[++i])
	{
		ft_putstr_fd(args[i], STDOUT);
		if (args[i + 1])
			write(1, " ", 1);
	}
	if (!ft_N(args[1]))
		ft_putstr_fd("\n", STDOUT);
	return (1);
}
