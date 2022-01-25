/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 10:05:42 by jinigo            #+#    #+#             */
/*   Updated: 2021/07/22 17:02:54 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_quote(t_shell *g_mini)
{
	if (g_mini->pipe_array[g_mini->pip][g_mini->k] == 34)
		dollar_quote_malloc(g_mini, 34);
	else
		dollar_quote_malloc(g_mini, 39);
}

void	dollar_space(t_shell *g_mini)
{
	int		count;
	char	*tmp;

	count = 0;
	while (g_mini->pipe_array[g_mini->pip][g_mini->k]
		&& g_mini->pipe_array[g_mini->pip][g_mini->k] != 32)
	{
		if (g_mini->pipe_array[g_mini->pip][g_mini->k] == 34
			|| g_mini->pipe_array[g_mini->pip][g_mini->k] == 39)
			break ;
		count++;
		g_mini->k++;
	}
	tmp = ft_substr(g_mini->pipe_array[g_mini->pip], g_mini->k - count, count);
	find_key(g_mini, tmp);
	if ((g_mini->pipe_array[g_mini->pip][g_mini->k] == 34
		|| g_mini->pipe_array[g_mini->pip][g_mini->k] == 39))
		if (g_mini->flag_q)
			g_mini->flag_q = 0;
}

void	dollar_question(t_shell *g_mini)
{
	char	*tmp;
	char	*tmp2;
	int		count;

	count = 0;
	g_mini->k++;
	tmp = g_mini->split_buf[g_mini->arg_buf];
	tmp2 = ft_itoa(g_mini->ft_errno);
	g_mini->split_buf[g_mini->arg_buf]
		= ft_strjoin(g_mini->split_buf[g_mini->arg_buf], tmp2);
	free(tmp);
	free(tmp2);
}

void	dollar(t_shell *g_mini)
{
	g_mini->k++;
	if (!g_mini->pipe_array[g_mini->pip][g_mini->k]
		|| g_mini->pipe_array[g_mini->pip][g_mini->k] == 32)
		dollar_malloc(g_mini);
	else if (g_mini->pipe_array[g_mini->pip][g_mini->k] == '?')
		dollar_question(g_mini);
	else if ((g_mini->pipe_array[g_mini->pip][g_mini->k] == 34
		|| g_mini->pipe_array[g_mini->pip][g_mini->k] == 39) && !g_mini->flag_q)
	{
		g_mini->flag_q = 1;
		dollar_quote(g_mini);
	}
	else if ((g_mini->pipe_array[g_mini->pip][g_mini->k] == 34
		|| g_mini->pipe_array[g_mini->pip][g_mini->k] == 39) && g_mini->flag_q)
	{
		g_mini->flag_q = 0;
		dollar_malloc(g_mini);
		return ;
	}
	else if (g_mini->pipe_array[g_mini->pip][g_mini->k]
		&& g_mini->pipe_array[g_mini->pip][g_mini->k] != 32)
		dollar_space(g_mini);
	if (!(g_mini->pipe_array[g_mini->pip][g_mini->k])
		|| g_mini->pipe_array[g_mini->pip][g_mini->k] == ' ')
		g_mini->arg_buf++;
}
