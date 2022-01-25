/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spacer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 20:43:42 by mcarry            #+#    #+#             */
/*   Updated: 2021/07/22 17:24:33 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	spacer_redirect(t_shell *g_mini, int count)
{
	if (g_mini->k > 0 && (g_mini->pipe_array[g_mini->pip][g_mini->k - 1]
		>= 33 && g_mini->pipe_array[g_mini->pip][g_mini->k - 1] <= 126))
	{
		free(g_mini->split_buf[g_mini->arg_buf]);
		g_mini->split_buf[g_mini->arg_buf]
			= ft_substr(g_mini->pipe_array[g_mini->pip],
				g_mini->k - count, count);
		g_mini->arg_buf++;
	}
	if (g_mini->pipe_array[g_mini->pip][g_mini->k] == '>')
	{
		while (g_mini->pipe_array[g_mini->pip][g_mini->k] == '>')
			g_mini->k++;
	}
	if (g_mini->pipe_array[g_mini->pip][g_mini->k] == '<')
	{
		while (g_mini->pipe_array[g_mini->pip][g_mini->k] == '<')
			g_mini->k++;
	}
}

int	spacer_cycle_util(t_shell *g_mini, int count)
{
	if (g_mini->pipe_array[g_mini->pip][g_mini->k] == '>'
		|| g_mini->pipe_array[g_mini->pip][g_mini->k] == '<')
	{
		g_mini->flag_rd = 1;
		spacer_redirect(g_mini, count);
		return (0);
	}
	return (count);
}

int	spacer_cycle(t_shell *g_mini, char c)
{
	int	count;

	count = 0;
	while (g_mini->pipe_array[g_mini->pip][g_mini->k]
		&& g_mini->pipe_array[g_mini->pip][g_mini->k] != c)
	{
		count = spacer_cycle_util(g_mini, count);
		if (g_mini->pipe_array[g_mini->pip][g_mini->k] == 34
			|| g_mini->pipe_array[g_mini->pip][g_mini->k] == 39
			|| g_mini->pipe_array[g_mini->pip][g_mini->k] == 36)
		{	
			if (g_mini->flag_rd)
			{
				g_mini->k++;
				while (g_mini->pipe_array[g_mini->pip][g_mini->k] != 34
					&& g_mini->pipe_array[g_mini->pip][g_mini->k] != 39)
					g_mini->k++;
				count = 0;
			}
			break ;
		}
		count++;
		g_mini->k++;
	}
	return (count);
}

int	spacer(t_shell *g_mini, char c)
{
	char	*tmp;
	char	*tmp2;
	int		count;

	count = spacer_cycle(g_mini, c);
	if (g_mini->flag_rd)
	{
		g_mini->flag_rd = 0;
		return (0);
	}
	tmp = g_mini->split_buf[g_mini->arg_buf];
	tmp2 = ft_substr(g_mini->pipe_array[g_mini->pip],
			g_mini->k - count, count);
	g_mini->split_buf[g_mini->arg_buf]
		= ft_strjoin(g_mini->split_buf[g_mini->arg_buf], tmp2);
	free(tmp);
	free(tmp2);
	if (g_mini->pipe_array[g_mini->pip][g_mini->k] == 34
		|| g_mini->pipe_array[g_mini->pip][g_mini->k] == 39
		|| g_mini->pipe_array[g_mini->pip][g_mini->k] == 36)
		g_mini->k--;
	if (!(g_mini->pipe_array[g_mini->pip][g_mini->k])
		|| g_mini->pipe_array[g_mini->pip][g_mini->k] == 32)
		g_mini->arg_buf++;
	return (0);
}
