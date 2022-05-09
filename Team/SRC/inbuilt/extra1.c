/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <leng-chu@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 20:55:42 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/09 13:45:47 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_split(char **s)
{
	int	i;

	i = -1;
	if (!s)
		return ;
	while (s[++i])
		free(s[i]);
	free(s);
}

int	ft_tablen(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	ft_getcharpos(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			break ;
	return (i);
}

int	ft_envcount(t_prompt *prompt)
{
	int	count;

	count = 0;
	while (prompt->our_env[count])
		count++;
	return (count);
}

int	ft_exportcheck2(char **args)
{
	char	**tmp;

	if (args[2] && args[2][0] == '=')
	{
		printf("minishell: %s not found\n", args[2]);
		g_ret = ERROR;
		return (0);
	}
	if (ft_isdigit(args[1][0]))
	{
		tmp = ft_split(args[1], '=');
		printf("minishell: export: not an identifier: %s\n", tmp[0]);
		ft_free_split(tmp);
		g_ret = ERROR;
		return (0);
	}
	return (1);
}
