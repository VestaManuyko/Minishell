/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   programs_validate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:51:58 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/24 18:39:37 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_redirections.h"
#include "ms_strings.h"
#include "ms_structs.h"
#include <minishell.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>


/*in this stage we must verify that each first item is a 
	* proper program.
	* cases like "." or "/" or "./" > return errors and moves to
	* the next pipe item.
	* here some insightfull examples :
	paglia@c1r1p5:~$ |
	bash: syntax error near unexpected token `|'
	fpaglia@c1r1p5:~$ a | |
	bash: syntax error near unexpected token `|'
	fpaglia@c1r1p5:~$ a | .|
	> 
	> a
	bash: .: filename argument required
	.: usage: . filename [arguments]
	a: command not found
	a: command not found
	fpaglia@c1r1p5:~$ .
	bash: .: filename argument required
	.: usage: . filename [arguments]
	fpaglia@c1r1p5:~$ /
	bash: /: Is a directory
	fpaglia@c1r1p5:~$ ./
	bash: ./: Is a directory
	fpaglia@c1r1p5:~$ a | ./
	bash: ./: Is a directory
	a: command not found
This program should also define if a call is going to a 
built in!
	*/

int is_path(char *exec)
{
	if (ft_strchr(exec, '/') != NULL)
		return (1);
	return (0);
}

int is_builtin(t_shell *sh, t_prog *pr, char *exec)
{
	int		i;
	size_t	size;
	
	size = ft_strlen(exec);
	i = 0;
	while (i < MS_BUILTINS)
	{
		if (ft_strncmp(sh->bltn[i].name, exec, size) == 0)
			return (pr->bltin = &sh->bltn[i], 1);
		i++;
	}
	return (0);
}

char **env_getpaths(t_arr *env)
{
	char *value;
	char **arr;

	env_getvalue((char **)env->arr, &value,
		env_getid((char **)env->arr, "PATH"));
	if (value == NULL)
		return (NULL);
	arr = str_split_by_set(value, ":", 1);
	free(value);
	if (arr == NULL)
		return (NULL);
	return (arr);
}

int is_valid_path(char *exec)
{
	if (exec[0] == '.')
		return(0);
	return (1);
}

int find_binary(t_arr *env, char **exec)
{
	char	*full_path;
	int		i;
	char	**paths;
	int		perm;
	
	paths = env_getpaths(env);
	if (paths == NULL)
		return (0);
	i = 0;
	while (i < env->size)
	{
		full_path = ft_strjoin(paths[i], *exec);
		if (full_path == NULL)
			return (0);
		perm = access(full_path, F_OK | X_OK);
		if (perm != -1) /* full match*/
		{
			free(*exec);
			*exec = full_path;
			return (arr_free(paths), 1);
		}
		else if (perm == 120)/* exists but no permissions */
			return (arr_free(paths), free(full_path), 0);
		free(full_path);
		i++;
	}
	arr_free(paths);
	return (0);
}


int	programs_validate(t_shell *sh)
{
	int i;
	char *exec;

	i = 0;
	while (i < sh->count)
	{
		exec = sh->items[i].prog->arr[0];
		if (!is_path(exec))
		{
			if (is_builtin(sh, &sh->items[i], exec))
				;
			else if (find_binary(sh->env, &exec) != 1)
				perror(ER_PERM);
			else 
				cmd_perror(exec);			
		}
		else 
			is_valid_path(exec);
	}
	(void)sh;
	return (1);
}
