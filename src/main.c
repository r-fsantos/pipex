/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:10:22 by rfelicio          #+#    #+#             */
/*   Updated: 2022/09/20 20:11:09 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	main(int argc, char **argv, char **env)
{
	if (argc != EXPECTED_ARGC)
		ft_error(e_bad_input);
	ft_putchar_fd(argc, e_fd_std_out);
	ft_putendl_fd(*argv, e_fd_std_out);
	ft_putendl_fd(*env, e_fd_std_out);
	return (0);
}
