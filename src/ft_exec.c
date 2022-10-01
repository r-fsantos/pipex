/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:22:53 by rfelicio          #+#    #+#             */
/*   Updated: 2022/10/01 00:14:38 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	ft_exec(int pipe_index, t_env *env)
{
	char	**cmd;

	if (!ft_args_init(pipe_index, env))
		return (false);
	cmd = env->cmd.args;
	if (is_awk(env))
	{
		ft_parsing_awk(env);
		ft_clean_unused_reference((void **)cmd);
	}
	else if ((cmd_has_any_options(cmd[1]) && single_or_double_quotes(cmd[1]))
		|| (cmd_has_any_options(cmd[2]) && single_or_double_quotes(cmd[2])))
		ft_parsing_options(env);
	ft_set_executable_path(env);
	if (execve(env->cmd.path, env->cmd.args, env->paths) == -1)
	{
		env->fl_error = e_execve_cmd_not_found_error;
		return (false);
	}
	return (true);
}

int	ft_args_init(int arg_index, t_env *env)
{
	char	*arg;

	if (!arg_index && !(*(env->argv[arg_index + 2])))
	{
		env->fl_error = e_no_args_to_execute;
		return (false);
	}
	arg = env->argv[arg_index + PIPEX_INFILE_OFFSET];
	env->cmd.args = ft_split_arg_and_options(arg);
	if (arg_index & !(*(env->cmd.args)))
	{
		env->fl_error = e_no_args_to_execute;
		return (false);
	}
	env->bin = ft_strdup(env->cmd.args[0]);
	return (true);
}
