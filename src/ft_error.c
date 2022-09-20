/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 19:37:22 by rfelicio          #+#    #+#             */
/*   Updated: 2022/09/20 20:04:09 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

/**
 * TODO: Add struct pipex/env/etc
 **/
void	ft_error(int error_code)
{
	ft_putstr_fd("bash: ", e_ft_std_err);
	if (error_code == e_bad_input)
		ft_putendl_fd(BAD_INPUT USAGE_MSG, e_ft_std_err);
	exit(-1);
}
