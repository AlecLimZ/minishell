/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:45:09 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/16 11:52:07 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_delete_token(void *arg)
{
	t_list	*token;

	if (!arg)
		return ;
	token = (t_list *)arg;
	free(token->content);
	free(token);
	token = NULL;
}

int	ft_n(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-')
	{
		while (s[++i] == 'n')
			;
		if (s[i] == '\0')
			return (1);
	}
	return (0);
}

int	ft_exportcheck(char **args, char *str, t_prompt *prompt, int c)
{
	if (!ft_strchr(str, '=') && !ft_ispecialexp(str))
		return (0);
	else if (c == 1 && ft_strlen(str) == 1 && ft_ispecialexp(str))
	{
		g_ret = ERROR;
		printf("minishell: export: '%s' not a valid identifier\n", str);
		return (0);
	}
	if ((str[0] != '_' && !ft_isalpha(str[0]))
		|| !ft_strcmp(str, "``"))
	{
		g_ret = ERROR;
		if (c == 1 && !ft_strcmp(str, "``"))
			ft_env(args, prompt);
		else if (str[0] == '-')
			g_ret = 2;
		else if (ft_isdigit(str[0]) || ft_ispecialexp(str))
			printf("minishell: export: '%s': not a valid identifier\n", str);
		return (0);
	}
	if (ft_exportcheck2(str) == 0)
		return (0);
	return (1);
}

int	ft_getexit(t_cmd *cmds)
{
	char	**args;
	int		i;

	i = -1;
	g_ret = 0;
	args = cmds->args;
	if (ft_tablen(args) < 2)
		return (1);
	else if (!ft_isnum(args[1]) || ft_strlen(args[1]) > 19)
	{
		g_ret = 255;
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		return (1);
	}
	if (args[1][0] == '+' || args[1][0] == '-')
		i++;
	while (args[1] && args[1][++i])
		if (!ft_isdigit(args[1][i]))
			g_ret = -1;
	if (g_ret != -1)
		g_ret = ft_atoi(args[1]);
	printf("exit\n");
	return (1);
}
