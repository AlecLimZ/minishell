/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:53:45 by leng-chu          #+#    #+#             */
/*   Updated: 2022/04/25 19:17:18 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "yeejin.h"

/* refresh the prompt if user hit Ctrl + C */
void new_prompt(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/* init environment, add environment list into linked list */
int	init_env(t_prompt *prompt, char *envp[])
{
	int		i;
	t_list	*new;

	i = -1;
	prompt->envp = NULL;
	while (envp[++i] != NULL)
	{
		new = ft_lstnew(envp[i]);
		ft_lstadd_back(&prompt->envp, new);
	}
	return (0);
}

/* get input from user and add it into history list */
int	get_input(char *str)
{
	char *buf;

	buf = readline(">>> ");
	if (buf && ft_strlen(buf) != 0)
	{
		add_history(buf);
		ft_strlcpy(str, buf, ft_strlen(buf) + 1);
		return (0);
	}
	else
		return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	char		input_str[MAXCOM];
	t_prompt	*prompt;

	prompt = malloc(sizeof(t_prompt));
	if (!prompt)
		return EXIT_FAILURE;
	ft_memset(prompt, 0, sizeof(t_prompt));
	init_env(prompt, envp);
	prompt->env = envp;
	//signal(SIGINT, new_prompt);
	while (argc && argv)
	{
		if (get_input(input_str))
			continue;
		if (parser(prompt, input_str) == -1)
		{
			printf("error occurred when parsing command\n");
			return (1);
		}
		exec_args(prompt);
		//printf("%s\n", getenv("HOME"));
		//parser(prompt, input_str);
		//split_args_pipe(input_str, str);
		//Perform any shutdown/cleanup
	}
	
	return EXIT_SUCCESS;
}
