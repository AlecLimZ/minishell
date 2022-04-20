/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 09:27:37 by yang              #+#    #+#             */
/*   Updated: 2022/04/20 15:27:43 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "yeejin.h"

void	set_cmd(t_cmd *cmd)
{
	t_list	*head;

	set_args(cmd, cmd->token);
	head = cmd->token;
	while (head != NULL && head->type < 3)
		head = head->next;
	if (head == NULL)
	{
		cmd->infile = STDIN;
		cmd->outfile = STDOUT;
	}
	while (head != NULL)
	{
		redirect(cmd, head->content, head->type);
		head = head->next;
	}
}

void	set_file(t_prompt *prompt, t_cmd *cmd, int i, int pipefd[2])
{
	if (i == 0 && cmd->outfile == STDOUT)
		cmd->outfile = pipefd[1];
	else if (i == prompt->total_cmd - 1 && cmd->infile == STDIN)
		cmd->infile = pipefd[0];
	else
	{
		if (cmd->infile == STDIN)
			cmd->infile = pipefd[1];
		if (cmd->outfile == STDOUT)
			cmd->outfile = pipefd[0];
	}
}

void	exec_cmd(t_prompt *prompt, t_cmd *cmd)
{

}

void	pipe_cmd(t_prompt *prompt, t_cmd *cmd, int pipefd[2])
{
	int	pid = fork();
	if (pid)
	{
		close(pipefd[1]);
		dup2(cmd->infile, STDIN);
		close(cmd->infile);
		waitpid(pid, NULL, 0);
	}
	else
	{
		close(pipefd[0]);
		dup2(cmd->outfile, STDOUT);
		close(cmd->outfile);
		// execute args
	}
	
}

void	exec_args(t_prompt *prompt)
{
	int	i;
	int	pipefd[2];

	i = -1;
	while (++i < prompt->total_cmd)
	{
		set_cmd(&prompt->cmds[i]); // set args and open infile outfile
		/* set file to its priority infile and outfile */
		set_file(prompt, &prompt->cmds[i], i, pipefd);
		/* pipe and execve */
		pipe_cmd(prompt, &prompt->cmds[i], pipefd);

	}
}