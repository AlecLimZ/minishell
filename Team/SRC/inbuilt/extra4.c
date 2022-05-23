/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:03:22 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/17 14:21:13 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_runscript(char *argv, char **envp, t_prompt *prompt)
{
	if (!prompt)
		return (0);
	ft_memset(prompt, 0, sizeof(t_prompt));
	init_env(prompt, envp);
	if (argv)
	{
		if (parser(prompt, argv) == -1)
		{
			g_ret = 2;
			ft_putendl_fd("minishellL: syntax error", 2);
			return (g_ret);
		}
		exec_args(prompt);
		clean_up(prompt, prompt->total_cmds - 1, 2);
	}
	return (g_ret);
}

int	ft_parenthesis(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
		{
			if (args[i][j] == '(')
			{
				ft_putendl_fd("minishell: pwd: syntax error \
near unexpected token '('", STDERR);
				return (1);
			}
			else if (args[i][j] == ')')
			{
				ft_putendl_fd("minishell: pwd: syntax error \
near unexpected token ')'", STDERR);
				return (1);
			}
		}
	}
	return (0);
}
