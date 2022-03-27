/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:54:47 by leng-chu          #+#    #+#             */
/*   Updated: 2022/03/28 01:01:46 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include "../SRC/libft/libft.h"

# define MAXCOM 1000

typedef struct s_prompt
{
	char				**envp;
	struct s_command	*command;
}	t_prompt;

typedef struct s_command
{
	char	**full_cmd;
	int		infile;
	int		outfile;
}	t_command;

#endif
