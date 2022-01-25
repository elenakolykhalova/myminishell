/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_creat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 13:25:08 by mcarry            #+#    #+#             */
/*   Updated: 2021/07/22 17:27:06 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	redirect_flags(t_shell *g_mini)
// {
// 	if (g_mini->flag_rd3 == 0)
// 	{
// 		g_mini->save1 = dup(0);
// 		g_mini->flag_rd3++;
// 	}
// 	dup2(g_mini->fd, 0);
// 	close(g_mini->fd);
// 	g_mini->flag_rd = 0;
// 	if (g_mini->flag_new2)
// 		g_mini->flag_new2 = 0;
// }

// void	redirect_key(t_shell *g_mini, char *filename)
// {
// 	char	*input;
// 	int		len1;
// 	int		len2;

// 	input = readline("> ");
// 	len1 = ft_strlen(filename);
// 	len2 = ft_strlen(input);
// 	if (len1 == len2)
// 	{
// 		if (ft_strncmp(input, filename, ft_strlen(filename)) == 0)
// 		{
// 			close(g_mini->fd);
// 			exit(EXIT_SUCCESS);
// 		}
// 	}
// 	write(g_mini->fd, input, ft_strlen(input));
// 	write(g_mini->fd, "\n", 1);
// }

void	redirect_heredoc(t_shell *g_mini, char *filename)
{
	int		status;
	pid_t	pid;

	pid = fork();
	g_mini->fd = open("heredoc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (pid == 0)
	{
		while (1)
			redirect_key(g_mini, filename);
	}
	if (pid != 0)
		waitpid(pid, &status, 0);
	free(filename);
	redirect_flags(g_mini);
}

char	*redirect_name(char *filename)
{
	char	*tmp;
	int		i;

	i = 0;
	while (filename[i] == ' ')
		i++;
	tmp = filename;
	filename = ft_substr(filename, i, ft_strlen(filename) - i);
	free(tmp);
	return (filename);
}

int	redirect_len2(t_shell *g_mini, int count)
{
	char	*filename;

	filename = ft_substr(g_mini->pipe_array[g_mini->pip],
			g_mini->k - count, count);
	filename = redirect_name(filename);
	if (ft_strlen(filename) == 0 && !g_mini->flag_new2)
	{
		printf("Prompt: syntax error near unexpected token `newline'\n");
		g_mini->flag_rd2 = 0;
		free(filename);
		g_mini->type_rd = 0;
		return (-1);
	}
	else
		redirect_heredoc(g_mini, filename);
	return (0);
}

void	redirect_file(t_shell *g_mini, int count)
{
	char	*filename;

	filename = ft_substr(g_mini->pipe_array[g_mini->pip],
			g_mini->k - count, count);
	filename = redirect_name(filename);
	if (g_mini->type_rd == 1)
		g_mini->fd = open(filename, O_CREAT | O_WRONLY | g_mini->options, 0777);
	if (g_mini->type_rd == 2)
		g_mini->fd = open(filename, O_RDONLY);
	if (g_mini->flag_rd3 == 0)
	{
		if (g_mini->type_rd == 1)
			g_mini->save1 = dup(1);
		if (g_mini->type_rd == 2)
			g_mini->save1 = dup(0);
		g_mini->flag_rd3++;
	}
	if (g_mini->type_rd == 1)
		dup2(g_mini->fd, 1);
	if (g_mini->type_rd == 2)
		dup2(g_mini->fd, 0);
	close(g_mini->fd);
	g_mini->flag_rd = 0;
	free(filename);
}

int	redirect_creat(t_shell *g_mini, int count)
{
	if (g_mini->type_rd == 1)
	{
		redirect_file(g_mini, count);
		return (0);
	}
	if (g_mini->type_rd == 2)
	{
		if (g_mini->len_rd == 1)
		{
			redirect_file(g_mini, count);
			return (0);
		}
		if (g_mini->len_rd == 2)
			redirect_len2(g_mini, count);
	}
	return (0);
}
