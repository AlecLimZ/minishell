/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 20:55:42 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/16 11:50:46 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

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
	int		count;
	t_list	*env;

	env = prompt->envp;
	count = 0;
	while (env != NULL)
	{
		env = env->next;
		count++;
	}
	return (count);
}

int	ft_exportcheck2(char *str)
{
	char	**tmp;

	tmp = NULL;
	if ((str[0] != '_' && ft_ispecialexp(str)) || str[0] == '-')
	{
		tmp = ft_split(str, '=');
		if (ft_ispecialexp(tmp[0]))
		{
			ft_reterror(str);
			printf("minishell: export: '%s': not a valid identifier\n", tmp[0]);
			free_double_ptr(tmp, false);
			return (0);
		}
		free_double_ptr(tmp, false);
	}
	return (1);
}
