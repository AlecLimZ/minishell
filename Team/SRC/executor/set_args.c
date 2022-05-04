/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 18:39:10 by yang              #+#    #+#             */
/*   Updated: 2022/05/04 19:24:02 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "alec.h"

int	set_args(t_cmd *cmd, t_list *token)
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
	if (!i)
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
	args[++i] = 0;
	cmd->args = args;
	return (1);
}

void	set_envp(t_prompt *prompt)
{
	t_list	*head;
	int		i;

	i = 0;
	head = prompt->envp;
	while (head)
	{
		i++;
		head = head->next;
	}
	prompt->env = (char **)malloc(sizeof(char *) * (i + 1));
	head = prompt->envp;
	i = -1;
	while (head)
	{
		prompt->env[++i] = ft_strdup(head->content);
		head = head->next;
	}
	prompt->env[++i] = 0;
}
