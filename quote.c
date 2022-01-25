/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 20:45:08 by mcarry            #+#    #+#             */
/*   Updated: 2021/07/22 17:01:22 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ver_quote(t_shell *g_mini)
{
	int	count;

	count = 0;
	if (g_mini->pipe_array[g_mini->pip][g_mini->k] == '$'
		&& !g_mini->flag_q1)
	{
		ver_dollar(g_mini);
		count = 0;
	}
	else
	{
		count++;
		g_mini->k++;
	}
}

int	ver_breaker_of_words(t_shell *g_mini, char c)
{
	g_mini->k++;
	while (g_mini->pipe_array[g_mini->pip][g_mini->k]
		&& g_mini->pipe_array[g_mini->pip][g_mini->k] != c)
		ver_quote(g_mini);
	if (g_mini->pipe_array[g_mini->pip][g_mini->k] != c)
	{
		printf("ERROR\n");
		return (-1);
	}
	else
		g_mini->flag_q = 0;
	if (!(g_mini->pipe_array[g_mini->pip][g_mini->k + 1])
		|| g_mini->pipe_array[g_mini->pip][g_mini->k + 1] == 32)
		g_mini->arg_buf++;
	return (0);
}

void	quote_malloc(t_shell *g_mini, int count)
{
	char	*tmp;
	char	*tmp2;

	tmp = g_mini->split_buf[g_mini->arg_buf];
	tmp2 = ft_substr(g_mini->pipe_array[g_mini->pip],
			g_mini->k - count, count);
	g_mini->split_buf[g_mini->arg_buf]
		= ft_strjoin(g_mini->split_buf[g_mini->arg_buf], tmp2);
	free(tmp);
	free(tmp2);
}

int	quote_move_forward(t_shell *g_mini, int count)
{
	if (g_mini->pipe_array[g_mini->pip][g_mini->k] == '$'
			&& !g_mini->flag_q1)
	{
		quote_malloc(g_mini, count);
		dollar(g_mini);
		count = 0;
	}
	else
	{
		count++;
		g_mini->k++;
	}
	return (count);
}

int	breaker_of_words(t_shell *g_mini, char c)
{
	int		count;

	count = 0;
	g_mini->k++;
	while (g_mini->pipe_array[g_mini->pip][g_mini->k]
		&& g_mini->pipe_array[g_mini->pip][g_mini->k] != c)
		count = quote_move_forward(g_mini, count);
	if (g_mini->pipe_array[g_mini->pip][g_mini->k] == c)
	{
		quote_malloc(g_mini, count);
		g_mini->flag_q = 0;
	}
	else
		return (-1);
	if (!(g_mini->pipe_array[g_mini->pip][g_mini->k + 1])
		|| g_mini->pipe_array[g_mini->pip][g_mini->k + 1] == 32)
		g_mini->arg_buf++;
	return (0);
}
