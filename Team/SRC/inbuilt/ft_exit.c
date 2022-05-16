/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:47:58 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/16 19:03:19 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exitclean(t_prompt *prompt)
{
	t_list	*token;
	t_list	*tmp;
	int		i;
	int		j;

	i = -1;
	while (++i < prompt->total_cmds)
	{
		j = -1;
		while (prompt->cmds[i].args[++j])
			free(prompt->cmds[i].args[j]);
		token = prompt->cmds[i].token;
		while (token != NULL)
		{
			tmp = token;
			token = token->next;
			free(tmp->content);
			free(tmp);
			tmp = NULL;
		}
	}
}

int	ft_exit(t_prompt *prompt)
{
	char			**args;
	int				i;

	i = -1;
	args = prompt->cmds->args;
	if (!ft_getexit(prompt->cmds))
		return (g_ret);
	if (args[1] && (args[1][0] == '+' || args[1][0] == '-'))
		i++;
	while (args[1] && args[1][++i] && args[1][0] != '#')
		if (!ft_isdigit(args[1][i]))
			g_ret = -1;
	if (g_ret != -1 && ft_tablen(args) > 1
		&& (((unsigned long)ft_atoi(args[1]) < 9223372036854775808U
				&& args[1][0] != '-') || args[1][0] == '-'))
		g_ret = ft_atoi(args[1]);
	ft_exitclean(prompt);
	exit(g_ret);
}

static void	ft_slash2(char ***str)
{
	char	*new;

	new = ft_rmslash(**str);
	free(**str);
	**str = new;
}

void	ft_chkslash(char **str)
{
	char	**tmp;
	char	*new;
	char	*join;

	if (ft_strchr(*str, '\\') && !ft_strchr(*str, '='))
		ft_slash2(&str);
	else if (ft_strchr(*str, '\\') && ft_strchr(*str, '='))
	{
		tmp = ft_split(*str, '=');
		new = ft_rmslash(tmp[0]);
		join = ft_strjoin(new, "=");
		free(new);
		free(*str);
		if (tmp[1])
		{
			*str = ft_strjoin(join, tmp[1]);
			free(join);
		}
		else
			*str = join;
		free_double_ptr(tmp, false);
	}
}
