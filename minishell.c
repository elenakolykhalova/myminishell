/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 16:22:51 by mcarry            #+#    #+#             */
/*   Updated: 2021/07/22 18:15:45 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_dfl(t_shell *g_mini)
{
	if (g_mini->type_rd == 1)
	{
		dup2(g_mini->save1, 1);
		close(g_mini->save1);
	}
	if (g_mini->type_rd == 2)
	{
		dup2(g_mini->save1, 0);
		close(g_mini->save1);
		close(g_mini->fd);
		unlink("heredoc");
	}
	g_mini->flag_rd = 0;
	g_mini->flag_rd2 = 0;
	g_mini->flag_rd3 = 0;
	g_mini->type_rd = 0;
}

void	check_buffer_null(t_shell *g_mini)
{
	if (g_mini->buffer == NULL)
	{
		printf("\033[A");
		printf("Prompt: exit\n");
		exit(EXIT_SUCCESS);
	}
}

int	check_buffer(t_shell *g_mini)
{
	check_buffer_null(g_mini);
	if (strlen(g_mini->buffer) > 0)
	{
		add_history(g_mini->buffer);
		if (!pipe_parser(g_mini))
		{
			if (g_mini->pip > 0)
				func_pipe(g_mini);
			else
			{
				if (preparsing(g_mini) == 0)
				{
					parsing(g_mini);
					if (g_mini->pip == 0)
						free_list(g_mini->split_buf);
				}
			}
		}
		free_list(g_mini->pipe_array);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	init_array(env, &g_mini);
	while (1)
	{
		g_mini.global_var = 0;
		check_path(&g_mini);
		g_mini.buffer = readline("Prompt: ");
		if (check_buffer(&g_mini) == 1)
			return (0);
		if (g_mini.flag_rd2 > 0)
			redirect_dfl(&g_mini);
		if (g_mini.path != NULL)
			free_list(g_mini.path);
		free(g_mini.buffer);
		g_mini.flag_q1 = 0;
	}
	return (0);
}
