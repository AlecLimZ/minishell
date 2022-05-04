/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <leng-chu@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:08:32 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/03 17:13:30 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_envar(char **env, char *tmp)
{
	int	i;

	i = -1;
	while (env && (env[++i]))
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
	if (!prompt->our_env || !args)
		return (NULL);
	tmp = (char **)malloc(sizeof(char *)
			* (ft_tablen(prompt->our_env) + 2));
	if (!tmp)
		return (NULL);
	while (prompt->our_env[++i])
		tmp[i] = ft_strdup(prompt->our_env[i]);
	tmp[i] = ft_strdup(args);
	tmp[++i] = NULL;
	return (tmp);
}

/*	ft_free_split(tmp);
	tmp = ft_create(prompt, args);
	ft_free_split(prompt->our_env);
	prompt->our_env = tmp;*/
void	ft_newexport(t_prompt *prompt, char **tmp, char *args)
{
	tmp = ft_create(prompt, args);
	prompt->our_env = tmp;
}

//		ft_free_split(tmp) after replace;
//	ft_free_split(args) before return ;
int	ft_export(t_cmd *cmd, t_prompt *prompt)
{
	int		i;
	char	**tmp;
	char	**args;

	args = cmd->args;
	tmp = NULL;
	if (!ft_exportcheck(args, prompt))
		return (1);
	i = 0;
	while (args[++i])
	{
		tmp = ft_split(args[i], '=');
		if (ft_is_envar(prompt->our_env, tmp[0]))
			ft_replace_val(prompt->our_env, tmp);
		else
			ft_newexport(prompt, tmp, args[i]);
	}
	return (1);
}
