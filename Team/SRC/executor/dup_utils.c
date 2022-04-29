/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 14:19:17 by yang              #+#    #+#             */
/*   Updated: 2022/04/29 14:19:50 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
