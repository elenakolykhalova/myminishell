/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_creat_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 17:26:01 by mcarry            #+#    #+#             */
/*   Updated: 2021/07/22 17:26:19 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_flags(t_shell *g_mini)
{
	if (g_mini->flag_rd3 == 0)
	{
		g_mini->save1 = dup(0);
		g_mini->flag_rd3++;
	}
	dup2(g_mini->fd, 0);
	close(g_mini->fd);
	g_mini->flag_rd = 0;
	if (g_mini->flag_new2)
		g_mini->flag_new2 = 0;
}

void	redirect_key(t_shell *g_mini, char *filename)
{
	char	*input;
	int		len1;
	int		len2;

	input = readline("> ");
	len1 = ft_strlen(filename);
	len2 = ft_strlen(input);
	if (len1 == len2)
	{
		if (ft_strncmp(input, filename, ft_strlen(filename)) == 0)
		{
			close(g_mini->fd);
			exit(EXIT_SUCCESS);
		}
	}
	write(g_mini->fd, input, ft_strlen(input));
	write(g_mini->fd, "\n", 1);
}
