/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 22:32:42 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/10 13:28:29 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

int	ft_findenv(char *env, t_prompt *prompt)
{
	char	*sub;
	int		index;
	t_list	*envp;
	int		i;

	i = 0;
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
			return (i);
		}
		free(sub);
		envp = envp->next;
		i++;
	}
	return (-1);
}

static int	ft_posenv(int pos, int i, char **args, t_prompt *prompt)
{
	t_list	*envp;
	t_list	*tmp;
	int		j;

	j = 0;
	envp = prompt->envp;
	while (pos != -1 && envp != NULL)
	{
		if (j++ == pos - 1)
		{
			tmp = envp->next->next;
			free(envp->next->content);
			free(envp->next);
			envp->next = tmp;
			break ;
		}
		envp = envp->next;
	}
	if (pos == -1)
	{
		printf("minishell: unset: '%s': not a valid identifier\n", args[i]);
		g_ret = ERROR;
		return (0);
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
