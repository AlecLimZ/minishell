/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:38:20 by yang              #+#    #+#             */
/*   Updated: 2022/05/02 15:48:54 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_double_ptr(char **argv, bool error)
{
	int	i;

	i = -1;
	while (argv[++i] != NULL)
		free(argv[i]);
	free(argv[i]);
	free(argv);
	if (error)
		return (-1);
	else
		return (0);
}

void	free_lst(t_list **lst)
{
	t_list	*head;
	t_list	*tmp;

	head = *lst;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->content);
		tmp->content = NULL;
		free(tmp);
		tmp = NULL;
	}
}

int	clean_up(t_prompt *prompt, int total, int stage)
{
	(void)stage;
	int	i;

	i = -1;
	if (stage == 1)
	{
		free_lst(&prompt->envp);
		free(prompt);
	}
	if (stage == 2 && total >= 0) 
	{
		while (++i <= total)
			free_lst(&prompt->cmds[i].token);
		free(prompt->cmds);
	}
	return (-1);
}

void	close_file(t_cmd *cmd)
{
	if (cmd->infile != STDIN)
		close(cmd->infile);
	if (cmd->outfile != STDOUT)
		close(cmd->outfile);
}
