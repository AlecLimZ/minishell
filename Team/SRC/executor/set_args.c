/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 18:39:10 by yang              #+#    #+#             */
/*   Updated: 2022/05/19 09:40:31 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_args(t_cmd *cmd, t_list *token)
{
	t_list	*head;
	char	**args;
	int		i;

	head = token;
	i = 0;
	while (head && head->type < 3)
	{
		i++;
		head = head->next;
	}
	if (!i || (i == 1 && !token->content))
		return (0);
	args = (char **)malloc(sizeof(char *) * (i + 1));
	head = token;
	i = -1;
	while (head && head->type < 3)
	{
		if (head->content)
			args[++i] = ft_strdup(head->content);
		head = head->next;
	}
	args[++i] = NULL;
	cmd->args = args;
	return (i);
}

char	**set_envp(t_prompt *prompt)
{
	t_list	*head;
	char	**env;
	int		i;

	i = 0;
	head = prompt->envp;
	while (head)
	{
		i++;
		head = head->next;
	}
	env = (char **)malloc(sizeof(char *) * (i + 1));
	head = prompt->envp;
	i = -1;
	while (head)
	{
		env[++i] = ft_strdup(head->content);
		head = head->next;
	}
	env[++i] = 0;
	return (env);
}

int	set_cmd(t_cmd *cmd, t_prompt *prompt)
{
	t_list	*head;
	int		redir;
	int		command;

	command = set_args(cmd, cmd->token);
	head = cmd->token;
	while (head != NULL && head->type < 3)
		head = head->next;
	cmd->infile = STDIN;
	cmd->outfile = STDOUT;
	while (head != NULL)
	{
		redir = redirect(cmd, head->content, head->type, prompt);
		head = head->next;
	}
	if (cmd->infile < 0 || cmd->outfile < 0)
		g_ret = 1;
	if (!command)
		return (0);
	return (1);
}
