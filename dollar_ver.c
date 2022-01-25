/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_ver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 10:59:29 by mcarry            #+#    #+#             */
/*   Updated: 2021/07/22 17:10:45 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_forward(t_shell *g_mini)
{
	if (g_mini->pipe_array[g_mini->pip][g_mini->k] == 34)
	{
		g_mini->k++;
		while (g_mini->pipe_array[g_mini->pip][g_mini->k]
			&& g_mini->pipe_array[g_mini->pip][g_mini->k] != 34)
		{
			g_mini->k++;
		}
	}
	else
	{
		g_mini->k++;
		while (g_mini->pipe_array[g_mini->pip][g_mini->k]
			&& g_mini->pipe_array[g_mini->pip][g_mini->k] != 39)
		{
			g_mini->k++;
		}
	}
	if (!g_mini->pipe_array[g_mini->pip][g_mini->k + 1])
		g_mini->arg_buf++;
}

void	move_forward2(t_shell *g_mini)
{
	while (g_mini->pipe_array[g_mini->pip][g_mini->k]
		&& g_mini->pipe_array[g_mini->pip][g_mini->k] != 32)
	{
		if (g_mini->pipe_array[g_mini->pip][g_mini->k] == 34
			|| g_mini->pipe_array[g_mini->pip][g_mini->k] == 39)
			break ;
		g_mini->k++;
	}
	if (g_mini->pipe_array[g_mini->pip][g_mini->k] == 34
		|| g_mini->pipe_array[g_mini->pip][g_mini->k] == 39)
		g_mini->k--;
}

void	ver_dollar(t_shell *g_mini)
{
	g_mini->k++;
	if (!g_mini->pipe_array[g_mini->pip][g_mini->k]
		|| g_mini->pipe_array[g_mini->pip][g_mini->k] == 32)
	{
	}
	else if (g_mini->pipe_array[g_mini->pip][g_mini->k] == '?')
		g_mini->k++;
	else if ((g_mini->pipe_array[g_mini->pip][g_mini->k] == 34
		|| g_mini->pipe_array[g_mini->pip][g_mini->k] == 39) && !g_mini->flag_q)
		move_forward(g_mini);
	else if ((g_mini->pipe_array[g_mini->pip][g_mini->k] == 34
		|| g_mini->pipe_array[g_mini->pip][g_mini->k] == 39) && g_mini->flag_q)
	{
		g_mini->flag_q = 0;
		return ;
	}
	else if (g_mini->pipe_array[g_mini->pip][g_mini->k]
		&& g_mini->pipe_array[g_mini->pip][g_mini->k] != 32)
		move_forward2(g_mini);
	if (!(g_mini->pipe_array[g_mini->pip][g_mini->k])
		|| g_mini->pipe_array[g_mini->pip][g_mini->k] == ' ')
		g_mini->arg_buf++;
}
