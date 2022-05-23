/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 17:19:18 by yang              #+#    #+#             */
/*   Updated: 2022/05/19 09:21:06 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect(t_cmd *cmd, char *fd, int type, t_prompt *prompt)
{
	if (type == LESS && cmd->infile >= 0)
	{
		if (cmd->infile != STDIN)
			close(cmd->infile);
		cmd->infile = open(fd, O_RDONLY);
		if (cmd->infile < 0)
			printf("minishell: %s: No such file or directory\n", fd);
	}
	else if (type == LESSLESS)
		cmd->infile = ft_launch_heredoc(cmd, prompt);
	else if ((type == GREAT || type == GREATGREAT)
		&& cmd->infile >= 0)
	{
		if (cmd->outfile != STDOUT)
			close(cmd->outfile);
		if (type == GREAT)
			cmd->outfile = open(fd, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (type == GREATGREAT)
			cmd->outfile = open(fd, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	if (cmd->infile < 0 || cmd->outfile < 0)
		return (-1);
	return (0);
}
