/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:48:20 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/21 17:17:48 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_strings.h"
#include "ms_structs.h"
#include <minishell.h>

void tpro_print(t_prog pr)
{
	int i = -1;
	t_red *tmp;
	
	printf("=========================>> PROG id:%3d <<========================\n", pr.id );
	printf("go_to: 		%s \n", pr.go_to == end ? "end" : "ispipe");
	printf("redirections: 	\n");
	while (++i < pr.redirect->size)
	{
		tmp = (t_red *)pr.redirect->arr[i];
		if (tmp->type == out_append || tmp->type == out_create)
			 printf("                fo: %s\n", tmp->val);
		else 
			 printf("                fi: %s\n", tmp->val);		
	}
	// printf("fi: %d fo: %d\n", pr.f_stdin, pr.f_stdout);
	printf("===========================>> ARRAY <<============================\n");
	arr_print((char **)pr.prog->arr);
	printf("\n\n");
}

void print_programs(t_shell sh)
{
	int i = 0;

	while (i <sh.count)
	{
		tpro_print(sh.items[i]);
		i++;
	}
}

t_prog *init_progs(int count)
{
	t_prog	*proc;
	proc = (t_prog *)calloc(count, sizeof(t_prog));
	if (proc == NULL)
		return (NULL);
	return (proc);
}

int	red_extract(char **str, char **end, t_arr *tar, int *quotes)
{
	char *line;
	if ( **end == *(*end +1))
		(*end)++;
	while (**end && (*quotes == 0 && ft_isspace(*(*end + 1))))
	{
		(*end)++;
		*quotes = str_isquoted(**end);
	}
	while ((**end && *(*end + 1) != '\0') && ( *quotes != 0 
			|| (ft_strchr(MS_METACHAR, *(*end + 1)) == NULL
			&& ft_strchr(MS_BLANKS, *(*end + 1)) == NULL)))
	{
		(*end)++;
		*quotes = str_isquoted(**end);
	}
	line = ft_strncpy(*str, *end - *str + 1);
	if (line == NULL)
		return (0);
	if (!tar_putred(tar, line))
		return (free(line), 0);
	free(line);
	*str = *end + 1;
	return (1);		
}

int cmd_append(char *str, char *end, t_arr *tar)
{
	char *line;

	line = ft_strncpy(str, end - str +1);
	if (line == NULL)
		return (0);
	if (!tar_putstr(tar, line))
		return (free(line), 0);
	free(line);
	return (1);
}

int	cmd_splitredirect(t_prog *proc, char *str, t_arr *redirect)
{
	char	*end;
	int		quotes;
	int		res;
	
	end = str;
	res = 1;
	while (*str)
	{
		quotes = str_isquoted(*end);
		if (*end && ft_strchr(MS_BLANKS, *end) != NULL)
			str++;
		else if (*str && ft_strchr("<>", *str) != NULL && quotes == 0)
			res = red_extract(&str, &end, redirect, &quotes);
		else if (*(end + 1) == '\0' || (quotes == 0 && (
			ft_strchr(MS_METACHAR, *(end + 1)) || ft_strchr(MS_BLANKS, *(end + 1)))))
		{
			res = cmd_append(str, end, proc->prog);
			str = end + 1;
		}
		if (res == 0)
			return (0);
		end++;
	}
	return (1);
}

int	cmd_fillheredoc(t_red *tmp)
{
	char *path;

	// path = heredoc(tmp->raw, tmp->val);
	path = ft_strdup("MISSING HEREDOC");
	if (path == NULL)
		return (0);
	free(tmp->val);
	tmp->val = path;
	return (1);
}

int cmd_parseredirect(t_arr *redirect, t_prog *proc, t_arr *env)
{
	int		i;
	t_red	*tmp;
	
	(void)proc;
	i = 0;
	while (i < redirect->size)
	{
		tmp = (t_red *)redirect->arr[i];
		if (!red_raw2val(tmp, env))
			return (0);
		if (tmp->type == in_heredoc)
			if (!cmd_fillheredoc(tmp))
				return (0);
		i++;
	}
	return (1);
}

/* this can actually become a pointer to the t_arr redirect included in the 
 * t_prog instead of the single fi | fo. at tge ebd if the day we have to
 * open all of them anyway...
 */
int	cmd_getredirections(t_prog *proc, char *str, t_shell *sh)
{
	proc->redirect = tar_init(NULL, red_free);
	proc->prog = tar_init(NULL, free);
	if (!cmd_splitredirect(proc, str, proc->redirect))
		return (0);
	if (!cmd_parseredirect(proc->redirect, proc, sh->env))
		return (0);
	return (1);
}

int populate_programs(t_shell *sh)
{
	t_arr	*pipes;
	char	**arr;
	int		i;

	arr = str_split_by_set(sh->cmd_line, "|", true);
	if (arr == NULL)
		return (0);
	pipes = tar_init(arr, free);
	arr_free(arr);
	if (pipes->size == 0)
		return (tar_free(pipes), 0);
	sh->items = init_progs(pipes->size);
	sh->count = pipes->size;
	if (sh->items == NULL)
		return (tar_free(pipes), 0);
	i = 0;
	while (i < pipes->size)
	{
		sh->items[i].id = i;
		if (i == pipes->size -1)
			sh->items[i].go_to = end;
		if (!cmd_getredirections(&sh->items[i], pipes->arr[i], sh))
			return (tar_free(pipes), free_progs(&sh->items, pipes->size), 0);
		i++;
	}
	tar_free(pipes);
	return (1);
}

void reset_shell(t_shell *sh)
{
	if (sh == NULL)
		return ;
	if (sh->cmd_line != NULL)
		free(sh->cmd_line);
	free_progs(&sh->items, sh->count);
}

int main(int ac, char **av, char **env)
{
	t_shell	sh;

	(void)ac;
	(void)av;
	if (!init_shell(&sh, env))
	{
		ft_putendl_fd(ER_INIT, 2);
		return (1);
	}
	while (1)
    {
    	if (get_command(&sh))
      	{
        	populate_programs(&sh);
			print_programs(sh);
        	// if (validate_programs(&sh))
			// {
			// 	run_programs(&sh);
			// }
			reset_shell(&sh);
		}
    }
	free_shell(&sh);
}
