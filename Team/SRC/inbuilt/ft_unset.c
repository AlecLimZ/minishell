/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 22:32:42 by leng-chu          #+#    #+#             */
/*   Updated: 2022/04/26 15:27:57 by leng-chu         ###   ########.fr       */
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
	while (prompt->environment[++i])
	{
		if (ft_getcharpos(prompt->environment[i], '=') == -1)
			index = ft_strlen(prompt->environment[i]);
		sub = ft_substr(prompt->environment[i], 0, index);
		if (sub)
		{
			if (!ft_strcmp(sub, env))
			{
				free(sub);
				return (i);
			}
			free(sub);
		}
		i++;
	}
	return (-1);
}

char **ft_delenv(int index, t_prompt *prompt)
{
	char	*tmp;
	int		i;
	int		size;

	i = index;
	size = ft_envcount(prompt);
	while (prompt->environment[i + 1])
	{
		tmp = ft_strdup(prompt->environment[i + 1]);
		free(prompt->environment[i]);
		prompt->environment[i] = tmp;
		i++;
	}
	return (ft_realloc_env((size - 1), prompt));
}

int	ft_unset(t_prompt *prompt)
{
	int	i;
	int	pos;
	char	**args;

	i = 0;
	args = prompt->cmds[0].args;
	if (!args[1])
		return (1);
	while (args[++i])
	{
		pos = ft_findenv(args[i], prompt);
		if (pos != -1)
		{
			if (prompt->environment[i])
				prompt->environment = ft_delenv(pos, prompt);
		}
		else
		{
			ft_putstr_fd("minishell: unset: '", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
	}
	return (1);
}
