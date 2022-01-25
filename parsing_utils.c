/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 15:55:52 by mcarry            #+#    #+#             */
/*   Updated: 2021/07/20 18:23:13 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_path(t_shell *g_mini)
{
	int		i;
	int		length;
	char	*road;

	i = -1;
	while (g_mini->str_env[++i])
	{
		if (!(ft_strncmp(g_mini->str_env[i], "PATH=", 5)))
		{
			length = ft_strlen(g_mini->str_env[i]);
			road = ft_substr(g_mini->str_env[i], 5, length - 5);
			g_mini->path = ft_split(road, ':');
			free(road);
			return ;
		}
		else
			g_mini->path = NULL;
	}
}

void	pars_status(t_shell *g_mini, int status)
{
	if (WIFEXITED(status) == 1)
		g_mini->ft_errno = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) == 1)
		g_mini->ft_errno = WTERMSIG(status) + 128;
}

void	pars_exec(t_shell *g_mini, int i)
{
	int	status;

	g_mini->global_var = 1;
	g_mini->pid = fork();
	if (g_mini->pid == 0)
	{
		g_mini->global_var2 = 1;
		execve(g_mini->path[i], g_mini->split_buf, g_mini->str_env);
		exit(EXIT_FAILURE);
	}
	if (g_mini->pid != 0)
	{
		if (g_mini->pip == 0)
		{
			waitpid(g_mini->pid, &status, 0);
			pars_status(g_mini, status);
		}
		else
		{
			g_mini->global_var2 = 1;
			waitpid(g_mini->pid, &status, 0);
			pars_status(g_mini, status);
		}
	}
}

int	pars_actions(t_shell *g_mini, struct stat *buf)
{
	char	*temp;
	int		i;

	i = 0;
	while (g_mini->path[i])
	{
		temp = ft_strjoin(g_mini->path[i], "/");
		free(g_mini->path[i]);
		g_mini->path[i] = ft_strjoin(temp, g_mini->split_buf[0]);
		free(temp);
		if (stat(g_mini->path[i], buf) == 0 && buf->st_mode != 16877)
		{
			pars_exec(g_mini, i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	full_path(t_shell *g_mini)
{
	struct stat	buf;
	int			status;

	if (stat(g_mini->split_buf[0], &buf) == 0 && buf.st_mode != 16877)
	{
		g_mini->global_var = 1;
		g_mini->pid = fork();
		if (g_mini->pid == 0)
		{
			execve(g_mini->split_buf[0], g_mini->split_buf, g_mini->str_env);
			exit(EXIT_SUCCESS);
		}
		if (g_mini->pid != 0)
			waitpid(g_mini->pid, &status, 0);
		return (0);
	}
	else
	{
		if (g_mini->path != NULL)
		{
			if (pars_actions(g_mini, &buf) == 0)
				return (0);
		}
	}
	return (1);
}
