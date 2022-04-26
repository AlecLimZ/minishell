/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cdecho.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <leng-chu@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:08:21 by leng-chu          #+#    #+#             */
/*   Updated: 2022/04/26 14:55:56 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_prompt *prompt)
{
	char	**args;

	args = prompt->cmds[0].args;
	if (args[2])
		ft_putstr_fd("minishell: cd: too many arguments", 2);
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

int	ft_echo(t_prompt *prompt)
{
	int		i;
	char	**args;

	args = prompt->cmds[0].args;
	if (!args[1])
		return (1);
	i = 0;
	if (args[1] && !ft_strcmp(args[1], "-n"))
		i = 1;
	while (args[++i])
		printf("%s ", args[i]);
	if (ft_strcmp(args[1], "-n"))
		printf("\n");
	return (1);
}
