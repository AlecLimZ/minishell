/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 19:06:27 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/10 10:44:33 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

char	*ft_dollar(char *str, char *nstr, int *i, t_prompt *prompt)
{
	int		s;
	char	*str2;
	char	*sub;
	char	*tmp;

	s = 0;
	str2 = (str + 1);
	while (str2[*i + s] != ' ' && str2[*i + s] != '$' && str2[*i + s] != '\0')
		s++;
	sub = ft_substr(str, *i + 1, s);
	tmp = ft_strdup(ft_genvp(sub, prompt));
	free(sub);
	if (nstr == NULL)
		nstr = ft_strjoin("", tmp);
	else
	{
		str2 = nstr;
		nstr = ft_strjoin(str2, tmp);
		free(str2);
	}
	free(tmp);
	*i += (s + 1);
	return (nstr);
}

char	*ft_nodollar(char *str, char *nstr, int *i)
{
	int		s;
	char	*sub;
	char	*str2;

	s = *i;
	while (str[s] != '$' && str[s] != '\0')
		s++;
	sub = ft_substr(str, *i, (s - (*i)));
	if (nstr == NULL)
		nstr = ft_strjoin("", sub);
	else
	{
		str2 = nstr;
		nstr = ft_strjoin(str2, sub);
		free(str2);
	}
	free(sub);
	*i = s;
	return (nstr);
}
