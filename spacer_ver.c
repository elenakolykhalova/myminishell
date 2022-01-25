/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spacer_ver.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 14:32:11 by mcarry            #+#    #+#             */
/*   Updated: 2021/07/22 13:20:14 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ver_spacer_flags(t_shell *g_mini)
{
	if (g_mini->pipe_array[g_mini->pip][g_mini->k] == 34
		|| g_mini->pipe_array[g_mini->pip][g_mini->k] == 39
		|| g_mini->pipe_array[g_mini->pip][g_mini->k] == 36)
	{
		if (g_mini->flag_new)
		{
			g_mini->flag_new = 0;
			return (1);
		}
		if (g_mini->type_rd == 2)
		{
			g_mini->flag_new = 1;
			g_mini->flag_new2 = 1;
		}
		if (!g_mini->flag_new)
			return (1);
	}
	return (0);
}

int	ver_spacer_cycle(t_shell *g_mini, char c)
{
	int		count;

	count = 0;
	while (g_mini->pipe_array[g_mini->pip][g_mini->k]
		&& g_mini->pipe_array[g_mini->pip][g_mini->k] != c)
	{
		if (g_mini->pipe_array[g_mini->pip][g_mini->k] == '>'
			|| g_mini->pipe_array[g_mini->pip][g_mini->k] == '<')
		{
			count = redirect(g_mini, count, c);
			if (count == -1)
				return (-1);
		}
		if (ver_spacer_flags(g_mini))
			break ;
		if (!g_mini->flag_new)
		{
			count++;
			g_mini->k++;
		}
	}
	return (count);
}

int	verified_spacer(t_shell *g_mini, char c)
{
	int		count;

	count = 0;
	count = ver_spacer_cycle(g_mini, c);
	if (count == -1)
		return (-1);
	if (g_mini->flag_rd)
	{
		if (redirect_creat(g_mini, count) < 0)
			return (-1);
	}
	if (g_mini->pipe_array[g_mini->pip][g_mini->k] == 34
		|| g_mini->pipe_array[g_mini->pip][g_mini->k] == 39
		|| g_mini->pipe_array[g_mini->pip][g_mini->k] == 36)
		g_mini->k--;
	if (!(g_mini->pipe_array[g_mini->pip][g_mini->k])
		|| g_mini->pipe_array[g_mini->pip][g_mini->k] == 32)
	{
		if (!g_mini->type_rd_arg)
		{
			if (!g_mini->type_rd)
				g_mini->arg_buf++;
		}
	}
	return (0);
}
