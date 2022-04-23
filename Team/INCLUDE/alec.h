/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <leng-chu@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:15:11 by leng-chu          #+#    #+#             */
/*   Updated: 2022/04/23 17:52:10 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALEC_H
# define ALEC_H

# include "minishell.h"

/*ft_inbuilts.c*/
int	ft_is_built(char *cmd, t_prompt *prompt);
int	ft_exit(t_prompt *prompt);
int	ft_pwd(t_prompt *prompt);
int	ft_env(t_prompt *prompt);

/*ft_export.c*/
int		ft_is_envar(char **env, char *tmp);
void	ft_replace_val(char **env, char **tmp);
char	**ft_create(t_prompt *prompt, char *args);
void	ft_newexport(t_prompt *prompt, char **tmp, char *args);
int		ft_export(t_prompt *prompt);

/*ft_cdecho*/
int		ft_cd(t_prompt *prompt);
int		ft_echo(t_prompt *prompt);

/*ft_unset.c*/
int		ft_unset(t_prompt *prompt);
char	**ft_delenv(int index, t_prompt *prompt);
int		ft_findenv(char *env, t_prompt *prompt);

/*utils.c*/
void	ft_free_split(char *s);
int		ft_tablen(char **s);
int		ft_getcharpos(char *str, char c);
int		ft_envcount(t_prompt *prompt);
char	**ft_realloc_env(int size, t_prompt *prompt);

/*utlis2.c*/
void	ft_free_array(char **array);

#endif
