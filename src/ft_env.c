/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 20:14:24 by rfelicio          #+#    #+#             */
/*   Updated: 2022/09/26 17:40:42 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	ft_env_init(int argc, char **argv, char **envp, t_env *env)
{
	ft_malloc(env);
	env->infile = argv[1];
	if (!is_accessible(env->infile, env))
		return (false);
	env->fl_error = e_no_error;
	env->argc = argc - 3;
	env->argv = argv;
	env->outfile = argv[argc - 1];
	env->paths = filter(envp, PATH);
	return (true);
}

int	is_accessible(char *path, t_env *env)
{
	if (access(path, F_OK) == e_file_not_accessible)
	{
		env->fl_error = e_file_not_accessible;
		return (false);
	}
	return (true);
}

int	ft_pipe_init(t_env *env)
{
	int	**pfd;
	int	i;

	pfd = (int **)ft_calloc((env->argc + 1), sizeof(*pfd));
	if (!pfd)
	{
		env->fl_error = e_pipe_init;
		return (false);
	}
	i = -1;
	while (++i < env->argc)
	{
		pfd[i] = (int *)ft_calloc(READ_WRITE_PIPES, sizeof(int));
		if (!pfd[i])
		{
			env->fl_error = e_pipe_init;
			ft_doublefree((void **)pfd);
			return (false);
		}
	}
	env->pfd = pfd;
	return (true);
}
