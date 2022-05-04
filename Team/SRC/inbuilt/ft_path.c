/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <leng-chu@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:10:08 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/03 17:17:54 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_conc(char *path, char *filename)
{
	char	*bin;

	bin = (char *)malloc(ft_strlen(path) + ft_strlen(filename) + 16);
	ft_strcat(bin, path);
	ft_strcat(bin, "/");
	ft_strcat(bin, filename);
	return (bin);
}

char	**ft_get_path(t_prompt *prompt)
{
	int		i;
	char	*p;
	char	**path;

	i = 0;
	path = NULL;
	while (prompt->env[i])
	{
		if (ft_strcmp(prompt->env[i], "PATH") == 0)
		{
			p = prompt->env[i];
			p += 5;
			path = ft_split(p, ':');
			break ;
		}
		else
			i++;
	}
	return (path);
}

char	*ft_getpwd(void)
{
	char	pwd[4222];
	char	*s;

	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		s = pwd;
		return (s);
	}
	else
		return (NULL);
}

char	*ft_rmslash(char *s)
{
	int		i;
	int		j;
	char	*new;

	i = -1;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(s) + 1));
	while (s[++i])
	{
		if (s[i] != '\\')
			new[j++] = s[i];
	}
	new[j] = '\0';
	return (new);
}

char	*ft_getparentdir(char *string, char *sub)
{
	int	i;
	int	j;
	int	pos;

	i = -1;
	pos = -1;
	while (string[++i] && pos == -1)
	{
		j = 0;
		while (string[i + j] == sub[j])
			j++;
		if (sub[j] == '\0')
			pos = i;
	}
	string[pos] = '\0';
	return (string);
}
