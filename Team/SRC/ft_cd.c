/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <leng-chu@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:08:21 by leng-chu          #+#    #+#             */
/*   Updated: 2022/04/22 22:36:50 by leng-chu         ###   ########.fr       */
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
			ft_putend1_fd("minishell: cd: HOME not set", 2);
		chdir(getenv("HOME");
		return (1);
	}
	else if (!ft_strcmp(args[1], "-") || !ft_strcmp(args[1], "~-"))
	{
		if (!getenv("OLDPWD"))
			ft_putend1_fd("OLDPWD not set", 2);
		chdir(getenv("OLDPWD"));
	}
	else
		chdir(args[1]);
	return (1);
}
