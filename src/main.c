/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:10:22 by rfelicio          #+#    #+#             */
/*   Updated: 2022/09/27 20:13:02 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

// TODO: Refactor ft_error. It is possible to set fl_error on t_env instance
int	main(int argc, char **argv, char **envp)
{
	t_env	env;

	if (argc != EXPECTED_ARGC)
		ft_error(e_bad_input, NULL);
	if (!ft_env_init(argc, argv, envp, &env))
		ft_error(e_env_init, &env);
	if (!ft_pipe_init(&env))
		ft_error(e_pipe_init, &env);
	if (!ft_executing_infile_pipeline(0, &env))
		ft_error(env.fl_error, &env);
	if (!ft_executing_outfile_pipeline(1, &env))
		ft_putendl_fd("NOT IMPLEMENTED ERROR: ft_executing_outfile_pipeline",
			1);
	ft_mdealloc(&env);
	return (0);
}
