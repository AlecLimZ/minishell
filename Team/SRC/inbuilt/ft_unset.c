/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 22:32:42 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/10 10:45:26 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

int	ft_findenv(char *env, t_prompt *prompt)
{
	char	*sub;
	int		index;
	t_list	*envp;

	envp = prompt->envp;
	if (!env)
		return (0);
	while (envp != NULL)
	{
		index = ft_getcharpos(envp->content, '=');
		sub = ft_substr(envp->content, 0, index);
		if (sub && !ft_strcmp(sub, env))
		{
			free(sub);
			return (1);
		}
		free(sub);
		envp = envp->next;
	}
	return (-1);
}

static int	ft_posenv(int pos, int i, char **args, t_prompt *prompt)
{
	if (pos != -1)
		ft_lstdel_pos(&prompt->envp, pos);
	else
	{
		ft_putstr_fd("minishell: unset: '", 2);
		ft_putstr_fd(args[i], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_ret = ERROR;
		return (-1);
	}
	return (1);
}

int	ft_unset(t_cmd *cmd, t_prompt *prompt)
{
	int		i;
	int		pos;
	char	**args;

	i = 0;
	args = cmd->args;
	g_ret = SUCCESS;
	if (!args[1])
	{
		g_ret = ERROR;
		return (g_ret && printf("minishell: unset: not enough arguments\n"));
	}
	else if (!ft_isalpha(args[1][0]) && args[1][0] != '_')
	{
		g_ret = ERROR;
		printf("minishell: unset: %s: invalid parameter name\n", args[1]);
		return (g_ret);
	}
	while (args[++i])
	{
		pos = ft_findenv(args[i], prompt);
		if (!ft_posenv(pos, i, args, prompt))
			return (g_ret);
	}
	return (g_ret);
}
