/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 11:38:20 by rfelicio          #+#    #+#             */
/*   Updated: 2022/09/24 11:44:42 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static int	ft_creating_pipe(int pipe_nbr, t_env *env);

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
 **/
int	ft_executing_infile_pipeline(int pipe_nbr, t_env *env)
{
	pid_t	**pfd;
	int		pid;
	int		fd;
	int		ret;

	if (!ft_creating_pipe(pipe_nbr, env))
		return (false);
	pfd = env->pfd;
	pid = fork();
	if (has_error_on(pid, e_forking_error, env))
		return (false);
	if (is_child_process(pid))
	{
		ft_putendl_fd("PROCESSO FILHO!", 1);
		ret = close(pfd[pipe_nbr][FOR_READ]);
		if (has_error_on(ret, e_closing_pipe, env))
			return (false);
		fd = open(env->infile, O_RDONLY);
		if (has_error_on(fd, e_open_infile, env))
			return (false);
	}
	close(pfd[pipe_nbr][FOR_WRITE]);
	return (true);
}

int	ft_executing_outfile_pipeline(void)
{
	return (true);
}

static int	ft_creating_pipe(int pipe_nbr, t_env *env)
{
	if (pipe(env->pfd[pipe_nbr]) == 0)
		return (true);
	env->fl_error = e_creating_pipe;
	return (false);
}
