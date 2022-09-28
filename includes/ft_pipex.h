/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelicio <rfelicio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:10:46 by rfelicio          #+#    #+#             */
/*   Updated: 2022/09/28 11:01:46 by rfelicio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# define EXPECTED_ARGC 5
# define READ_WRITE_PIPES 2
# define FOR_READ 0
# define FOR_WRITE 1
# define PIPEX_INFILE_OFFSET 2
# define NEW_LINE '\n'
# define BAD_INPUT "Bad input: \n"
# define USAGE_MSG "pipex usage: ./pipex infile \"cmd1\" \"cmd2\" outfile"
# define FILE_NOT_ACCESSIBLE_MSG "No such file or directory: "
# define PATH "PATH="
# define PIPE_INIT_ERROR "On create pipes and/or mem allocation"
# define FORKING_ERROR "On forking new processes"
# define CMD_NOT_FOUND "command not found: "
# define PERMISSION_DENIED "permission denied: "

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
	e_file_not_accessible = -1,
	e_no_error = 0,
	e_bad_input = 1,
	e_env_init = 2,
	e_pipe_init = 3,
	e_creating_pipe = 4,
	e_forking_error = 5,
	e_closing_pipe = 6,
	e_open_infile = 7,
	e_dup2_infile_to_stdin = 8,
	e_dup2_write_fd_of_pfd_to_stdout = 9,
	e_no_args_to_execute = 10,
	e_calloc_error = 11,
	e_dup2_read_fd_of_pfd_to_stdout = 12,
	e_dup2_outfile_to_stdout = 13,
	e_open_outfile = 14,
	e_execve_cmd_not_found_error = 127,
};

enum e_fd
{
	e_fd_std_in,
	e_fd_std_out,
	e_fd_std_err
};

typedef struct s_cmd
{
	char	*path;
	char	**args;
}	t_cmd;

typedef struct s_env
{
	int		fl_error;
	char	*infile;
	char	*outfile;
	int		argc;
	char	**argv;
	char	**paths;
	int		**pfd;
	t_cmd	cmd;
	char	*bin;
}	t_env;

// Errors
void	ft_error(int error_code, t_env *env);
int		has_error_on(int operation_return, int error_code, t_env *env);

// Put strings
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);

// Strings
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);

// Akw parsing
int		is_awk(void);

// Parser
char	**filter(char **env, char *match);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split_arg_and_options(char *arg);
int		cmd_has_any_options(char *str);
int		single_or_double_quotes(char *str);
int		ft_parsing_options(t_env *env);
int		ft_args_init(int arg_index, t_env *env);
char	*ft_pathjoin(char *s1, char *s2);
char	*ft_get_filepath(t_env *env);
void	ft_set_executable_path(t_env *env);

// Env
int		is_accessible(char *path, t_env *env);
int		ft_env_init(int argc, char **argv, char **envp, t_env *env);
int		ft_pipe_init(t_env *env);

// Mem
void	ft_singlefree(void *arr);
void	ft_mclean(char *buf, t_env *env);
void	ft_malloc(t_env *env);
void	ft_mdealloc(t_env *env);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	ft_doublefree(void **arr);

// Split e Split2 - Remover ao final. Portar libft
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memmove(void *dst, const void *src, size_t len);

// Process
int		is_child_process(int id);

// Pipeline
int		ft_executing_infile_pipeline(int pipe_nbr, t_env *env);
int		ft_executing_outfile_pipeline(int pipe_nbr, t_env *env);

// Exec
int		ft_exec(int pipe_index, t_env *env);

#endif
