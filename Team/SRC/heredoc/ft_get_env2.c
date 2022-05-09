/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:29:03 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/09 19:45:01 by leng-chu         ###   ########.fr       */
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
			str = ft_substr(envp->content, index, ft_strlen(envp->content));
			return (str);
		}
		free(name);
		envp = envp->next;
	}
	return (NULL);
}
