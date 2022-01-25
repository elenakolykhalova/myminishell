/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:11:39 by mcarry            #+#    #+#             */
/*   Updated: 2021/07/19 17:24:19 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_shell *g_mini)
{
	int	i;

	if (g_mini->arg_buf > 1)
	{
		write(1, "env: Must be without any options and any arguments\n", 52);
		g_mini->ft_errno = 127;
		return (0);
	}
	i = -1;
	while (g_mini->str_env[++i])
	{
		printf("%s\n", g_mini->str_env[i]);
	}
	g_mini->ft_errno = 0;
	return (0);
}
