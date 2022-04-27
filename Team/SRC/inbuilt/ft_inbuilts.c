/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inbuilts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <leng-chu@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:22:38 by leng-chu          #+#    #+#             */
/*   Updated: 2022/04/27 15:57:01 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_built(t_cmd *cmd, t_prompt *prompt)
{
	char	**argv;

	argv = cmd->args;
	if (!ft_strncmp(argv[0], "echo", 4))
		return (ft_echo(cmd));
	if (!ft_strncmp(argv[0], "cd", 2) && ft_strlen(argv[0]) == 2)
		return (ft_cd(prompt));
	if (!ft_strncmp(argv[0], "pwd", 3) && ft_strlen(argv[0]) == 3)
		return (ft_pwd());
	if (!ft_strncmp(argv[0], "export", 6) && ft_strlen(argv[0]) == 6)
		return (ft_export(prompt));
	if (!ft_strncmp(argv[0], "unset", 5) && ft_strlen(argv[0]) == 5)
		return (ft_unset(prompt));
	if (!ft_strncmp(argv[0], "env", 3) && ft_strlen(argv[0]) == 3)
		return (ft_env(prompt));
	if (!ft_strncmp(argv[0], "exit", 4) && ft_strlen(argv[0]) == 4)
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
	printf("exit\n");
	exit(0);
}

int	ft_pwd(void)
{
	char	*buf;

	buf = NULL;
	getcwd(buf, 2000);
	ft_putendl_fd(buf, STDOUT);
	return (1);
}

int	ft_env(t_prompt *prompt)
{
	int	i;

	i = -1;
	while (prompt->env[++i])
		ft_putendl_fd(prompt->env[i], 1);
	return (1);
}
