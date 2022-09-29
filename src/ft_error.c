/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 19:37:22 by rfelicio          #+#    #+#             */
/*   Updated: 2022/09/28 21:53:03 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static int	has_any_pipe_error(int error_code);
static int	has_any_dup_error(int error_code);
static void	ft_puterror_msg_to_std_err(char *left_join_msg,
				char *right_join_msg, int *exit_code, int e_error_code);

int	has_error_on(int operation_return, int error_code, t_env *env)
{
	if (operation_return != -1)
		return (false);
	env->fl_error = error_code;
	return (true);
}

void	ft_error(int error_code, t_env *env)
{
	int		exit_code;

	exit_code = -1;
	ft_putstr_fd("bash: ", e_fd_std_err);
	if (error_code == e_bad_input || error_code == e_no_args_to_execute)
		ft_putendl_fd(BAD_INPUT USAGE_MSG, e_fd_std_err);
	if (error_code == e_open_infile || error_code == e_open_outfile)
		ft_puterror_msg_to_std_err(FILE_NOT_ACCESSIBLE_MSG, env->infile,
			&exit_code, e_open_infile);
	if (error_code == e_file_not_accessible)
		ft_puterror_msg_to_std_err(PERMISSION_DENIED, env->infile,
			&exit_code, e_file_not_accessible);
	if (has_any_pipe_error(error_code))
		ft_putendl_fd(PIPE_INIT_ERROR, e_fd_std_err);
	if (error_code == e_forking_error)
		ft_putendl_fd(FORKING_ERROR, e_fd_std_err);
	if (has_any_dup_error(error_code))
		ft_putendl_fd(DUP2_ERROR, e_fd_std_err);
	if (error_code == e_execve_cmd_not_found_error)
		ft_puterror_msg_to_std_err(CMD_NOT_FOUND, env->cmd.args[0],
			&exit_code, e_execve_cmd_not_found_error);
	if (error_code == e_calloc_error)
		ft_putendl_fd(MEMORY_ERROR, e_fd_std_err);
	ft_mclean(NULL, env);
	exit(exit_code);
}

static void	ft_puterror_msg_to_std_err(char *left_join_msg,
	char *right_join_msg, int *exit_code, int e_error_code)
{
	char	*msg;

	msg = ft_strjoin(left_join_msg, right_join_msg);
	ft_putendl_fd(msg, e_fd_std_err);
	*exit_code = e_error_code;
	ft_singlefree((void *)msg);
}

static int	has_any_pipe_error(int error_code)
{
	return (error_code == e_pipe_init
		|| error_code == e_creating_pipe
		|| error_code == e_closing_pipe);
}

static int	has_any_dup_error(int error_code)
{
	return (error_code == e_dup2_write_fd_of_pfd_to_stdout
		|| error_code == e_dup2_infile_to_stdin
		|| error_code == e_dup2_read_fd_of_pfd_to_stdout
		|| error_code == e_dup2_outfile_to_stdout);
}
