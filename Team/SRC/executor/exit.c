/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:42:32 by yang              #+#    #+#             */
/*   Updated: 2022/05/09 16:47:41 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status(int err, char *err_msg, t_prompt *prompt)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd("\n", 2);
	clean_up(prompt, prompt->total_cmds - 1, 2);
	ft_free_split(prompt->our_env);
	g_ret = err;
	// printf("g_ret: %d\n", g_ret);
	// system("leaks minishell");
	exit(err);
}

int	wait_exit_status(int last_pid)
{
	int	status;
	int	pid;

	while (true)
	{
		pid = wait(&status);
		if (pid == -1)
			break ;
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				g_ret = WEXITSTATUS(status);
		}
	}
	return (1);
}
