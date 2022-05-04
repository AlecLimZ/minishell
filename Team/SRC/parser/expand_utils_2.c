/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:07:39 by yang              #+#    #+#             */
/*   Updated: 2022/05/04 19:38:40 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_path(char *prefix, char *postfix, char *path)
{
	char	*temp;
	char	*expand;

	temp = NULL;
	expand = NULL;
	if (!path)
	{
		if (!prefix && !postfix)
			return (NULL);
		else if (!prefix)
			return (ft_strjoin("", postfix));
		else if (!postfix)
			return (ft_strjoin(prefix, ""));
		else
			return (ft_strjoin(prefix, postfix));
	}
	if (!prefix)
		temp = path;
	else
		temp = ft_strjoin(prefix, path);
	if (!postfix)
		expand = ft_strdup(temp);
	else
		expand = ft_strjoin(temp, postfix);
	return (expand);
}

static char	*expand_str(char *str, int *pos, char *path)
{
	char	*expand;
	char	*prefix;
	char	*postfix;

	prefix = get_prefix(str, *pos);
	postfix = get_postfix(str, pos);
	expand = expand_path(prefix, postfix, path);
	free(prefix);
	prefix = NULL;
	free(postfix);
	postfix = NULL;
	return (expand);
}

static char	*var_expand_env(char *str, int *pos, t_prompt *prompt, int i)
{
	char	*expand;
	char	*temp;
	char	*path;

	temp = ft_strndup(str + *pos + 1, i - *pos);
	if (!is_name(temp))
	{
		if (ft_isdigit(temp[0]))
		{
			ft_memmove(&str[*pos], &str[*pos + 2], ft_strlen(str) - *pos + 2);
			expand = str;
			return (expand);
		}
		return (NULL);
	}
	else
	{
		path = ft_getenv(temp, prompt);
		free(temp);
		temp = NULL;
		expand = expand_str(str, pos, path);
	}
	return (expand);
}

char	*var_expand(char *str, int *pos, t_prompt *prompt)
{
	char	*expand;
	int		i;

	i = *pos;
	expand = NULL;
	if (str[i + 1] == '$')
	{
		ft_memmove(&str[i], &str[i + 1], ft_strlen(str) - i);
		*pos = i + 1;
		return (str);
	}
	else if (str[i + 1] == '?')
	{
		printf("g_ret: %d\n", g_ret);
		expand = ft_strdup(ft_itoa(g_ret));
	}
	else
	{
		while (str[i] && is_env(str[i + 1]))
			i++;
		expand = var_expand_env(str, pos, prompt, i);
	}
	return (expand);
}
