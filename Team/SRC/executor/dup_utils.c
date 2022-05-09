/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 14:19:17 by yang              #+#    #+#             */
/*   Updated: 2022/05/09 16:48:58 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_n_close(int fd, int fd_dup)
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

void	exit_status(int err, char *err_msg, t_prompt *prompt)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd("\n", 2);
	clean_up(prompt, prompt->total_cmds - 1, 2);
	ft_free_split(prompt->our_env);
	g_ret = err;
//	printf("g_ret: %d\n", g_ret);
//	system("leaks minishell");
	exit(err);
}
