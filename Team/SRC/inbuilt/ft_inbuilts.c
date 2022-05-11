/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inbuilts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:22:38 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/11 18:39:13 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

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
		return ft_exit(prompt);
	g_ret = NOCMD;
	return (g_ret);
}

//	line 53		ft_lstdelone(tmp, ft_delete_token);
int	ft_exit(t_prompt *prompt)
{
	t_list	*token;
	t_list	*tmp;
	int		i;
	int		j;

	i = -1;
	if (!ft_getexit(prompt->cmds))
		return (g_ret);
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
	exit(g_ret);
}

int	ft_pwd(char **args)
{
	char	*pwd;
	char	dest[4222];

	pwd = ft_getpwd();
	ft_strlcpy(dest, pwd, ft_strlen(pwd) + 1);
	g_ret = SUCCESS;
	if (ft_tablen(args) > 1)
	{
		ft_putendl_fd("minishell: pwd: too many arguments", STDERR);
		g_ret = ERROR;
	}
	else if (pwd)
		ft_putendl_fd(dest, STDOUT);
	else
	{
		ft_putendl_fd("minishell: pwd: error", STDERR);
		g_ret = ERROR;
	}
	return (g_ret);
}

int	ft_env(char **args, t_prompt *prompt)
{
	t_list	*envp;

	envp = prompt->envp;
	g_ret = SUCCESS;
	if (args[1] && ft_strcmp(args[1], "") && ft_strcmp(args[1], "``"))
	{
		ft_putstr_fd("minishell: env: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		g_ret = NOCMD;
		return (g_ret);
	}
	while (envp != NULL)
	{
		if (!ft_strcmp(args[0], "export"))
			ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(envp->content, 1);
		envp = envp->next;
	}
	if (!ft_strcmp(args[0], "export") && ft_findenv("OLDPWD", prompt) == -1)
		printf("declare -x OLDPWD\n");
	g_ret = SUCCESS;
	return (g_ret);
}
