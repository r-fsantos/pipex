/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 22:48:50 by rfelicio          #+#    #+#             */
/*   Updated: 2022/09/30 12:28:48 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	has_silent_errors_on_wait_or_close_pipe(int closing_fd, t_env *env)
{
	int	ret;
	int	wstatus;

	wait(&wstatus);
	if (WIFEXITED(wstatus))
		env->fl_error = WEXITSTATUS(wstatus);
	ret = close(closing_fd);
	if (has_error_on(ret, e_closing_pipe, env))
		return (false);
	return (true);
}

int	ft_creating_pipe(int pipe_nbr, t_env *env)
{
	if (pipe(env->pfd[pipe_nbr]) == 0)
		return (true);
	env->fl_error = e_creating_pipe;
	return (false);
}

/**
 * TODO: adds definition for dup2. Its quite interesting and challenging to do!
 * Debugger: 
 * 	ft_putstr_fd("ft_creating_infile_pipeline - write_fd_of_pfd: ", 1);
 * 	ft_putchar_fd(write_fd_of_pfd + 48, 1);
 * 	ft_putendl_fd("", 1);
 **/
int	ft_creating_infile_pipeline(int infile_fd, int write_fd_of_pfd, t_env *env)
{
	if (dup2(infile_fd, STDIN_FILENO) == -1)
	{
		env->fl_error = e_dup2_infile_to_stdin;
		return (false);
	}
	if (dup2(write_fd_of_pfd, STDOUT_FILENO) == -1)
	{
		env->fl_error = e_dup2_write_fd_of_pfd_to_stdout;
		return (false);
	}
	return (true);
}

int	ft_creating_outfile_pipeline(int read_fd_of_pfd, int outfile_fd,
	t_env *env)
{
	if (dup2(read_fd_of_pfd, STDIN_FILENO) == -1)
	{
		env->fl_error = e_dup2_read_fd_of_pfd_to_stdout;
		return (false);
	}
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
	{
		env->fl_error = e_dup2_outfile_to_stdout;
		return (false);
	}
	return (true);
}
