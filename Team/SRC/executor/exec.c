/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 09:27:37 by yang              #+#    #+#             */
/*   Updated: 2022/04/27 17:08:02 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_cmd(t_cmd *cmd)
{
	t_list	*head;
	int		redir;

	set_args(cmd, cmd->token);
	head = cmd->token;
	while (head != NULL && head->type < 3)
		head = head->next;
	// if (head == NULL)
	// {
	cmd->infile = STDIN;
	cmd->outfile = STDOUT;
	//}
	while (head != NULL)
	{
		redir = redirect(cmd, head->content, head->type);
		if (redir < 0)
			return ;
		head = head->next;
	}
}

void	dup_n_close(int	fd, int fd_dup)
{
	dup2(fd, fd_dup);
	close(fd);
}

void	dup_infile_outfile(t_cmd *cmd)
{
	if (cmd->infile != STDIN)
		dup_n_close(cmd->infile, STDIN);
	if (cmd->outfile != STDOUT)
		dup_n_close(cmd->outfile, STDOUT);
}

void	pipe_cmd(t_prompt *prompt, int i, int pipefd[2], int keep_fd)
{
	t_cmd	*cmd;

	cmd = &prompt->cmds[i];
	dup_infile_outfile(cmd);
	if (prompt->total_cmds > 1)
	{
		if (i >= 0 && i < prompt->total_cmds - 1)
		{
			close(pipefd[0]);
			if (i > 0)
			{
				if (cmd->infile == STDIN)
					dup_n_close(keep_fd, STDIN);
			}
			if (cmd->outfile == STDOUT)
				dup_n_close(pipefd[1], STDOUT);
		}
		if (i == prompt->total_cmds - 1)
		{
			if (cmd->infile == STDIN)
				dup_n_close(keep_fd, STDIN);
		}
	}
}

int do_exec_cmd(char **argv, t_prompt *prompt) //include build in here
{
	char		*path;
	struct stat	st;

	if (ft_strchr(argv[0], '/'))
	{
		if (stat(argv[0], &st) == 0 && S_ISREG(st.st_mode))
			execve(argv[0], argv, prompt->env);
		else if (S_ISDIR(st.st_mode))
			printf("is a directory\n");
		else
			printf("Incorrect command\n");
	}
	else
	{
		/* check if command is build in */
		path = search_path(getenv("PATH"), argv[0]);
		if (!path)
			return (0);
		execve(path, argv, prompt->env);
		free(path);
	}
	return (0);
}

void	execute(t_prompt *prompt, t_cmd *cmd, int i, int pipefd[2])
{
	int			pid;
	static int	keep_fd;

	pid = fork();
	if (pid == 0)
	{
		pipe_cmd(prompt, i, pipefd, keep_fd);
		//if (ft_is_built(cmd, prompt));
		//else
			do_exec_cmd(cmd->args, prompt); //check user input is relative path or command
	}
	else
	{
		if (prompt->total_cmds > 1)
		{
			if (i > 0)
				close(keep_fd);
			close(pipefd[1]);
			keep_fd = pipefd[0];
		}
		waitpid(pid, NULL, 0);
	}	
}

void	exec_args(t_prompt *prompt)
{
	int	i;
	int	pipefd[2];

	i = -1;
	while (++i < prompt->total_cmds)
	{
		set_cmd(&prompt->cmds[i]); // set args and open infile outfile
		/* pipe and execve */
		if (prompt->total_cmds > 1 && i < prompt->total_cmds - 1)
			pipe(pipefd);
		execute(prompt, &prompt->cmds[i], i, pipefd);
	}
}
