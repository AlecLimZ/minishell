/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:54:47 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/10 00:33:06 by jacklearn        ###   ########.fr       */
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
# include <sys/stat.h>
# include <stdbool.h>
# include <termios.h>
# include "libft.h"
# include "yeejin.h"
# include "alec.h"

# define DEF "\033[0m"
# define BRED "\033[1;31m"
# define GRN "\e[0;32m"
# define BLU "\e[0;34m"
# define YEL "\e[0;33m"
# define BYEL "\e[1;33m"
# define WHT "\033[0;37m"
# define MAXCOM 1000
# define MAX 100

// NOCMD is for 
// 1. no command found
// 2. no such file or directory from env's 2nd parameter
# define SUCCESS 0
# define ERROR 1
# define NOCMD 127
# define CTRLC 130

int	g_ret;

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

/*main.c*/
int	init_env(t_prompt *prompt, char *envp[]);

#endif
