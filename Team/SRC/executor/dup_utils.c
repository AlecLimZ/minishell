/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 14:19:17 by yang              #+#    #+#             */
/*   Updated: 2022/05/19 13:17:41 by yang             ###   ########.fr       */
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

void	save_stdout_stdin(int save[2], int stage)
{
	if (stage == 0)
	{
		save[0] = dup(0);
		save[1] = dup(1);
	}
	else if (stage == 1)
	{
		dup2(save[0], 0);
		dup2(save[1], 1);
	}
	else if (stage == 2)
	{
		close(save[0]);
		close(save[1]);
	}
}
