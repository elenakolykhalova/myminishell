/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 11:52:18 by mcarry            #+#    #+#             */
/*   Updated: 2021/07/22 17:04:32 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_error(t_shell *g_mini, int count, char c)
{
	char	*filename;

	count = 0;
	while (g_mini->pipe_array[g_mini->pip][g_mini->k]
		&& g_mini->pipe_array[g_mini->pip][g_mini->k] != c)
	{
		count++;
		g_mini->k++;
	}
	filename = ft_substr(g_mini->pipe_array[g_mini->pip],
			g_mini->k - count, count);
	printf("Prompt: syntax error near unexpected token `%s'\n", filename);
	free(filename);
}

int	redirect_in(t_shell *g_mini)
{
	char	*filename;
	int		count;

	g_mini->type_rd = 1;
	count = 0;
	while (g_mini->pipe_array[g_mini->pip][g_mini->k] == '>')
	{
		count++;
		g_mini->k++;
	}
	if (count == 1)
		g_mini->options = 0x0400;
	else if (count == 2)
		g_mini->options = 0x0008;
	else
	{
		filename = ft_substr(g_mini->pipe_array[g_mini->pip],
				g_mini->k - (count - 2), count - 2);
		printf("Prompt: syntax error near unexpected token `%s'\n", filename);
		free(filename);
		return (-1);
	}
	return (0);
}

int	redirect_out(t_shell *g_mini, int count)
{
	char	*filename;

	count = 0;
	g_mini->type_rd = 2;
	while (g_mini->pipe_array[g_mini->pip][g_mini->k] == '<')
	{
		count++;
		g_mini->k++;
	}
	g_mini->len_rd = count;
	if (count > 2)
	{
		filename = ft_substr(g_mini->pipe_array[g_mini->pip],
				g_mini->k - (count - 2), count - 2);
		printf("Prompt: syntax error near unexpected token `%s'\n", filename);
		free(filename);
		return (-1);
	}
	return (0);
}

int	redirect_in_or_out(t_shell *g_mini, int count)
{
	if (g_mini->pipe_array[g_mini->pip][g_mini->k] == '>')
	{
		if (redirect_in(g_mini) < 0)
			return (-1);
	}
	if (g_mini->pipe_array[g_mini->pip][g_mini->k] == '<')
	{
		if (redirect_out(g_mini, count) < 0)
			return (-1);
	}
	return (0);
}

int	redirect(t_shell *g_mini, int count, char c)
{
	if (g_mini->flag_rd > 0)
	{
		redirect_error(g_mini, count, c);
		return (-1);
	}
	else
	{
		g_mini->flag_rd = 1;
		g_mini->flag_rd2 = 1;
		if (g_mini->k > 0 && (g_mini->pipe_array[g_mini->pip][g_mini->k - 1]
			>= 33 && g_mini->pipe_array[g_mini->pip][g_mini->k - 1] <= 126))
			g_mini->arg_buf++;
		if (redirect_in_or_out(g_mini, count) == -1)
			return (-1);
		count = 0;
	}
	return (count);
}
