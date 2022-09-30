/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:10:22 by rfelicio          #+#    #+#             */
/*   Updated: 2022/09/30 15:59:26 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	env;
	int		i;

	if (argc != EXPECTED_ARGC)
	{
		ft_putendl_fd(BAD_INPUT USAGE_MSG, e_fd_std_err);
		exit(0);
	}
	if (!ft_env_init(argc, argv, envp, &env))
		ft_error(env.fl_error, &env);
	if (!ft_pipe_init(&env))
		ft_error(env.fl_error, &env);
	if (!ft_executing_infile_pipeline(0, &env))
		ft_error(env.fl_error, &env);
	if (!ft_executing_outfile_pipeline(1, &env))
		ft_error(env.fl_error, &env);
	i = -1;
	while (++i < env.argc)
		wait(NULL);
	ft_mdealloc(&env);
	return (0);
}
