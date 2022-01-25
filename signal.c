/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 20:41:28 by jinigo            #+#    #+#             */
/*   Updated: 2021/07/21 18:59:05 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hand_c2(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	errno = 1;
}

void	hand_c(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	errno = 1;
}

void	handler(int num)
{
	if (num == SIGINT && g_mini.global_var == 0)
		hand_c();
	if (num == SIGINT && g_mini.global_var == 1)
		hand_c2();
	if (num == SIGQUIT && g_mini.global_var == 1)
	{
		if (g_mini.global_var2 == 0)
			printf("Quit: 3\n");
	}
	if (num == SIGQUIT && g_mini.global_var == 0)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}
