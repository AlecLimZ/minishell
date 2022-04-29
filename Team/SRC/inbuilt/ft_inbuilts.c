/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inbuilts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:22:38 by leng-chu          #+#    #+#             */
/*   Updated: 2022/04/29 21:28:23 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_built(t_cmd *cmd)
{
	char	**args;
	int		len;

	args = cmd->args;
	len = ft_strlen(args[0]);
	if ((!ft_strncmp(args[0], "echo", 4) && len == 4) ||
		(!ft_strncmp(args[0], "cd", 2) && len == 2) ||
		(!ft_strncmp(args[0], "pwd", 3) && len == 3) ||
		(!ft_strncmp(args[0], "export", 6) && len == 6) ||
		(!ft_strncmp(args[0], "unset", 5) && len == 5) ||
		(!ft_strncmp(args[0], "env", 3) && len == 3) ||
		(!ft_strncmp(args[0], "exit", 4) && len == 4))
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
		return (ft_cd(cmd));
	else if (!ft_strncmp(args[0], "pwd", 3) && len == 3)
		return (ft_pwd());
	else if (!ft_strncmp(args[0], "export", 6) && len == 6)
		return (ft_export(cmd, prompt));
	else if (!ft_strncmp(args[0], "unset", 5) && len == 5)
		return (ft_unset(prompt));
	else if (!ft_strncmp(args[0], "env", 3) && len == 3)
		return (ft_env(prompt));
	else if (!ft_strncmp(args[0], "exit", 4) && len == 4)
		return (ft_exit(prompt));
	return (0);
}

//	line 53		ft_lstdelone(tmp, ft_delete_token);
int	ft_exit(t_prompt *prompt)
{
	t_list	*token;
	t_list	*tmp;
	int		i;
	int		j;

	i = -1;
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
	exit(0);
}

int	ft_pwd(void)
{
	char	buf[4222];

	if (getcwd(buf, sizeof(buf)) != NULL)
		ft_putendl_fd(buf, STDOUT);
	else
		ft_putendl_fd("pwd: error\n", STDERR);
	return (1);
}

int	ft_env(t_prompt *prompt)
{
	int	i;

	i = -1;
	while (prompt->our_env[++i])
		ft_putendl_fd(prompt->our_env[i], 1);
	return (1);
}
