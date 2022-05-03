/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <leng-chu@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 18:55:41 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/03 17:52:49 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*if_env(char *str, char *s, int *cur, t_prompt *prompt)
{
	char	*env;
	char	*join;

	env = ft_stringenv(str, s, cur, prompt);
	if (!env)
		return (ft_freestr(s));
	join = ft_strjoin(s, env);
	ft_freestr(s);
	ft_freestr(env);
	return (join);
}

char	*if_no_env(char *str, char *s, int *cur)
{
	char	*new;
	char	*join;
	int		start;

	start = *cur;
	while (str[*cur] && str[*cur] != '$')
		(*cur)++;
	new = malloc(sizeof(char) * ((*cur) - start));
	if (!new)
		return (ft_freestr(s));
	new = ft_strncpy(new, str + start, ((*cur) - start));
	join = ft_strjoin(s, new);
	ft_freestr(s);
	ft_freestr(new);
	return (join);
}

int	ft_launch_heredoc(t_cmd *cmd, t_prompt *prompt)
{
	int		fd;
	char	*filename;

	filename = NULL;
	fd = -1;
	while (fd == -1)
	{
		if (filename)
			free(filename);
		filename = ft_create_file();
		fd = open(filename, O_CREAT | O_EXCL | O_RDWR, 0644);
	}
	ft_write_infd(fd, cmd, prompt);
	fd = open(filename, O_RDONLY);
	return (fd);
}

int	ft_write_infd(int fd, t_cmd *cmd, t_prompt *prompt)
{
	char	*str;
	char	*eof;
	t_list	*token;
	(void)prompt;

	token = cmd->token;
	while (token != NULL)
	{
		if (token->type == 4)
			eof = token->content;
		token = token->next;
	}
	while (1)
	{
		str = readline("myheredoc>> ");
		if (!str)
			return (0);
		if (ft_strcmp(eof, str) == 0)
			break ;
	// need ask Yee Jin about expand on env's $
	/*	if (str[0] != '\0')
		{
			if (expanded == 0)
			{
				str = ft_expanded(str, prompt);
				if (str == NULL)
					return (50);
			}
		}*/
		ft_putendl_fd(str, fd);
		free(str);
	}
	free(str);
	return (0);
}

char	*ft_expanded(char *str, t_prompt *prompt)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			new = if_env(str, new, &i, prompt);
			if (!new)
				return (NULL);
		}
		else
		{
			new = if_no_env(str, new, &i);
			if (!new)
				return (NULL);
		}
	}
	free(str);
	return (new);
}
