/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:15:11 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/04 16:59:54 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALEC_H
# define ALEC_H

# include "minishell.h"
# include "yeejin.h"

typedef struct s_prompt	t_prompt;
typedef struct s_cmd	t_cmd;

/*ft_inbuilts.c*/
int		ft_is_built(t_cmd *cmd);
int		ft_inbuilt(t_cmd *cmd, t_prompt *prompt);
void	ft_exit(t_prompt *prompt);
int		ft_pwd(char **args);
int		ft_env(char **args, t_prompt *prompt);

/*ft_export.c*/
int		ft_is_envar(char **env, char *tmp);
void	ft_replace_val(char **env, char **tmp);
char	**ft_create(t_prompt *prompt, char *args);
void	ft_newexport(t_prompt *prompt, char **tmp, char *args);
int		ft_export(t_cmd *cmd, t_prompt *prompt);

/*ft_cdecho*/
int		ft_cd(t_cmd *cmd, t_prompt *prompt);
int		ft_echo(t_cmd *cmd);
void	ft_cdirectory(char **args, t_prompt *prompt);

/*ft_unset.c*/
int		ft_unset(t_cmd *cmd, t_prompt *prompt);
char	**ft_delenv(int index, t_prompt *prompt);
int		ft_findenv(char *env, t_prompt *prompt);

/*ft_path*/
char	*ft_conc(char *path, char *filename);
char	**ft_get_path(t_prompt *prompt);
char	*ft_getpwd(void);
char	*ft_rmslash(char *s);
char	*ft_getparentdir(char *string, char *sub);

/*ft_create*/
int		ft_char(void);
char	*ft_create_file(void);
void	ft_oldpwd(t_prompt *prompt);
char	*ft_geteof(t_cmd *cmd);

/*ft_heredoc*/
char	*if_env(char *str, char *s, int *cur, t_prompt *prompt);
char	*if_no_env(char *str, char *s, int *cur);
int		ft_launch_heredoc(t_cmd *cmd, t_prompt *prompt);
int		ft_write_infd(int fd, t_cmd *cmd, t_prompt *prompt);
char	*ft_expanded(char *str, t_prompt *prompt);

/*ft_get_env.c*/
char	*ft_get_envp(int *cur, char *str, t_prompt *prompt);
int		ft_env_len(char *str);
char	*ft_alloc(int *cur);
char	*ft_getenv(char *s, t_prompt *prompt);

/*extra1.c*/
void	ft_free_split(char **s);
int		ft_tablen(char **s);
int		ft_getcharpos(char *str, char c);
int		ft_envcount(t_prompt *prompt);
char	**ft_realloc_env(int size, t_prompt *prompt);

/*extra2.c*/
void	ft_free_array(char **array);
char	*ft_strcat(char *s1, const char *s2);
char	*ft_freestr(char *s);
char	*ft_stringenv(char *s, char *tmp, int *cur, t_prompt *prompt);
char	*ft_strncpy(char *dst, const char *src, size_t len);

/*extra3.c*/
int		ft_strcmp(const char *s1, const char *s2);
void	ft_delete_toen(void *arg);
int		ft_n(char *s);
int		ft_exportcheck(char **args, t_prompt *prompt);
#endif
