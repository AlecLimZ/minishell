/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <leng-chu@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 22:32:42 by leng-chu          #+#    #+#             */
/*   Updated: 2022/04/22 23:48:05 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_findenv(char *env, t_prompt *prompt)
{
	char	*sub;
	int		i;
	int		index;

	if (!env)
		return (0);
	i = -1;
	sub = NULL;
	while (prompt->enviroment[++i])
	{BB}
}

int	ft_unset(t_prompt *prompt)
{
	int	i;
	int	pos;
	int	args;

	i = 0;
	args = prompt->cmds[0].args;
	if (!args[1])
		return (1);
	while (args[++i])
	{
		pos = ft_findenv(args[i], prompt);
	}
}
