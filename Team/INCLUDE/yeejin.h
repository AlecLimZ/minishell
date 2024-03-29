/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yeejin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:50:34 by yang              #+#    #+#             */
/*   Updated: 2022/05/19 13:16:45 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef YEEJIN_H
# define YEEJIN_H

# include "minishell.h"
# include "alec.h"
# define STDERR	2
# define STDOUT	1
# define STDIN	0

typedef struct s_prompt	t_prompt;
typedef struct s_cmd	t_cmd;

/* --------------------------- PARSER ---------------------------- */
int		parser(t_prompt *prompt, char *str);
/* ----------- Check Pipe ----------- */
int		check_pipe(char *str);
int		err_msg(int err, char str[100]);
/* ----------- Clean Up ------------- */
int		free_double_ptr(char **argv, bool error);
void	free_lst(t_list **lst);
int		clean_up(t_prompt *prompt, int total, int stage);
/* ------------- Expand ------------- */
int		is_name(char *str);
int		get_env_pos(char *str, int pos);
int		need_expansion(char *str);
char	*get_prefix(char *str, int i);
char	*get_postfix(char *str, int *i);
// int		expand_token(t_prompt *prompt);
int		expand_token(char *src, t_list *head, t_cmd *cmd, t_prompt *prompt);
void	replace_expand_str(t_list *head, char *str);
int		var_expand(char *str, char **expand, t_prompt *prompt);
void	expand_n_remove_quote(t_prompt *prompt);
// char	*var_expand(char *str, int *pos, t_prompt *prompt);
/* ------------ Redirect ----------- */
int		set_token_redirection(t_cmd *cmd, char **token, int i);
int		is_operator_in_str(char *str);
void	set_token_type(t_list *new, int i);
/* ----------- Remove Quote -------- */
void	remove_quotes(t_list *lst);
/* ---------- Utils_Split ---------- */
int		count(char *str, char c);
char	**ft_split_str(char *str, char c);
/* --------------- Utils --------------- */
int		in_quote(char *str, int i);
int		is_space(char c);
int		is_operator(char c);
int		is_quote(char c);
int		is_env(char c);
int		get_file_len(char *str, int i);
int		get_redirection_type(char *str);

/* --------------------- EXECUTOR ------------------ */
/* ----------- dup utils ---------- */
void	dup_n_close(int fd, int fd_dup);
void	dup_infile_outfile(t_cmd *cmd);
void	exit_status(int err, char *err_msg, t_prompt *prompt);
int		wait_exit_status(int last_pid);
void	save_stdout_stdin(int save[2], int stage);
/* ----------- exec ------------ */
int		exec_args(t_prompt *prompt);
/* ---------- redirect ----------- */
int		redirect(t_cmd *cmd, char *fd, int type, t_prompt *prompt);
/* --------- search path ---------- */
char	*search_path(char *path, char *command);
/* ---------- set_args ----------- */
// int		set_args(t_cmd *cmd, t_list *token);
char	**set_envp(t_prompt *prompt);
int		set_cmd(t_cmd *cmd, t_prompt *prompt);

void	print_cmds(t_prompt *prompt);

#endif
