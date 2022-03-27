/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:53:45 by leng-chu          #+#    #+#             */
/*   Updated: 2022/03/28 00:13:59 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDE/minishell.h"

/* refresh the prompt if user press Ctrl + C 
 * Problem facing: ^C displayed
 */
void new_prompt(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
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
	//t_prompt	*prompt;
	(void)envp;

	signal(SIGINT, new_prompt);
	while (argc && argv)
	{
		get_input(input_str);
			//continue;
		//split_args_pipe(input_str, str);
		//Perform any shutdown/cleanup
	}
	
	return EXIT_SUCCESS;
}
