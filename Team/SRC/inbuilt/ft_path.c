/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:10:08 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/16 18:19:03 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

char	*ft_conc(char *path, char *filename)
{
	char	*bin;

	bin = (char *)malloc(ft_strlen(path) + ft_strlen(filename) + 16);
	ft_strcat(bin, path);
	ft_strcat(bin, "/");
	ft_strcat(bin, filename);
	return (bin);
}

char	*ft_getpwd(void)
{
	char	pwd[4222];
	char	*s;

	ft_memset(pwd, 0, sizeof(pwd));
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
		while (sub[j] && string[i + j] == sub[j])
			j++;
		if (sub[j] == '\0')
			pos = i;
	}
	string[pos] = '\0';
	return (string);
}

int	ft_ispecialexp(char *s)
{
	int	i;

	i = -1;
	while (s[++i] != '\0')
		if (!ft_isalnum(s[i]) && s[i] != '_' && s[i] != '=')
			return (1);
	return (0);
}
