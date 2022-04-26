/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <leng-chu@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:10:08 by leng-chu          #+#    #+#             */
/*   Updated: 2022/04/26 17:32:36 by leng-chu         ###   ########.fr       */
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
	while (prompt->environment[i])
	{
		if (ft_strcmp(prompt->environment[i], "PATH") == 0)
		{
			p = prompt->environment[i];
			p += 5;
			path = ft_split(p, ':');
			break ;
		}
		else
			i++;
	}
	return (path);
}

/*
void	ft_exec(t_prompt *prompt)
{
	char 	**path;
	char 	*buf;
	int		i;

	i = 0;
	path = ft_get_path(prompt->environment);
	while (path[i])
	{
		buf = ft_conc(path[i], prompt->cmds[0].args[0]);
		if (execve(buf, argv, envp) != -1)
			break ;
		else
			i++;
	}
	if (i >= 0)
		ft_putendl_fd("Could not find command\n", 2);
}
*/
