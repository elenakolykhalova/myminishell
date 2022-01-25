/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 17:41:23 by jinigo            #+#    #+#             */
/*   Updated: 2021/07/20 20:17:16 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_malloc(t_shell *g_mini, int j)
{
	g_mini->pids = malloc(sizeof(pid_t) * (j + 1));
	if (!g_mini->pids)
		return (-1);
	g_mini->pfd = malloc(sizeof(int *) * (j + 1));
	if (!g_mini->pfd)
		return (-1);
	g_mini->pfd[j] = NULL;
	g_mini->pip = 0;
	while (g_mini->pip < j)
	{
		g_mini->pfd[g_mini->pip] = malloc(sizeof(int) * 2);
		if (!g_mini->pfd[g_mini->pip])
			return (-1);
		g_mini->pip++;
	}
	return (0);
}

void	pipe_action_dup(t_shell *g_mini, int j)
{
	if (g_mini->pip != j)
	{
		dup2(g_mini->pfd[g_mini->pip][1], 1);
		close(g_mini->pfd[g_mini->pip][1]);
		close(g_mini->pfd[g_mini->pip][0]);
	}
	if (g_mini->pip != 0)
	{
		dup2(g_mini->pfd[g_mini->pip - 1][0], 0);
		close(g_mini->pfd[g_mini->pip - 1][0]);
		close(g_mini->pfd[g_mini->pip - 1][1]);
	}
}

void	pipe_action_preparsing(t_shell *g_mini)
{
	parsing(g_mini);
	if (g_mini->flag_rd2 > 0)
	{
		if (g_mini->type_rd == 1)
		{
			dup2(g_mini->save1, 1);
			close(g_mini->save1);
		}
		if (g_mini->type_rd == 2 && g_mini->len_rd == 1)
		{
			dup2(g_mini->save1, 0);
			close(g_mini->save1);
		}
		g_mini->flag_rd2 = 0;
		g_mini->flag_rd3 = 0;
	}
}

void	pipe_action(t_shell *g_mini, int j)
{
	g_mini->pip = 0;
	while (g_mini->pip < j + 1)
	{
		if (g_mini->pip != j)
			pipe(g_mini->pfd[g_mini->pip]);
		g_mini->global_var = 1;
		g_mini->pids[g_mini->pip] = fork();
		if (g_mini->pids[g_mini->pip] == 0)
		{
			pipe_action_dup(g_mini, j);
			if (preparsing(g_mini) == 0)
				pipe_action_preparsing(g_mini);
			free_list(g_mini->split_buf);
			exit(g_mini->ft_errno);
		}
		else
		{
			if (g_mini->pip != 0)
			{
				close(g_mini->pfd[g_mini->pip - 1][0]);
				close(g_mini->pfd[g_mini->pip - 1][1]);
			}
		}
		g_mini->pip++;
	}
}

void	func_pipe(t_shell *g_mini)
{
	int	status;
	int	j;
	int	k;

	j = g_mini->pip;
	pipe_malloc(g_mini, j);
	pipe_action(g_mini, j);
	--g_mini->pip;
	waitpid(g_mini->pids[g_mini->pip], &status, 0);
	if (WIFEXITED(status))
		g_mini->ft_errno = WEXITSTATUS(status);
	else
		g_mini->ft_errno = WTERMSIG(status) + 128;
	while (wait(NULL) > 0)
		wait(NULL);
	k = -1;
	while (++k < j)
	{
		close(g_mini->pfd[k][0]);
		close(g_mini->pfd[k][1]);
	}
	free_int(g_mini->pfd);
	free(g_mini->pids);
}
