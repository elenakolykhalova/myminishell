/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:12:07 by mcarry            #+#    #+#             */
/*   Updated: 2021/07/22 17:57:54 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <term.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/stat.h>

typedef struct s_shell
{
	char	**str_env;
	char	**str_exp;
	char	*buffer;
	char	**split_buf;

	char	**pipe_array;
	int		pip;
	int		**pfd;
	pid_t	*pids;
	pid_t	pid;
	char	**path;
	int		arg_buf;
	int		k;
	int		save1;
	int		fd;
	int		flag_n;
	int		flag_rd;
	int		flag_rd2;
	int		flag_rd3;
	int		type_rd;
	int		type_rd_arg;
	int		len_rd;
	int		flag_q;
	int		flag_q1;
	int		ft_errno;
	int		flag_new;
	int		flag_new2;
	int		global_var;
	int		global_var2;
	int		flag_pipe1;
	int		flag_pipe2;
	int		options;
	int		cd;
	int		flag_dol_q;

}				t_shell;

void	init_array(char **envp, t_shell *mini);
int		ft_pwd(t_shell *mini);
int		ft_env(t_shell *mini);
int		ft_unset(t_shell *mini);
int		ft_export(t_shell *mini);
void	ft_exit(t_shell *mini);
void	ft_echo(t_shell *mini);
int		ft_cd(t_shell *mini);

int		check_twin(char **array, char *str, char c);
int		first_el(char *arguments);

int		preparsing(t_shell *mini);
int		parsing(t_shell *mini);

char	**cp_ar(char **array);
void	cp_tmp(char **array, char **tmp);
void	free_list(char **str);
void	free_int(int **str);
int		full_path(t_shell *mini);
void	check_path(t_shell *mini);

void	handler(int num);
void	rl_replace_line (const char *text, int clear_undo);
void	func_pipe(t_shell *mini);
int		pipe_parser(t_shell *mini);

char	**unset_array(char **array, t_shell *g_mini);
char	**create_var(char **array);
char	**turnoff(char **array, char **arguments, char **variable);
char	**record_list(char **array, char **tmp);
int		turnoff_del_arg(char **array, char **arguments, char **variable, int i);
char	**sort_ar(t_shell *g_mini);
void	print_array(char **str_sort);
void	ver_dollar(t_shell *g_mini);
void	dollar(t_shell *g_mini);
int		verified_spacer(t_shell *g_mini, char c);
int		spacer(t_shell *g_mini, char c);
int		ver_breaker_of_words(t_shell *g_mini, char c);
int		breaker_of_words(t_shell *g_mini, char c);
int		find_key(t_shell *g_mini, char *tmp);
void	ver_dollar(t_shell *g_mini);
int		dollar_malloc(t_shell *g_mini);
void	dollar_quote_malloc(t_shell *g_mini, char c);
int		redirect(t_shell *g_mini, int count, char c);
int		redirect_creat(t_shell *g_mini, int count);
int		verified_spacer(t_shell *g_mini, char c);
void	redirect_flags(t_shell *g_mini);
void	redirect_key(t_shell *g_mini, char *filename);
void	pipe_flags_off(t_shell *g_mini);

t_shell	g_mini;

#endif