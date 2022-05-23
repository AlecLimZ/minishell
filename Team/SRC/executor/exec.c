/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 09:27:37 by yang              #+#    #+#             */
/*   Updated: 2022/05/19 13:17:05 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_cmd(t_prompt *prompt, int i, int pipefd[2], int keep_fd)
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

static int	do_exec_cmd(char **argv, t_prompt *prompt)
{
	char		*path;
	struct stat	st;
	char		**envp;

	envp = set_envp(prompt);
	if (ft_strchr(argv[0], '/'))
	{
		if (stat(argv[0], &st) == 0 && S_ISREG(st.st_mode))
			execve(argv[0], argv, envp);
		else if (S_ISDIR(st.st_mode))
			exit_status(126, "is a directory", prompt);
		else
			exit_status(127, "No such file or directory", prompt);
	}
	else
	{
		path = search_path(ft_genvp("PATH", prompt), argv[0]);
		if (!path)
			exit_status(127, "command not found", prompt);
		execve(path, argv, envp);
	}
	return (0);
}

static void	exec_child(t_prompt *prompt, t_cmd *cmd)
{
	if (ft_is_built(cmd))
	{
		g_ret = ft_inbuilt(cmd, prompt);
		exit(g_ret);
	}
	else
		do_exec_cmd(cmd->args, prompt);
}

static int	execute(t_prompt *prompt, t_cmd *cmd, int i, int pipefd[2])
{
	int			pid;
	static int	keep_fd;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		pipe_cmd(prompt, i, pipefd, keep_fd);
		exec_child(prompt, cmd);
	}
	else if (pid)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		if (prompt->total_cmds > 1)
		{
			if (i > 0)
				close(keep_fd);
			close(pipefd[1]);
			keep_fd = pipefd[0];
		}
		return (pid);
	}
	return (pid);
}

// int	exec_args(t_prompt *prompt)
// {
// 	int		i;
// 	t_cmd	*cmd;
// 	int		pipefd[2];
// 	int		save_stdout;
// 	int		save_stdin;
// 	int		pid;

// 	i = -1;
// 	save_stdout = dup(1);
// 	save_stdin = dup(0);
// 	while (++i < prompt->total_cmds)
// 	{
// 		cmd = &prompt->cmds[i];
// 		if (!set_cmd(cmd, prompt))
// 			return (-1);
// 		if (prompt->total_cmds > 1 && i < prompt->total_cmds - 1)
// 			pipe(pipefd);
// 		if (prompt->total_cmds == 1 && ft_is_built(cmd) && cmd->infile >= 0)
// 		{
// 			ft_inbuilt(cmd, prompt);
// 			dup2(save_stdout, 1);
// 			dup2(save_stdin, 0);
// 		}
// 		else if (cmd->infile >= 0)
// 			pid = execute(prompt, &prompt->cmds[i], i, pipefd);
// 	}
// 	close(save_stdin);
// 	close(save_stdout);
// 	return (wait_exit_status(pid));
// }

int	exec_args(t_prompt *prompt)
{
	int		i;
	t_cmd	*cmd;
	int		pipefd[2];
	int		save[2];
	int		pid;

	i = -1;
	save_stdout_stdin(save, 0);
	while (++i < prompt->total_cmds)
	{
		cmd = &prompt->cmds[i];
		if (!set_cmd(cmd, prompt))
			return (-1);
		if (prompt->total_cmds > 1 && i < prompt->total_cmds - 1)
			pipe(pipefd);
		if (prompt->total_cmds == 1 && ft_is_built(cmd) && cmd->infile >= 0)
		{
			ft_inbuilt(cmd, prompt);
			save_stdout_stdin(save, 1);
		}
		else if (cmd->infile >= 0)
			pid = execute(prompt, &prompt->cmds[i], i, pipefd);
	}
	save_stdout_stdin(save, 2);
	return (wait_exit_status(pid));
}
