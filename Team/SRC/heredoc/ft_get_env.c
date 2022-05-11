/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:12:24 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/10 10:44:36 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

// line:29 return need to modify for exit status
char	*ft_get_envp(int *cur, char *str, t_prompt *prompt)
{
	int		len;
	char	*cpy;
	char	*env;

	cpy = NULL;
	len = ft_env_len(str);
	if (!len)
		return (ft_alloc(cur));
	if (len == 1 && str[1] == '?')
	{
		*cur = *cur + 2;
		return (NULL);
	}
	cpy = malloc(sizeof(char) * (len + 1));
	if (cpy == NULL)
		return (NULL);
	cpy = ft_strncpy(cpy, str + 1, len);
	env = ft_genvp(cpy, prompt);
	free(cpy);
	if (!env)
		return (NULL);
	*cur = *cur + len + 1;
	cpy = ft_strdup(env);
	return (cpy);
}

int	ft_env_len(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '$')
		str++;
	if (str[0] && str[0] == '?')
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

char	*ft_alloc(int *cur)
{
	char	*new;

	*cur = *cur + 1;
	new = malloc(sizeof(char) * 2);
	if (new)
	{
		new[0] = '$';
		new[1] = '\0';
		return (new);
	}
	return (NULL);
}

//char	*ft_getenv(char *s, t_prompt *prompt)
//{
//	int	pos;
//	int	sign;
//
//	pos = ft_findenv(s, prompt);
//	if (pos != -1)
//	{
//		sign = ft_getcharpos(prompt->our_env[pos], '=');
//		return (prompt->our_env[pos] + (sign + 1));
//	}
//	else
//		return (NULL);
//}

char	*ft_getenvword(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '$' && s[i] != ' ')
		i++;
	return (ft_substr(s, 0, i));
}
