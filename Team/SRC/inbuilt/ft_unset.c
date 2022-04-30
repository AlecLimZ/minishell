/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 22:32:42 by leng-chu          #+#    #+#             */
/*   Updated: 2022/04/30 18:00:10 by leng-chu         ###   ########.fr       */
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
	while (prompt->our_env[++i])
	{
		index = ft_getcharpos(prompt->our_env[i], '=');
		sub = ft_substr(prompt->our_env[i], 0, index);
		if (sub)
		{
			if (!ft_strcmp(sub, env))
			{
				free(sub);
				return (i);
			}
			free(sub);
		}
	}
	return (-1);
}

char	**ft_delenv(int index, t_prompt *prompt)
{
	char	**tmp;
	int		i;
//	int		size;

	i = index;
	free(prompt->our_env[i]);
	prompt->our_env[i] = NULL;
	tmp = prompt->our_env;
//	size = ft_envcount(prompt);
//	while (prompt->our_env[i + 1])
//	{
//		tmp = ft_strdup(prompt->our_env[i + 1]);
//		free(prompt->our_env[i]);
//		prompt->our_env[i] = tmp;
//		i++;
//	}
//	return (ft_realloc_env((size - 1), prompt));
	return (tmp);
}

int	ft_unset(t_cmd *cmd, t_prompt *prompt)
{
	int		i;
	int		pos;
	char	**args;

	i = 0;
	args = cmd->args;
	if (!args[1])
		return (1);
	while (args[++i])
	{
		pos = ft_findenv(args[i], prompt);
		if (pos != -1)
		{
			if (prompt->our_env[pos])
				prompt->our_env = ft_delenv(pos, prompt);
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
