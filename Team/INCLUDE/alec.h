/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <leng-chu@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:15:11 by leng-chu          #+#    #+#             */
/*   Updated: 2022/04/22 21:51:04 by leng-chu         ###   ########.fr       */
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

/*ft_cd*/
int		ft_cd(t_prompt *prompt);

/*utils.c*/
void	ft_free_split(char *s);
int		ft_tablen(char **s);
#endif
