/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:53:45 by leng-chu          #+#    #+#             */
/*   Updated: 2022/03/28 15:34:16 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

/* refresh the prompt if user hit Ctrl + C */
void new_prompt(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/* init environment */
void init_env(t_prompt *prompt, char *envp[])
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (envp[++i] != NULL)
		count++;
	prompt->envp = (char **)malloc(sizeof(char *) * (count + 1));
	if (!prompt->envp)
		return;
	i = -1;
	while (envp[++i] != NULL)
		prompt->envp[i] = ft_strdup(envp[i]);
	prompt->envp[i] = NULL;
}

/* get input from user and add it into history list */
int get_input(char *str)
{
	char *buf;

	buf = readline(">>> ");
	if (strlen(buf) != 0)
	{
		add_history(buf);
		ft_strlcpy(str, buf, ft_strlen(buf) + 1);
		return (0);
	}
	else
		return (1);
}

int main(int argc, char *argv[], char *envp[])
{
	char input_str[MAXCOM];
	t_prompt	*prompt;
	(void)envp;

	prompt = malloc(sizeof(t_prompt));
	if (!prompt)
		return EXIT_FAILURE;
	ft_memset(prompt, 0, sizeof(t_prompt));
	init_env(prompt, envp);
	signal(SIGINT, new_prompt);
	while (argc && argv)
	{
		if (get_input(input_str))
			continue;
		parser(prompt, input_str);
		//split_args_pipe(input_str, str);
		//Perform any shutdown/cleanup
	}
	
	return EXIT_SUCCESS;
}
