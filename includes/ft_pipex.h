/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:10:46 by rfelicio          #+#    #+#             */
/*   Updated: 2022/09/20 20:08:33 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# define EXPECTED_ARGC 5
# define NEW_LINE '\n'
# define BAD_INPUT "Bad input: \n"
# define USAGE_MSG "pipex usage: ./pipex infile \"cmd1\" \"cmd2\" outfile"

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>

// Enums
enum e_bool
{
	false,
	true
};

enum e_error_msg_codes
{
	e_bad_input = 0,
};

enum e_fd
{
	e_ft_std_in,
	e_fd_std_out,
	e_ft_std_err
};

// Errors
void	ft_error(int error_code);

// Put strings
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);

#endif
