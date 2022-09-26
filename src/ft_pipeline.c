/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 11:38:20 by rfelicio          #+#    #+#             */
/*   Updated: 2022/09/27 10:28:29 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static int	ft_creating_pipe(int pipe_nbr, t_env *env);
static int	ft_creating_infile_pipeline(int infile_fd, int write_fd_of_pfd,
				t_env *env);
static int	ft_creating_outfile_pipeline(int read_fd_of_pfd, int outfile_fd,
				t_env *env);

/**
 * DESCRIPTION: wrapper/commander responsible for prepare the
 * read/execute pipeline.
 * 		- Creates the pipe instance to be shared;
 * 		- Closes the read pipe. At this point only write is allowed;
 * 		- Creates child processes instances. System calls will be executed
 * 		only on them;
 * 		- Opens the infile;
 * 		- TODO: DESCRIPTION dup2;
 * 		- Perform the system calls and waits for them to finish;
 * 		- Closes the write pipe;
 * INPUT:
 * 		- (int) pipe_nbr. The project is ready to be scalled to multiple
 * 		pipes redirection.
 * 		- (t_env) *env;
 * RETURN: e_bool (true) if no error occurs. Otherwhise, will set
 * the appropriate env->fl_error and then return e_bool (false).
 * 
 * Debugger: // pid = true; if (is_child_process(pid) || pid)
 **/
int	ft_executing_infile_pipeline(int pipe_nbr, t_env *env)
{
	pid_t	**pfd;
	int		pid;
	int		fd;
	int		ret;
	int		wstatus;

	if (!ft_creating_pipe(pipe_nbr, env))
		return (false);
	pfd = env->pfd;
	pid = fork();
	if (has_error_on(pid, e_forking_error, env))
		return (false);
	if (is_child_process(pid))
	{
		ret = close(pfd[pipe_nbr][FOR_READ]);
		if (has_error_on(ret, e_closing_pipe, env))
			return (false);
		fd = open(env->infile, O_RDONLY);
		if (has_error_on(fd, e_open_infile, env))
			return (false);
		if (!ft_creating_infile_pipeline(fd, pfd[pipe_nbr][FOR_WRITE], env))
			return (false);
		if (!ft_exec(pipe_nbr, env))
			return (false);
	}
	wait(&wstatus);
	if (WIFEXITED(wstatus))
		env->fl_error = WEXITSTATUS(wstatus);
	close(pfd[pipe_nbr][FOR_WRITE]);
	return (true);
}

int	ft_executing_outfile_pipeline(int pipe_nbr, t_env *env)
{
	pid_t	**pfd;
	int		pid;
	int		fd;
	int		wstatus;

	if (!ft_creating_pipe(pipe_nbr, env))
		return (false);
	pfd = env->pfd;
	pid = fork();
	if (has_error_on(pid, e_forking_error, env))
		return (false);
	if (!pid)
	{
		fd = open(env->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (has_error_on(fd, e_open_outfile, env))
			return (false);
		if (!ft_creating_outfile_pipeline(pfd[pipe_nbr - 1][0], fd, env))
			return (false);
		if (!ft_exec(pipe_nbr, env))
			return (false);
	}
	wait(&wstatus);
	if (WIFEXITED(wstatus))
		env->fl_error = WEXITSTATUS(wstatus);
	close(pfd[pipe_nbr - 1][FOR_READ]);
	return (true);
}

static int	ft_creating_pipe(int pipe_nbr, t_env *env)
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
static int	ft_creating_infile_pipeline(int infile_fd, int write_fd_of_pfd,
	t_env *env)
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

static int	ft_creating_outfile_pipeline(int read_fd_of_pfd, int outfile_fd,
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
