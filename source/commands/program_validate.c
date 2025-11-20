/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_validate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:51:58 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/17 12:32:31 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_valid_file(char *exec);

/* Verify if the executable matches any of the available built ins.
 * If true set the param bltin of the t_prog* to the appropriate 
 * pointer function it relates to.
 * 
 * RETURN:
 * 1 on function match;
 * 0 on no match encountered.
 */
static int	is_builtin(t_shell *sh, t_prog *pr, char *exec)
{
	int		i;
	size_t	size;

	size = ft_strlen(exec);
	i = 0;
	while (i < MS_BUILTINS)
	{
		if (ft_strncmp(sh->bltn[i].name, exec, size) == 0)
		{
			pr->bltin = &sh->bltn[i];
			return (1);
		}
		i++;
	}
	return (0);
}

/* Validate if the string given correspond to a valid executable.
 * 
 * RETURNS:
 * 1 on success
 * 0 on error 
 *
 * errno values are set according to the following logic:
 * EISDIR if the path is a directory
 * EPERM if the path doesn't correspond to a regular file or link
 * EPERM if the file is not accessible in execution by the calling user.
 */
static int	is_valid_path(char *exec, t_shell *sh)
{
	struct stat	info;

	if ((stat(exec, &info)) == -1)
		return (sh->status = 1, 0);
	if S_ISDIR(info.st_mode)
		return (errno = EISDIR, sh->status = EISDIR, 0);
	else if (!(S_ISREG(info.st_mode) || S_ISLNK(info.st_mode)))
		return (errno = EACCES, sh->status = 126, 0);
	else if (access(exec, X_OK) == -1)
		return (errno = EACCES, sh->status = 126, 0);
	return (1);
}

/* Evaluate if the full_path (as a result of one of the env paths joined
 * with the executable name prefixed with a '/') returns a valid executable
 * file.
 * RETURNS:
 * - 0 if the file exists but the caller has no rights to run it
 * - 1 if the file exists and the caller has the rights to run it
 * - 2 in it's not a match
 */
static int	check_exec_path(char *path, char *slash, void **exec, t_shell *sh)
{
	char	*full_path;

	full_path = ft_strjoin(path, slash);
	if (full_path == NULL)
		return (0);
	if (is_valid_file(full_path))
	{
		if (access(full_path, X_OK) == 0)
		{
			free(*exec);
			*exec = full_path;
			return (1);
		}
		else
		{
			cmd_perror(ER_MINI, *exec, ER_NOEXEC);
			sh->status = 126;
			return (free(full_path), 0);
		}
	}
	free(full_path);
	return (2);
}

/* Evaluate if the given executable name matches an actual executable
 * found in one of the search path defined in the environment.
 * if the executable is found modify the entry of the in the t_arr *prog[0] 
 * with the matching found string.
 * 
 * In case the executable is not found prints an error message and 
 * set errno to 127 (same value as BASH).
 * In case is found but permission are not available an error message
 * is also print and the errno is set by the access() funct.
 *
 * RETURNS
 * - 1 if the executable is found
 * - 0 if not found.
 */
int	is_executable(t_arr *env, void **exec, t_shell *sh)
{
	int		ret;
	int		i;
	char	**paths;
	char	*slash;

	slash = ft_strjoin("/", (char *)*exec);
	if (slash == NULL)
		return (0);
	paths = env_getpaths(env, sh);
	if (paths == NULL)
		return (0);
	i = 0;
	while (paths[i] != NULL)
	{
		ret = check_exec_path(paths[i], slash, exec, sh);
		if (ret != 2)
			return (free(slash), arr_free(paths), ret);
		i++;
	}
	free(slash);
	arr_free(paths);
	sh->status = 127;
	cmd_perror("", *exec, ER_CMD);
	return (0);
}

int	program_validate(t_shell *sh, t_prog *proc)
{
	void	**exec;

	if (proc->prog->size == 0)
		return (0);
	exec = &proc->prog->arr[0];
	if (!(ft_strchr(*exec, '/') != NULL))
	{
		is_builtin(sh, proc, *exec);
		if (proc->bltin == NULL)
		{
			if (!is_executable(sh->env, exec, sh))
				return (0);
		}
	}
	else if (!is_valid_path(*exec, sh))
	{
		return (cmd_perror(ER_MINI, *exec, strerror(errno)), 0);
	}
	return (1);
}
