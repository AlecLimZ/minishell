/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:03:22 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/11 19:26:50 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

void	ft_checkslash(char **s)
{
	char	*tmp;
	char	*new;

	new = NULL;
	tmp = *s;
	if (ft_strchr(tmp, '\\'))
	{
		new = ft_rmslash(tmp);
		free(tmp);
		*s = new;
	}
}

int	ft_isnum(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_home(t_prompt *prompt)
{
	char	*tmp;

	tmp = ft_genvp("HOME", prompt);
	if (!tmp)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		g_ret = ERROR;
	}
	ft_oldpwd(prompt);
	chdir(tmp);
	free(tmp);
}
