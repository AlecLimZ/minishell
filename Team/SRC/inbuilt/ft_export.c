/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <leng-chu@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:08:32 by leng-chu          #+#    #+#             */
/*   Updated: 2022/04/26 14:58:12 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_envar(char **env, char *tmp)
{
	int	i;

	i = -1;
	while (env && env[++i])
		if (!ft_strncmp(env[i], tmp, ft_strlen(tmp)))
			return (1);
	return (0);
}

void	ft_replace_val(char **env, char **tmp)
{
	int		i;
	char	*tmp2;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], tmp[0], ft_strlen(tmp[0])))
		{
			if (tmp && env)
			{
				tmp2 = ft_strjoin(tmp[0], "=");
				free(env[i]);
				if (!tmp[1])
					env[i] = ft_strdup(tmp2);
				else
					env[i] = ft_strjoin(tmp2, tmp[1]);
				free(tmp2);
			}
		}
	}
}

char	**ft_create(t_prompt *prompt, char *args)
{
	char	**tmp;
	int		i;

	i = -1;
	if (!prompt->environment || !args)
		return (NULL);
	tmp = (char **)malloc(sizeof(char *) * (ft_tablen(prompt->environment) + 2));
	if (!tmp)
		return (NULL);
	while (prompt->environment[++i])
		tmp[i] = ft_strdup(prompt->environment[i]);
	tmp[i] = ft_strdup(args);
	tmp[++i] = NULL;
	return (tmp);
}

void	ft_newexport(t_prompt *prompt, char **tmp, char *args)
{
	ft_free_split(tmp);
	tmp = ft_create(prompt, args);
	ft_free_split(prompt->environment);
	prompt->environment = tmp;
}

int	ft_export(t_prompt *prompt)
{
	int	i;
	char	**tmp;
	char	**args;

	args = prompt->cmds[0].args;
	tmp = NULL;
	if (args[0] && args[1])
	{
		i = 0;
		while (args[++i])
		{
			tmp = ft_split(args[i], '=');
			if (ft_is_envar(prompt->environment, tmp[0]))
			{
				ft_replace_val(prompt->environment, tmp);
				ft_free_split(tmp);
			}
			else
				ft_newexport(prompt, tmp, args[i]);
		}
	}
	ft_free_split(args);
	return (1);
}
