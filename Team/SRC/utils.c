/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <leng-chu@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 20:55:42 by leng-chu          #+#    #+#             */
/*   Updated: 2022/04/23 15:29:46 by leng-chu         ###   ########.fr       */
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
		free(s);
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
	char	*ch;

	ch = ft_strchr(str, c);
	if (!ch)
		return (-1);
	return (ch - str);
}

int	ft_envcount(t_prompt *prompt)
{
	int	count;

	count = 0;
	while (prompt->enviroment[count])
		count++;
	return (count);
}

char	**ft_realloc_env(int size, t_prompt *prompt)
{
	char	**new;
	int		i;

	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (prompt->environment[i] && i < size)
	{
		new[i] = ft_strdup(prompt->environment[i]);
		i++;
	}
	new[size] = '\0';
	ft_free_array(prompt->environment[i]);
	return (new);
}
