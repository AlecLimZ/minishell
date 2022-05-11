/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 18:55:41 by leng-chu          #+#    #+#             */
/*   Updated: 2022/05/10 10:44:43 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDE/minishell.h"

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
	if (s == NULL)
		s = ft_strdup("");
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
	free(filename);
	return (fd);
}

int	ft_write_infd(int fd, t_cmd *cmd, t_prompt *prompt)
{
	char	*str;
	char	*eof;

	eof = ft_geteof(cmd);
	while (1)
	{
		str = readline(YEL"myheredoc>> "DEF);
		if (!str)
			return (ERROR);
		if (ft_strcmp(eof, str) == 0)
			break ;
		if (str[0] != '\0')
			if (ft_strchr(str, '$'))
				str = ft_expanded(str, prompt);
		ft_putendl_fd(str, fd);
		free(str);
	}
	free(str);
	return (SUCCESS);
}

char	*ft_expanded(char *str, t_prompt *prompt)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	while (str[i] != '\0' && i < (int)ft_strlen(str))
	{
		if (str[i] == '$')
			new = ft_dollar(str, new, &i, prompt);
		else
			new = ft_nodollar(str, new, &i);
	}
	free(str);
	return (new);
}
