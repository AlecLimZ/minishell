/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 18:39:10 by yang              #+#    #+#             */
/*   Updated: 2022/04/25 14:36:29 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "yeejin.h"

void	set_args(t_cmd *cmd, t_list *token)
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
	// if (!i)
	// 	return (0);
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
}
