/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:54:47 by leng-chu          #+#    #+#             */
/*   Updated: 2022/04/21 13:27:45 by yang             ###   ########.fr       */
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
# include <fcntl.h>
# include "libft.h"
# include "yeejin.h"

# define BRED "\033[1;31m"
# define GRN "\e[0;32m"
# define BLU "\e[0;34m"
# define YEL "\e[0;33m"
# define BYEL "\e[1;33m"
# define WHT "\033[0;37m"
# define MAXCOM 1000
# define MAX 100
//# define SPACE	32

enum	e_token_type
{
	COMMAND = 1,
	ARGUMENT,
	LESS,
	LESSLESS,
	GREAT,
	GREATGREAT,
};

struct s_prompt
{
	t_list			*envp;
	char			**environment;
	struct s_cmd	*cmds;
	int				total_cmds;
};

struct s_cmd
{
	t_list	*token;
	char	**args;
	int		infile;
	int		outfile;
};

#endif
