/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 09:27:37 by yang              #+#    #+#             */
/*   Updated: 2022/05/06 19:13:55 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	set_cmd(t_cmd *cmd, t_prompt *prompt)
// {
// 	t_list	*head;
// 	int		redir;

// 	if (!set_args(cmd, cmd->token))
// 		return (0);
// 	head = cmd->token;
// 	while (head != NULL && head->type < 3)
// 		head = head->next;
// 	cmd->infile = STDIN;
// 	cmd->outfile = STDOUT;
// 	while (head != NULL)
// 	{
// 		redir = redirect(cmd, head->content, head->type, prompt);
// 		if (redir < 0)
// 			return (0);
// 		head = head->next;
// 	}
// 	return (1);
// }

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

	if (ft_strchr(argv[0], '/'))
	{
		if (stat(argv[0], &st) == 0 && S_ISREG(st.st_mode))
			execve(argv[0], argv, prompt->env);
		else if (S_ISDIR(st.st_mode))
			exit_status(126, "is a directory", prompt);
		else
			exit_status(127, "No such file or directory", prompt);
	}
	else
	{
		path = search_path(ft_getenv("PATH", prompt), argv[0]);
		if (!path)
			exit_status(127, "command not found", prompt);
		execve(path, argv, prompt->env);
	}
	return (0);
}

// Previous code: having malloc problem for fork
// static void	exec_child(t_prompt *prompt, t_cmd *cmd)
// {
// 	if (ft_is_built(cmd)) && ft_inbuilt(cmd, prompt))
// 	{
// 		exit_status(1, "", prompt);
// 	}
// 	else
// 	{
// 		printf("entering execute command\n");
// 		do_exec_cmd(cmd->args, prompt);
// 	}
// }

static void	exec_child(t_prompt *prompt, t_cmd *cmd)
{
	if (ft_is_built(cmd))
	{
		printf("is built in\n");
		g_ret = ft_inbuilt(cmd, prompt);
		printf("cmd->token: %p\t cmd->args: %p\n", cmd->token, cmd->args);
		exit(g_ret);
	}
	else
		do_exec_cmd(cmd->args, prompt);
}

static void	execute(t_prompt *prompt, t_cmd *cmd, int i, int pipefd[2])
{
	int			pid;
	static int	keep_fd;
	int			status;

	pid = fork();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (pid == 0)
	{
		printf("******* Child Process ********\n");
		printf("pid: %d\n", getpid());
		pipe_cmd(prompt, i, pipefd, keep_fd);
		exec_child(prompt, cmd);
	}
	else
	{
		waitpid(pid, &status, 0);
		printf("******* Parent Process ********\n");
		printf("pid: %d\n", getpid());
		printf("cmd->token: %p\t cmd->args: %p\n", cmd->token, cmd->args);
		if (prompt->total_cmds > 1)
		{
			if (i > 0)
				close(keep_fd);
			close(pipefd[1]);
			keep_fd = pipefd[0];
		}
		if (WIFEXITED(status))
			g_ret = WEXITSTATUS(status);
	}
}

int	exec_args(t_prompt *prompt)
{
	int		i;
	t_cmd	*cmd;
	int		pipefd[2];
	int		save_stdout;

	i = -1;
	save_stdout = dup(1);
	while (++i < prompt->total_cmds)
	{
		cmd = &prompt->cmds[i];
		if (!set_cmd(cmd, prompt))
			return (0);
		if (prompt->total_cmds > 1 && i < prompt->total_cmds - 1)
			pipe(pipefd);
		if (prompt->total_cmds == 1 && ft_is_built(cmd))
		{
			ft_inbuilt(cmd, prompt);
			dup2(save_stdout, 1);
			close(save_stdout);
		}
		else
			execute(prompt, &prompt->cmds[i], i, pipefd);
	}
	return (1);
}
