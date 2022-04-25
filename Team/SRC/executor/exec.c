/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 09:27:37 by yang              #+#    #+#             */
/*   Updated: 2022/04/25 19:31:30 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "yeejin.h"

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

void	pipe_cmd(t_prompt *prompt, int i, int pipefd[2], int keep_fd)
{
	t_cmd	*cmd;

	if (prompt->total_cmds > 1)
	{
		cmd = &prompt->cmds[i];
		//printf("infile: %d\t outfile: %d\n", cmd->infile, cmd->outfile);
		if (i == 0 || (i > 0 && i < prompt->total_cmds - 1))
			close(pipefd[0]);
		else if (i == prompt->total_cmds - 1)
			close(pipefd[1]);
		if (cmd->infile != STDIN)
				dup_n_close(cmd->infile, 0);
		if (cmd->outfile != STDOUT)
				dup_n_close(cmd->outfile, 1);			
		if (i > 0 && cmd->infile == STDIN)
		{
			// if (cmd->infile != STDIN)
			// 	dup_n_close(cmd->infile, 0);
			// else
				dup_n_close(keep_fd, 0);
		}
		if (i < prompt->total_cmds - 1 && cmd->outfile == STDOUT)
		{
			// if (cmd->outfile != STDOUT)
			// 	dup_n_close(cmd->outfile, 1);
			// else
				dup_n_close(pipefd[1], 1);
		}
	}
}

int do_exec_cmd(char **argv, t_prompt *prompt)
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
		do_exec_cmd(cmd->args, prompt);
	}
	else
	{
		if (prompt->total_cmds > 1)
		{
			if (i < prompt->total_cmds - 1)
			{
				close(pipefd[1]);
				if (i != 0)
					close(keep_fd);
				keep_fd = pipefd[0];
			}
			else
				close(keep_fd);
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
		// if (prompt->cmds[i].infile != STDIN)
		// 	dup_n_close(prompt->cmds[i].infile, STDIN);
		// if (prompt->cmds[i].outfile != STDOUT)
		// 	dup_n_close(prompt->cmds[i].outfile, STDOUT);
		// printf("infile: %d\t outfile: %d\n", prompt->cmds[i].infile, prompt->cmds[i].outfile);
		execute(prompt, &prompt->cmds[i], i, pipefd);

	}
}