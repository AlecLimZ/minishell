/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:54:47 by leng-chu          #+#    #+#             */
/*   Updated: 2022/04/06 13:55:57 by yang             ###   ########.fr       */
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
# define MAX 100

enum	token_type
{
	COMMAND = 1,
	ARGUMENT,
	LESS,
	LESSLESS,
	GREAT,
	GREATGREAT,
};

typedef struct s_prompt
{
	t_list			*envp;
	struct s_cmd	*cmds;
	int				total_cmds;
}	t_prompt;

typedef struct s_cmd
{
	t_list	*token;
}	t_cmd;


/* ------------ PARSER ------------- */
int		count(char *str, char c);
char	**ft_split_str(char *str, char c);
int		get_cmds(t_prompt *prompt, char *str);
int	parser(t_prompt *prompt, char *str);
void expand_token(t_prompt *prompt);
int	set_token_redirection(t_cmd *cmd, char **token, int i);
void	set_token_type(t_list *new, int i);

int	check_pipe(char *str);
int	in_quote(char *str, int i);
int	is_space(char c);
int	is_operator(char c);
int	is_quote(char c);
int is_env(char c);
int	get_pos(char *str, char c);
void	free_malloc(char **array);

#endif
