/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:12:24 by leng-chu          #+#    #+#             */
/*   Updated: 2022/04/26 17:30:36 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// line:29 return need to modify for exit status
char	*ft_get_envp(int *cur, char *str)
{
	int		len;
	char	*cpy;
	char	*env;

	cpy = NULL;
	len = ft_env_len(str);
	if (!len)
		return (ft_alloc(cur));
	if (len == 1 && str[1] == '?')
	{
		*cur = *cur + 2;
		return (NULL);
	}
	cpy = malloc(sizeof(char) * (len + 1));
	if (cpy == NULL)
		return (NULL);
	cpy = ft_strncpy(cpy, str + 1, len);
	env = getenv(cpy);
	free(cpy);
	if (!env)
		return (NULL);
	*cur = *cur + len + 1;
	cpy = ft_strdup(env);
	return (cpy);
}

int	ft_env_len(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '$')
		str++;
	if (str[0] && str[0] == '?')
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

char	*ft_alloc(int *cur)
{
	char	*new;

	*cur = *cur + 1;
	new = malloc(sizeof(char) * 2);
	if (new)
	{
		new[0] = '$';
		new[1] = '\0';
		return (new);
	}
	return (NULL);
}