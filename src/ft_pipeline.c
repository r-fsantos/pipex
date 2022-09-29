/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 11:38:20 by rfelicio          #+#    #+#             */
/*   Updated: 2022/09/28 22:53:03 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

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

	if (!ft_creating_pipe(pipe_nbr, env))
		return (false);
	pfd = env->pfd;
	pid = fork();
	if (has_error_on(pid, e_forking_error, env))
		return (false);
	if (is_child_process(pid))
	{
		fd = close(pfd[pipe_nbr][FOR_READ]);
		if (has_error_on(fd, e_closing_pipe, env))
			return (false);
		fd = open(env->infile, O_RDONLY);
		if (has_error_on(fd, e_file_not_accessible, env))
			return (false);
		if (!ft_creating_infile_pipeline(fd, pfd[pipe_nbr][FOR_WRITE], env))
			return (false);
		if (!ft_exec(pipe_nbr, env))
			return (false);
	}
	return (has_silent_errors_on_wait_or_close_pipe(pfd[pipe_nbr][FOR_WRITE],
		env));
}

int	ft_executing_outfile_pipeline(int pipe_nbr, t_env *env)
{
	pid_t	**pfd;
	int		pid;
	int		fd;

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
	return (has_silent_errors_on_wait_or_close_pipe(pfd[pipe_nbr - 1][FOR_READ],
		env));
}
