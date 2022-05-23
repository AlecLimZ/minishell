/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:29:03 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/17 14:22:08 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_genvp(char *env, t_prompt *prompt)
{
	int		index;
	t_list	*envp;
	char	*name;
	char	*str;

	envp = prompt->envp;
	if (!env)
		return (NULL);
	while (envp != NULL)
	{
		index = ft_getcharpos(envp->content, '=');
		name = ft_substr(envp->content, 0, index);
		if (name && !ft_strcmp(name, env))
		{
			free(name);
			str = ft_substr(envp->content, index + 1, ft_strlen(envp->content));
			return (str);
		}
		free(name);
		envp = envp->next;
	}
	return (NULL);
}
