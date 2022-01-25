/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 11:07:10 by jinigo            #+#    #+#             */
/*   Updated: 2021/07/22 17:57:59 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_flags(t_shell *g_mini, int i)
{
	if (g_mini->buffer[i] == 34 && !g_mini->flag_pipe1)
	{
		if (!g_mini->flag_pipe2)
			g_mini->flag_pipe2 = 1;
		else
			g_mini->flag_pipe2 = 0;
	}
	if (g_mini->buffer[i] == 39 && !g_mini->flag_pipe2)
	{
		if (!g_mini->flag_pipe1)
			g_mini->flag_pipe1 = 1;
		else
			g_mini->flag_pipe1 = 0;
	}
}

void	pipe_count(t_shell *g_mini)
{
	int	i;

	i = 0;
	while (g_mini->buffer[i])
	{
		pipe_flags(g_mini, i);
		if (g_mini->buffer[i] == '|'
			&& (!g_mini->flag_pipe1 && !g_mini->flag_pipe2))
			g_mini->pip++;
		i++;
	}
}

int	ft_isspace(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != 32)
			return (0);
	}
	return (1);
}

void	pipe_gap(t_shell *g_mini)
{
	int	i;
	int	j;

	i = 0;
	j = i;
	while (g_mini->buffer[i])
	{
		pipe_flags(g_mini, i);
		if (g_mini->buffer[i] == '|'
			&& (!g_mini->flag_pipe1 && !g_mini->flag_pipe2))
		{
			g_mini->pipe_array[g_mini->pip]
				= ft_substr(g_mini->buffer, j, i - j);
			j = i + 1;
			g_mini->pip++;
		}
		i++;
	}
	g_mini->pipe_array[g_mini->pip] = ft_substr(g_mini->buffer, j, i - j);
}

int	pipe_parser(t_shell *g_mini)
{
	g_mini->pip = 0;
	pipe_count(g_mini);
	g_mini->pip++;
	g_mini->pipe_array = malloc(sizeof(char *) * (g_mini->pip + 1));
	if (!g_mini->pipe_array)
		return (1);
	pipe_flags_off(g_mini);
	g_mini->pipe_array[g_mini->pip] = NULL;
	g_mini->pip = 0;
	pipe_gap(g_mini);
	pipe_flags_off(g_mini);
	g_mini->pip = -1;
	while (g_mini->pipe_array[++g_mini->pip])
	{
		if ((ft_strlen(g_mini->pipe_array[g_mini->pip]) == 0
				|| ft_isspace(g_mini->pipe_array[g_mini->pip]))
			&& g_mini->pip > 0)
		{
			printf("Prompt: syntax error near unexpected token `|'\n");
			return (1);
		}
	}
	g_mini->pip--;
	return (0);
}
