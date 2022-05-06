/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:07:39 by yang              #+#    #+#             */
/*   Updated: 2022/05/06 00:00:01 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_path(char *prefix, char *postfix, char *path)
{
	char	*temp;
	char	*expand;

	temp = NULL;
	expand = NULL;
	if (!prefix && !postfix)
		return (ft_strdup(path));
	else if (!prefix)
		return (ft_strjoin(path, postfix));
	else if (!postfix)
		return (ft_strjoin(prefix, path));
	else
	{
		temp = ft_strjoin(prefix, path);
		expand = ft_strjoin(temp, postfix);
		free(temp);
		return (expand);
	}
	return (expand);
}

static char	*expand_str(char *str, int *pos, char *path, bool heap)
{
	char	*expand;
	char	*prefix;
	char	*postfix;

	prefix = get_prefix(str, *pos);
	postfix = get_postfix(str, pos);
	if (!path)
	{
		if (!prefix && !postfix)
			expand = NULL;
		else if (!prefix)
			expand = ft_strjoin("", postfix);
		else if (!postfix)
			expand = ft_strjoin(prefix, "");
		else
			expand = ft_strjoin(prefix, postfix);
	}
	else
		expand = expand_path(prefix, postfix, path);
	free(prefix);
	free(postfix);
	if (heap)
		free(path);
	return (expand);
}

static char	*var_expand_env(char *str, int *pos, t_prompt *prompt, int i)
{
	char	*expand;
	char	*temp;
	char	*path;

	temp = ft_strndup(str + *pos + 1, i - *pos);
	path = ft_getenv(temp, prompt);
	free(temp);
	temp = NULL;
	expand = expand_str(str, pos, path, false);
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
		expand = expand_str(str, pos, ft_itoa(g_ret), true);
	else
	{
		while (str[i] && is_env(str[i + 1]))
			i++;
		expand = var_expand_env(str, pos, prompt, i);
	}
	return (expand);
}
