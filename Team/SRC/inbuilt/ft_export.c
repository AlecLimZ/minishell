/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:08:32 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/17 14:21:27 by yang             ###   ########.fr       */
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
	char	*tmp2;
	t_list	*envp;

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

void	ft_newexport(t_prompt *prompt, char *args)
{
	t_list	*envp;
	t_list	*new;

	envp = prompt->envp;
	new = ft_lstnew(args);
	ft_lstadd_back(&envp, new);
}

int	ft_export(t_cmd *cmd, t_prompt *prompt)
{
	int		i;
	char	**tmp;
	char	**args;

	args = cmd->args;
	tmp = NULL;
	i = 0;
	g_ret = SUCCESS;
	if (ft_tablen(args) == 1 || args[1][0] == '#')
		ft_env(args, prompt);
	while (args[++i] != NULL && i < ft_tablen(args) && args[1][0] != '#')
	{
		if (!ft_exportcheck(args, args[i], prompt, i))
			continue ;
		tmp = ft_split(args[i], '=');
		if (ft_findenv(tmp[0], prompt) != -1)
			ft_replace_val(prompt, tmp);
		else
			ft_newexport(prompt, args[i]);
		free_double_ptr(tmp, false);
	}
	return (g_ret);
}
