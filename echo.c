/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:38:53 by mcarry            #+#    #+#             */
/*   Updated: 2021/07/20 13:29:45 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_dfl(t_shell *g_mini, int i)
{
	while (g_mini->split_buf[i])
	{
		write(1, g_mini->split_buf[i], ft_strlen(g_mini->split_buf[i]));
		if (g_mini->split_buf[i + 1])
			write(1, " ", 1);
		i++;
	}
	i--;
	return (i);
}

int	echo_flag(t_shell *g_mini, int i)
{
	int	j;

	j = 1;
	while (g_mini->split_buf[i] && g_mini->split_buf[i][j] == 'n')
		j++;
	if (!(g_mini->split_buf[i][j]))
		g_mini->flag_n = 1;
	else
	{
		while (g_mini->split_buf[i])
		{
			write(1, g_mini->split_buf[i], ft_strlen(g_mini->split_buf[i]));
			if (g_mini->split_buf[i + 1])
				write(1, " ", 1);
			i++;
		}
		i--;
	}
	return (i);
}

int	echo_n(t_shell *g_mini, int i)
{
	int	j;

	j = 0;
	if (i > 1)
	{
		i = 1;
		while (g_mini->split_buf[i])
		{
			j = 0;
			if (g_mini->split_buf[i][j] == '-')
			{
				if (g_mini->split_buf[i][j + 1] == 'n')
					i = echo_flag(g_mini, i);
			}
			else
				i = echo_dfl(g_mini, i);
			i++;
		}
	}
	if (g_mini->flag_n)
		return (1);
	else
		return (0);
}

void	ft_echo(t_shell *g_mini)
{
	int	i;

	g_mini->flag_n = 0;
	i = 0;
	while (g_mini->split_buf[i])
		i++;
	if (!echo_n(g_mini, i))
		write(1, "\n", 1);
	g_mini->ft_errno = 0;
}
