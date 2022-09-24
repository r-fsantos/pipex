/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 19:37:22 by rfelicio          #+#    #+#             */
/*   Updated: 2022/09/24 11:35:12 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static int	has_any_pipe_error(int error_code);
static void	ft_mclean(char *buf, t_env *env);

int	has_error_on(int operation_return, int error_code, t_env *env)
{
	if (operation_return != -1)
		return (false);
	env->fl_error = error_code;
	return (true);
}

/**
 * TODO: ? Improve error handling for env_init? access or malloc?
 **/
void	ft_error(int error_code, t_env *env)
{
	char	*msg;

	msg = NULL;
	ft_putstr_fd("bash: ", e_ft_std_err);
	if (error_code == e_bad_input)
		ft_putendl_fd(BAD_INPUT USAGE_MSG, e_ft_std_err);
	if (error_code == e_env_init)
	{
		msg = ft_strjoin(env->infile, FILE_NOT_ACCESSIBLE_MSG);
		ft_putendl_fd(msg, e_ft_std_err);
	}
	if (has_any_pipe_error(error_code))
		ft_putendl_fd(PIPE_INIT_ERROR, e_fd_std_out);
	if (error_code == e_forking_error)
		ft_putendl_fd(FORKING_ERROR, e_fd_std_out);
	ft_mclean(msg, env);
	exit(-1);
}

static int	has_any_pipe_error(int error_code)
{
	return (error_code == e_pipe_init || error_code == e_creating_pipe);
}

static void	ft_mclean(char *buf, t_env *env)
{
	if (buf)
	{
		free(buf);
		buf = NULL;
	}
	if (env)
		ft_mdealloc(env);
}
