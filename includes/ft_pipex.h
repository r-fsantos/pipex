/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:10:46 by rfelicio          #+#    #+#             */
/*   Updated: 2022/09/22 21:26:29 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# define EXPECTED_ARGC 5
# define NEW_LINE '\n'
# define BAD_INPUT "Bad input: \n"
# define USAGE_MSG "pipex usage: ./pipex infile \"cmd1\" \"cmd2\" outfile"
# define FILE_NOT_ACCESSIBLE_MSG ": No such file or directory"
# define PATH "PATH="

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
	e_no_error = 0,
	e_bad_input = 1,
	e_env_prep = 2,
	e_file_not_accessible = -1
};

enum e_fd
{
	e_ft_std_in,
	e_fd_std_out,
	e_ft_std_err
};

typedef struct s_env
{
	int		error_flag;
	char	*infile;
	char	*outfile;
	int		argc;
	char	**argv;
	char	**paths;
}	t_env;

// Errors
void	ft_error(int error_code, t_env *env);

// Put strings
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);

// Strings
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);

// Parser
char	**filter(char **env, char *match);

// Env
int		is_accessible(t_env *env);
int		ft_env_init(int argc, char **argv, char **envp, t_env *env);

// Mem
void	ft_malloc(t_env *env);
void	ft_mdealloc(t_env *env);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	ft_doublefree(char **arr);

// Split e Split2 - Remover ao final. Portar libft
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memmove(void *dst, const void *src, size_t len);

#endif
