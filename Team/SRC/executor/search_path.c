/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:44:25 by yang              #+#    #+#             */
/*   Updated: 2022/05/04 19:33:54 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	next_path(char **search, char **file)
{
	char	*found;

	*file = NULL;
	if (*search == NULL)
		return (false);
	found = ft_strchr(*search, ':');
	if (found)
	{
		*file = ft_strndup(*search, found - *search);
		*search = found + 1;
	}
	else
	{
		*file = ft_strdup(*search);
		*search = NULL;
	}
	return (true);
}

char	*search_path(char *path, char *command)
{
	char		*search;
	char		*file;
	char		*temp;
	struct stat	st;

	search = ft_strdup(path);
	while (next_path(&search, &file))
	{
		if (*file)
		{
			temp = ft_strjoin(file, "/");
			free(file);
			file = ft_strjoin(temp, command);
			free(temp);
			if (stat(file, &st) == 0 && S_ISREG(st.st_mode))
				return (file);
			free(file);
		}
	}
	return (NULL);
}
