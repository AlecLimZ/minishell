/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:45:09 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/07 19:13:54 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_delete_token(void *arg)
{
	t_list	*token;

	if (!arg)
		return ;
	token = (t_list *)arg;
	free(token->content);
	free(token);
	token = NULL;
}

int	ft_n(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-')
	{
		while (s[++i] == 'n')
			;
		if (s[i] == '\0')
			return (1);
	}
	return (0);
}

int	ft_exportcheck(char **args, t_prompt *prompt)
{
	char	**tmp;

	if ((ft_tablen(args) == 1) || !ft_strcmp(args[1], "") || args[1][0] == '=')
	{
		tmp = ft_split(args[1], '=');
		if ((ft_tablen(args) == 1) || (ft_strcmp(args[1], "") == 0))
			ft_env(args, prompt);
		else if (ft_strcmp(args[1], "=") == 0)
			ft_putendl_fd("minishell: bad assigment", 2);
		else if (args[1][0] == '=')
		{
			printf("minishell: %s not found\n", tmp[0]);
			g_ret = ERROR;
		}
		ft_free_split(tmp);
		return (0);
	}
	if (!ft_exportcheck2(args))
		return (0);
	return (1);
}

int	ft_getexit(t_cmd *cmds)
{
	char	**args;
	int		i;

	i = -1;
	g_ret = 0;
	args = cmds->args;
	if (ft_tablen(args) < 2)
		return (1);
	else if (ft_tablen(args) > 2)
	{
		g_ret = -1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (0);
	}
	while (args[1] && args[1][++i])
		if (!ft_isdigit(args[1][i]))
			g_ret = -1;
	if (g_ret != -1)
		g_ret = ft_atoi(args[1]);
	return (1);
}
