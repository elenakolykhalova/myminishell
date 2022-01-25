/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 20:24:18 by mcarry            #+#    #+#             */
/*   Updated: 2021/07/21 17:51:49 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_error(int err, t_shell *g_mini, char *path)
{
	if (err == ENOENT)
		printf("Prompt: cd: %s: No such file or directory\n", path);
	else if (err == ENOTDIR)
		printf("Prompt: cd: %s: Not a directory\n", path);
	g_mini->ft_errno = 1;
}

void	cd_oldpwd_pwd(t_shell *g_mini, char *str)
{
	check_twin(g_mini->str_env, str, '=');
	check_twin(g_mini->str_exp, str, '=');
	free(str);
}

char	*check_cd(t_shell *g_mini)
{
	int		i;
	int		length;
	char	*path;

	i = -1;
	while (g_mini->str_env[++i])
	{
		if (!(ft_strncmp(g_mini->str_env[i], "HOME=", 5)))
		{
			length = ft_strlen(g_mini->str_env[i]);
			path = ft_substr(g_mini->str_env[i], 5, length - 5);
			return (path);
		}
	}
	return (NULL);
}

char	*cd_fd(t_shell *g_mini)
{
	char	*path;

	path = NULL;
	if (g_mini->split_buf[1])
		g_mini->cd = chdir(g_mini->split_buf[1]);
	else
	{
		path = check_cd(g_mini);
		g_mini->cd = chdir(path);
		free(path);
	}
	return (path);
}

int	ft_cd(t_shell *g_mini)
{
	char	*path;
	char	*buf;
	char	*str;
	char	*tmp;

	buf = NULL;
	tmp = getcwd(buf, 4096);
	str = ft_strjoin("OLDPWD=", tmp);
	free(tmp);
	path = cd_fd(g_mini);
	if (g_mini->cd < 0)
	{
		cd_error(errno, g_mini, path);
		free(str);
	}
	else
	{
		cd_oldpwd_pwd(g_mini, str);
		g_mini->ft_errno = 0;
	}
	tmp = getcwd(buf, 4096);
	str = ft_strjoin("PWD=", tmp);
	free(tmp);
	cd_oldpwd_pwd(g_mini, str);
	return (0);
}
