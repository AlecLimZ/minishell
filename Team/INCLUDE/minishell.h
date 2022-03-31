/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:54:47 by leng-chu          #+#    #+#             */
/*   Updated: 2022/03/29 18:24:12 by yang             ###   ########.fr       */
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
	struct s_cmd	*cmd;
	int					total_cmds;
}	t_prompt;

typedef struct s_cmd
{
	char	*full_cmd;
	char	**token;
	int		infile;
	int		outfile;
}	t_cmd;


/* ------------ PARSER ------------- */
int		in_quote(char *str, int i);
int		is_space(char c);
int		is_operator(char c);
int		parser(t_prompt *prompt, char *str);
int		total_cmds(char *str);
int		split_args_pipe(t_prompt *prompt, char *str);
int		total_token(char *str);
int		split_token(t_cmd *cmd, char *str);
void	operator_add_space(t_prompt *prompt);

#endif
