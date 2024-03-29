/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:15:11 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/16 18:42:50 by leng-chu         ###   ########.fr       */
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
int		ft_pwd(char **args);
int		ft_env(char **args, t_prompt *prompt);

/*ft_export.c*/
int		ft_is_envar(char **env, char *tmp);
void	ft_replace_val(t_prompt *prompt, char **tmp);
char	**ft_create(char **array, char *args);
void	ft_newexport(t_prompt *prompt, char *args);
int		ft_export(t_cmd *cmd, t_prompt *prompt);

/*ft_cdecho*/
int		ft_cd(t_cmd *cmd, t_prompt *prompt);
int		ft_echo(t_cmd *cmd);
void	ft_cdirectory(char **args, t_prompt *prompt);

/*ft_unset.c*/
int		ft_unset(t_cmd *cmd, t_prompt *prompt);
int		ft_findenv(char *env, t_prompt *prompt);
void	ft_freeourenvp(t_prompt *prompt);
int		ft_ispecial(char *s);
void	ft_reterror(char *s);
int		ft_posenv(int pos, t_prompt *prompt);

/*ft_path*/
char	*ft_conc(char *path, char *filename);
char	*ft_getpwd(void);
char	*ft_rmslash(char *s);
char	*ft_getparentdir(char *string, char *sub);
int		ft_ispecialexp(char *s);

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
char	*ft_getenvword(char *s);

/*ft_get_env2.c*/
char	*ft_genvp(char *env, t_prompt *prompt);

/*ft_env2.c*/
char	*ft_dollar(char *str, char *nstr, int *i, t_prompt *prompt);
char	*ft_nodollar(char *str, char *nstr, int *i);

/*ft_exit*/
int		ft_exit(t_prompt *prompt);
void	ft_chkslash(char **str);

/*extra1.c*/
void	ft_free_split(char **s);
int		ft_tablen(char **s);
int		ft_getcharpos(char *str, char c);
int		ft_envcount(t_prompt *prompt);
int		ft_exportcheck2(char *str);

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
int		ft_exportcheck(char **args, char *str, t_prompt *prompt, int c);
int		ft_getexit(t_cmd *cmds);

/*extra4*/
void	ft_checkslash(char **s);
int		ft_isnum(char *s);
void	ft_home(t_prompt *prompt);
int		ft_runscript(char *argv, char **envp, t_prompt *prompt);
int		ft_parenthesis(char **args);

#endif
