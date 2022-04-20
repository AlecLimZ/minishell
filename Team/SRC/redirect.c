/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 17:19:18 by yang              #+#    #+#             */
/*   Updated: 2022/04/20 11:58:58 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "yeejin.h"

void	redirect(t_cmd *cmd, char *fd, int type)
{
	if (type == LESS)
		cmd->infile = open(fd, O_RDONLY);
	//else if (type == LESSLESS)
		// heredoc
	else if (type == GREAT)
		cmd->outfile = open(fd, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == GREATGREAT)
		cmd->outfile = open(fd, O_CREAT | O_WRONLY | O_APPEND, 0644);
}
