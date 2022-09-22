/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 22:12:37 by rfelicio          #+#    #+#             */
/*   Updated: 2022/09/22 00:45:21 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

// TODO: It is really needed to malloc t_env? i'm using the pointer on stack...
// TODO: Talvez seja necessário usar o malloc diretamente, em seguida ft_bzero.
void	ft_malloc(t_env *env)
{
	ft_bzero(env, sizeof(t_env));
}

// Implements double free for **paths
void	ft_mdealloc(t_env *env)
{
	if (env->paths)
		ft_doublefree(env->paths);
	ft_putendl_fd("NOT IMPLEMENTED ERROR: Memory deallocation!",
		e_ft_std_err);
}

void	ft_bzero(void *s, size_t n)
{
	if (n != 0)
		ft_memset(s, 0, n);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (len--)
		*ptr++ = (unsigned char)c;
	return (b);
}

void	ft_doublefree(char **arr)
{
	while (*arr++)
	{
		free(*arr);
		*arr = NULL;
	}
	arr = NULL;
}
