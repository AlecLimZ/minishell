/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yeejin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:50:34 by yang              #+#    #+#             */
/*   Updated: 2022/04/27 15:29:23 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef YEEJIN_H
# define YEEJIN_H

# include "minishell.h"
# include "alec.h"
# define STDOUT 1
# define STDIN 0

typedef struct	s_prompt t_prompt;
typedef struct	s_cmd t_cmd;

/* ------------ PARSER ------------- */
int		count(char *str, char c);
char	**ft_split_str(char *str, char c);
int		get_cmds(t_prompt *prompt, char *str);
int		parser(t_prompt *prompt, char *str);
void 	expand_token(t_prompt *prompt);
int		set_token_redirection(t_cmd *cmd, char **token, int i);
void	set_token_type(t_list *new, int i);

int		check_pipe(char *str);
int		is_operator_in_str(char *str);
int		in_quote(char *str, int i);
int		is_space(char c);
int		is_operator(char c);
int		is_quote(char c);
int 	is_env(char c);
int		get_pos(char *str, char c);
void	free_malloc(char **array);

void	print_cmds(t_prompt *prompt);
void	remove_quotes(t_list *lst);
void	set_args(t_cmd *cmd, t_list *token);
void	set_envp(t_prompt *prompt);
int		redirect(t_cmd *cmd, char *fd, int type);

/* ----------- expand_utils.c -------- */
int		is_name(char *str);
int		get_env_pos(char *str);
char	*get_prefix(char *str, int i);
char	*get_postfix(char *str, int i);

void	exec_args(t_prompt *prompt);
char	*search_path(char *path, char *command);

#endif
