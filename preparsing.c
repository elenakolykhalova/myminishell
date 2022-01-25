/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 11:04:02 by jinigo            #+#    #+#             */
/*   Updated: 2021/07/22 17:12:17 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arg_buf_fill(t_shell *g_mini)
{
	while (g_mini->pipe_array[g_mini->pip][g_mini->k] == ' ')
		g_mini->k++;
	if (g_mini->pipe_array[g_mini->pip][g_mini->k] >= 33
		&& g_mini->pipe_array[g_mini->pip][g_mini->k] <= 126)
	{
		if (g_mini->pipe_array[g_mini->pip][g_mini->k] == 34
			|| g_mini->pipe_array[g_mini->pip][g_mini->k] == 39)
		{
			g_mini->flag_q = 1;
			if (g_mini->pipe_array[g_mini->pip][g_mini->k] == 34)
				breaker_of_words(g_mini, 34);
			else
				breaker_of_words(g_mini, 39);
		}
		else if (g_mini->pipe_array[g_mini->pip][g_mini->k] == 36)
			dollar(g_mini);
		else
			spacer(g_mini, 32);
	}
	if (g_mini->pipe_array[g_mini->pip][g_mini->k])
		g_mini->k++;
}

int	preparsing_quote(t_shell *g_mini)
{
	int	i;

	i = 0;
	if (g_mini->pipe_array[g_mini->pip][g_mini->k] == 34)
	{
		i = ver_breaker_of_words(g_mini, 34);
		if (i != 0)
			return (1);
	}
	else
	{	
		g_mini->flag_q1 = 1;
		i = ver_breaker_of_words(g_mini, 39);
		if (i != 0)
			return (1);
	}
	return (0);
}

int	preparsing_ver(t_shell *g_mini)
{	
	while (g_mini->pipe_array[g_mini->pip][g_mini->k] == ' ')
		g_mini->k++;
	if (g_mini->pipe_array[g_mini->pip][g_mini->k] >= 33
		&& g_mini->pipe_array[g_mini->pip][g_mini->k] <= 126)
	{
		if (g_mini->pipe_array[g_mini->pip][g_mini->k] == 34
			|| g_mini->pipe_array[g_mini->pip][g_mini->k] == 39)
		{
			g_mini->flag_q = 1;
			if (preparsing_quote(g_mini))
				return (1);
		}
		else if (g_mini->pipe_array[g_mini->pip][g_mini->k] == 36)
			ver_dollar(g_mini);
		else
		{
			if (verified_spacer(g_mini, 32) == -1)
				return (1);
		}
	}
	return (0);
}

int	preparsing(t_shell *g_mini)
{
	g_mini->k = 0;
	g_mini->arg_buf = 0;
	while (g_mini->pipe_array[g_mini->pip][g_mini->k])
	{
		if (preparsing_ver(g_mini))
			return (1);
		if (g_mini->pipe_array[g_mini->pip][g_mini->k])
			g_mini->k++;
	}
	g_mini->split_buf = malloc(sizeof(char *) * (g_mini->arg_buf + 1));
	g_mini->split_buf[g_mini->arg_buf] = NULL;
	if (g_mini->split_buf == 0)
		return (1);
	while (--g_mini->arg_buf >= 0)
		g_mini->split_buf[g_mini->arg_buf] = ft_strdup("");
	g_mini->k = 0;
	g_mini->arg_buf = 0;
	while (g_mini->pipe_array[g_mini->pip][g_mini->k])
		arg_buf_fill(g_mini);
	if (g_mini->type_rd_arg)
		g_mini->type_rd_arg = 0;
	return (0);
}
