/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_mal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 11:02:43 by mcarry            #+#    #+#             */
/*   Updated: 2021/07/21 11:03:06 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollar_malloc(t_shell *g_mini)
{
	free(g_mini->split_buf[g_mini->arg_buf]);
	g_mini->split_buf[g_mini->arg_buf] = malloc(sizeof(char) * (1 + 1));
	if (!g_mini->split_buf[g_mini->arg_buf])
		return (-1);
	g_mini->split_buf[g_mini->arg_buf][1] = '\0';
	g_mini->split_buf[g_mini->arg_buf][0] = '$';
	return (0);
}

void	dollar_quote_malloc(t_shell *g_mini, char c)
{
	char	*tmp;
	char	*tmp2;
	int		count;

	count = 0;
	while (g_mini->pipe_array[g_mini->pip][g_mini->k]
		&& g_mini->pipe_array[g_mini->pip][g_mini->k] != c)
		count++;
	tmp = g_mini->split_buf[g_mini->arg_buf];
	tmp2 = ft_substr(g_mini->pipe_array[g_mini->pip], g_mini->k - count, count);
	g_mini->split_buf[g_mini->arg_buf]
		= ft_strjoin(g_mini->split_buf[g_mini->arg_buf], tmp2);
	free(tmp);
	free(tmp2);
}
