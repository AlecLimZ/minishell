/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inbuilts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:22:38 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/07 18:03:41 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_built(t_cmd *cmd)
{
	char	**args;
	int		len;

	args = cmd->args;
	len = ft_strlen(args[0]);
	if ((!ft_strncmp(args[0], "echo", 4) && len == 4)
		|| (!ft_strncmp(args[0], "cd", 2) && len == 2)
		|| (!ft_strncmp(args[0], "pwd", 3) && len == 3)
		|| (!ft_strncmp(args[0], "export", 6) && len == 6)
		|| (!ft_strncmp(args[0], "unset", 5) && len == 5)
		|| (!ft_strncmp(args[0], "env", 3) && len == 3)
		|| (!ft_strncmp(args[0], "exit", 4) && len == 4))
		return (1);
	return (0);
}

int	ft_inbuilt(t_cmd *cmd, t_prompt *prompt)
{
	char	**args;
	int		len;

	args = cmd->args;
	len = ft_strlen(args[0]);
	if (prompt->total_cmds == 1)
		dup_infile_outfile(cmd);
	if (!ft_strncmp(args[0], "echo", 4) && len == 4)
		return (ft_echo(cmd));
	else if (!ft_strncmp(args[0], "cd", 2) && len == 2)
		return (ft_cd(cmd, prompt));
	else if (!ft_strncmp(args[0], "pwd", 3) && len == 3)
		return (ft_pwd(args));
	else if (!ft_strncmp(args[0], "export", 6) && len == 6)
		return (ft_export(cmd, prompt));
	else if (!ft_strncmp(args[0], "unset", 5) && len == 5)
		return (ft_unset(cmd, prompt));
	else if (!ft_strncmp(args[0], "env", 3) && len == 3)
		return (ft_env(args, prompt));
	else if (!ft_strncmp(args[0], "exit", 4) && len == 4)
		ft_exit(prompt);
	g_ret = NOCMD;
	return (g_ret);
}

//	line 53		ft_lstdelone(tmp, ft_delete_token);
void	ft_exit(t_prompt *prompt)
{
	t_list	*token;
	t_list	*tmp;
	int		i;
	int		j;

	i = -1;
	if (!ft_getexit(prompt->cmds))
		return ;
	while (++i < prompt->total_cmds)
	{
		j = -1;
		while (prompt->cmds[i].args[++j])
			free(prompt->cmds[i].args[j]);
		token = prompt->cmds[i].token;
		while (token != NULL)
		{
			tmp = token;
			token = token->next;
			free(tmp->content);
			free(tmp);
			tmp = NULL;
		}
	}
	ft_free_split(prompt->our_env);
	exit(g_ret);
}

int	ft_pwd(char **args)
{
	char	*pwd;

	pwd = ft_getpwd();
	g_ret = SUCCESS;
	if (ft_tablen(args) > 1)
	{
		ft_putendl_fd("minishell: pwd: too many arguments", STDERR);
		g_ret = ERROR;
	}
	else if (pwd)
		ft_putendl_fd(pwd, STDOUT);
	else
	{
		ft_putendl_fd("minishell: pwd: error", STDERR);
		g_ret = ERROR;
	}
	return (g_ret);
}

int	ft_env(char **args, t_prompt *prompt)
{
	int	i;

	i = -1;
	g_ret = SUCCESS;
	if (args[1] && ft_strcmp(args[1], "") != 0)
	{
		ft_putstr_fd("minishell: env: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		g_ret = NOCMD;
		return (g_ret);
	}
	while (prompt->our_env[++i] != NULL)
		ft_putendl_fd(prompt->our_env[i], 1);
	return (g_ret);
}
