/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:14:27 by mcarry            #+#    #+#             */
/*   Updated: 2021/07/20 13:41:03 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_error(t_shell *g_mini)
{
	int	i;

	i = 0;
	while (g_mini->split_buf[1][i])
	{
		if (!ft_isdigit(g_mini->split_buf[1][i]))
		{
			printf("exit\n");
			printf("Prompt: exit: %s: numeric argument required\n",
				g_mini->split_buf[1]);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	printf("exit\n");
	printf("Prompt: exit: too many arguments\n");
}

void	ft_exit(t_shell *g_mini)
{
	int	i;

	i = 0;
	if (g_mini->arg_buf > 2)
	{
		ft_exit_error(g_mini);
		return ;
	}
	printf("exit\n");
	if (g_mini->split_buf[1])
	{
		while (g_mini->split_buf[1][i])
		{
			if (!ft_isdigit(g_mini->split_buf[1][i]))
			{
				printf("Prompt: exit: %s: numeric argument required\n",
					g_mini->split_buf[1]);
				break ;
			}
			i++;
		}
	}
	free_list(g_mini->str_env);
	exit(errno);
}
