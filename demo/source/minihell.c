/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:48:20 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/20 14:49:43 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_init.h"
#include "ms_redirections.h"
#include "ms_strings.h"
#include "ms_structs.h"
#include <minishell.h>
#include <fcntl.h>
#include <stdbool.h>

void tpro_print(t_prog pr)
{
	printf("id: %d, go_to: %s \n", pr.id, pr.go_to == end ? "end" : "ispipe");
	arr_print(pr.prog);
	printf("=================================================================\n");
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
	while (**end && (quotes == 0 && ft_isspace(**end)))
	{
		(*end)++;
		*quotes = str_isquoted(**end);
	}
	while (**end && (quotes != 0 || ft_strchr(MS_METACHAR, *(*end + 1)) == NULL
			 || ft_strchr(MS_BLANKS, **end) == NULL || *(*end + 1) != '\0'))
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

int	cmd_splitredirections(t_prog *proc, char *str, t_arr *redirect)
{
	char	*end;
	int		quotes;
	int		res;
	
	end = str;
	res = 1;
	while (*str)
	{
		quotes = str_isquoted(*end);
		if (*str && ft_strchr("<>", *str) != NULL && quotes == 0)
			res = red_extract(&str, &end, redirect, &quotes);
		else if (*(end + 1) == '\0' || (quotes == 0 && (
			ft_strchr(MS_METACHAR, *(end + 1)) || ft_strchr(MS_BLANKS, *(end + 1)))))
		 	res = cmd_append(str, end, proc->prog);
		if (res == 0)
			return (0);
		end++;
	}
	return (1);
}

int red_expandvalue(t_red *item, t_arr *env)
{
	char *line_$;
	char *line_q;

	line_$ = str_expand(dollar, env, item->raw);
	if (line_$ == NULL)
		return (0);
	line_q = str_expand(quotes, env, line_$);
	free(line_$);
	if (line_q == NULL)
		return (0);
	item->val = line_q;
	return (1);
}

int red_openfile(t_red *item, t_prog *proc)
{
	if (item->type == out_create || item->type == out_append)
	{
		if (item->type == out_create)
			item->fd = open(item->val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (item->type == out_append)
			item->fd = open(item->val, O_CREAT | O_WRONLY | O_APPEND, 0644);
		proc->f_stdout = item->fd;
	}
	else
	{
		if (item->type == in_file)
			item->fd = open(item->val, O_RDONLY);
		else
		 	item->fd = -1; // TODO: waiting for heredoc function
		proc->f_stdin = item->fd;
	}
	if (item->fd == -1)
		return (0);
	return (1);
}	

int red_closeunusedfd(t_arr *redirect, t_prog *proc)
{
	int		i;
	t_red	*tmp;
	
	i = 0;
	while (i < redirect->size)
	{
		tmp = (t_red *)redirect->arr[i];
		if (tmp->type == out_create || tmp->type == out_append)
		{
			if (tmp->fd != proc->f_stdout)
			{
				tmp->fd = close(tmp->fd);
				if (tmp->fd == -1)
				return (0);	
			}
		}
		else
		{
			if (tmp->fd != proc->f_stdin)
			{
				tmp->fd = close(tmp->fd);
				if ( tmp->fd == -1)
				return (0);	
			}
		}
		i++;
	}
	return (1);
}


int cmd_openredirections(t_arr *redirect, t_prog *proc, t_arr *env)
{
	int		i;
	t_red	*tmp;
	
	i = 0;
	while (i < redirect->size)
	{
		tmp = (t_red *)redirect->arr[i];
		if (!red_expandvalue(tmp, env))
			return (0);
		if (!red_openfile(tmp, proc))
			return (0);
		i++;
	}
	if (!red_closeunusedfd(redirect, proc))
		return (0);
	return (1);		
}

int	cmd_getredirections(t_prog *proc, char *str, t_shell *sh)
{
	t_arr	*redirect;
	
	redirect = tar_init(NULL, red_free);
	proc->prog = tar_init(NULL, free);
	if (!cmd_splitredirections(proc, str, redirect))
		return (tar_free(redirect), tar_free(proc->prog), 0);
	if (!cmd_openredirections(redirect, proc, sh->env))
		return (tar_free(redirect), tar_free(proc->prog), 0);
	tar_free(redirect);
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
		if (!cmd_getredirections(&sh->items[i], pipes->arr[i], sh))
			return (tar_free(pipes), free_progs(sh->items, pipes->size), 0);
		i++;
	}
	return (1);
}

#include <minishell.h>

int main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	if (!init_shell(&shell, env))
	{
		ft_putendl_fd(ER_INIT, 2);
		return (1);
	}
	while (1)
    {
    	if (get_command(&shell))
      	{
        	populate_programs(&shell);
        	// if (validate_programs(&shell))
			// {
			// run_programs(&shell);
			// free_programs(&shell);
			// }
		}
    }
}


/* Compile the code then do the following:
 * echo 'cd $HOME $"H"\'O\'M"E" '\\t    ' | ls -a -l -s" | grep *.out |" wc -l' > lines.txt
 * minihell.out lines.txt | cat -e
 */
 /*
int main(int ac, char **av, char **env)
{
	int fd;
	char *line;
	char *expanded_line;
	t_arr *proc_line;
	t_arr *my_env = tar_init(env);
	t_prog *proc;
	t_shell shell;
	int i = 0;
	int j = 0;

	if (ac != 2)
	{
		printf("usage: minihell.out {file_with_commans}\n");
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		proc_line = tar_init(str_split_by_c(line, '|', 1));
//		arr_print(proc_line->arr);
		printf("commands: %s \n", line);
		proc = (t_prog *)malloc((proc_line->size + 1) * sizeof(t_prog));
		while (i < proc_line->size)
		{
			j = 0;
			(proc + i)->id = i;
			if (i < proc_line->size -1)
				(proc + i)->go_to = ispipe;
			else
				(proc + i)->go_to = end;
			(proc + i)->prog = str_split_by_c((proc_line->arr)[i], ' ', 1);
			while ((proc + i)->prog[j] != NULL)
			{
				expanded_line = (proc+ i)->prog[j];
				expanded_line = str_clearquotes(my_env, (proc+ i)->prog[j]);
				free((proc + i)->prog[j]);
				(proc + i)->prog[j] = expanded_line;
				j++;
			}
			(proc + i)->complete = 0;
			(proc + i)->cpid = 0;
			i++;
		}
		i = 0;
		while (i < proc_line->size)
		{
			tpro_print(proc[i]);
			i++;
		}
		free(line);
		arr_free(proc_line->arr);
		free(proc_line);
		free(proc);
	}
	return (0);
	
}
*/