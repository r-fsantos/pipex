/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 22:12:37 by rfelicio          #+#    #+#             */
/*   Updated: 2022/09/27 10:43:54 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static void	ft_free(void *arr);

/**
 * TODO: Handle pipe dealloc
 **/
void	ft_mdealloc(t_env *env)
{
	if (env->paths)
		ft_doublefree((void **)env->paths);
	if (env->pfd)
		ft_doublefree((void **)env->pfd);
	if (env->cmd.args)
		ft_doublefree((void **)env->cmd.args);
	if (env->cmd.path)
		ft_free((void *)env->cmd.path);
}

static void	ft_free(void *arr)
{
	free(arr);
	arr = NULL;
}

void	ft_doublefree(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}
