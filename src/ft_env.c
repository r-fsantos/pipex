/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 20:14:24 by rfelicio          #+#    #+#             */
/*   Updated: 2022/09/22 06:26:06 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	ft_env_prep(int argc, char **argv, char **envp, t_env *env)
{
	ft_malloc(env);
	env->infile = argv[1];
	if (!is_accessible(env))
		return (false);
	env->error_flag = e_no_error;
	env->argc = argc - 2;
	env->argv = argv;
	env->outfile = argv[argc - 1];
	env->paths = filter(envp, PATH);
	return (true);
}

int	is_accessible(t_env *env)
{
	if (access(env->infile, F_OK) == e_file_not_accessible)
	{
		env->error_flag = e_file_not_accessible;
		return (false);
	}
	return (true);
}
