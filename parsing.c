/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 11:51:40 by mcarry            #+#    #+#             */
/*   Updated: 2021/07/22 17:00:13 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins(t_shell *g_mini)
{
	if (!ft_strncmp(g_mini->split_buf[0], "env", ft_strlen("env")))
		ft_env(g_mini);
	else if (!ft_strncmp(g_mini->split_buf[0], "pwd", ft_strlen("pwd")))
		ft_pwd(g_mini);
	else if (!ft_strncmp(g_mini->split_buf[0], "unset", ft_strlen("unset")))
		ft_unset(g_mini);
	else if (!ft_strncmp(g_mini->split_buf[0], "export",
			ft_strlen("export")))
		ft_export(g_mini);
	else if (!ft_strncmp(g_mini->split_buf[0], "exit", ft_strlen("exit")))
		ft_exit(g_mini);
	else if (!ft_strncmp(g_mini->split_buf[0], "echo", ft_strlen("echo")))
		ft_echo(g_mini);
	else if (!ft_strncmp(g_mini->split_buf[0], "cd", ft_strlen("cd")))
		ft_cd(g_mini);
	else
		return (1);
	return (0);
}

void	binary(t_shell *g_mini)
{
	if (full_path(g_mini) == 0)
		return ;
	else
	{
		if (g_mini->flag_rd2 > 0)
		{
			dup2(g_mini->save1, 1);
			close(g_mini->save1);
			g_mini->flag_rd2 = 0;
			g_mini->flag_rd3 = 0;
		}
		if (ft_strlen(g_mini->split_buf[0]) > 0)
		{
			printf("Prompt: %s: command not found\n",
				g_mini->split_buf[0]);
			g_mini->ft_errno = 127;
		}
	}
}

int	parsing(t_shell *g_mini)
{
	if (g_mini->split_buf[0] && ft_strlen(g_mini->split_buf[0]) > 0)
	{
		if (builtins(g_mini))
			binary(g_mini);
	}
	return (0);
}
