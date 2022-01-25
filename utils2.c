/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 14:50:17 by mcarry            #+#    #+#             */
/*   Updated: 2021/07/22 17:57:44 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_int(int **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_list(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	find_key_write(t_shell *g_mini, char *tmp, int i)
{
	char	*tmp4;
	char	*tmp2;

	tmp4 = g_mini->split_buf[g_mini->arg_buf];
	tmp2 = ft_substr(g_mini->str_env[i], ft_strlen(tmp),
			ft_strlen(g_mini->str_env[i]) - ft_strlen(tmp));
	g_mini->split_buf[g_mini->arg_buf]
		= ft_strjoin(g_mini->split_buf[g_mini->arg_buf], tmp2);
	free(tmp4);
	free(tmp2);
	free(tmp);
}

int	find_key(t_shell *g_mini, char *tmp)
{
	int		i;
	char	*tmp3;

	tmp3 = tmp;
	tmp = ft_strjoin(tmp, "=");
	free(tmp3);
	i = 0;
	while (g_mini->str_env[i])
	{
		if (!ft_strncmp(g_mini->str_env[i], tmp, ft_strlen(tmp)))
		{
			find_key_write(g_mini, tmp, i);
			return (0);
		}
		i++;
	}
	free(tmp);
	return (1);
}

void	pipe_flags_off(t_shell *g_mini)
{
	if (g_mini->flag_pipe2)
		g_mini->flag_pipe2 = 0;
	if (g_mini->flag_pipe1)
		g_mini->flag_pipe1 = 0;
}
