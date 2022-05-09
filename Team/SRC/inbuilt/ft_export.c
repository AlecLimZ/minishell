/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:08:32 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/09 23:24:15 by yang             ###   ########.fr       */
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

void	ft_replace_val(t_prompt *prompt, char **tmp)
{
	int		i;
	char	*tmp2;
	t_list	*envp;

	i = -1;
	envp = prompt->envp;
	while (envp != NULL)
	{
		if (!ft_strncmp(envp->content, tmp[0], ft_strlen(tmp[0])))
		{
			if (tmp && envp->content)
			{
				tmp2 = ft_strjoin(tmp[0], "=");
				free(envp->content);
				if (!tmp[1])
					envp->content = ft_strdup(tmp2);
				else
					envp->content = ft_strjoin(tmp2, tmp[1]);
				free(tmp2);
			}
		}
		envp = envp->next;
	}
}

char	**ft_create(char **array, char *args)
{
	char	**tmp;
	int		i;

	i = -1;
	if (!array || !args)
		return (NULL);
	tmp = (char **)malloc(sizeof(char *)
			* (ft_tablen(array) + 2));
	if (!tmp)
		return (NULL);
	while (array[++i])
		tmp[i] = ft_strdup(array[i]);
	tmp[i] = ft_strdup(args);
	tmp[++i] = NULL;
	return (tmp);
}

void	ft_newexport(t_prompt *prompt, char **tmp, char *args)
{
	char	**array;

	array = set_envp(prompt);
	ft_free_split(tmp);
	tmp = ft_create(array, args);
	clean_up(prompt, prompt->total_cmds - 1, 2);
	init_env(prompt, tmp);
	ft_free_split(array);
}

int	ft_export(t_cmd *cmd, t_prompt *prompt)
{
	int		i;
	char	**tmp;
	char	**args;

	args = cmd->args;
	tmp = NULL;
	g_ret = SUCCESS;
	if (!ft_exportcheck(args, prompt))
		return (g_ret);
	i = 0;
	while (args[++i])
	{
		tmp = ft_split(args[i], '=');
		if (ft_findenv(tmp[0], prompt))
		{
			ft_replace_val(prompt, tmp);
			free_double_ptr(tmp, false);
			//ft_free_split(tmp);
		}
		else
			ft_newexport(prompt, tmp, args[i]);
	}
	i = 0;
	return (g_ret);
}
