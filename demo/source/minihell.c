/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:48:20 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/17 11:28:54 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_init.h"
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

int	redirection_append(char **str, char **end, t_arr *tar, int *quotes)
{
	char *line;
	if (ft_strchr("<>", *(*end +1)) != NULL)
		(*end)++;
	while (**end && (quotes == 0 && ft_isspace(**end)))
	{
		(*end)++;
		*quotes = str_isquoted(**end);
	}
	while (**end && (quotes != 0 || !ft_isspace(**end)))
	{
		(*end)++;
		*quotes = str_isquoted(**end);
	}
	line = ft_strncpy(*str, *end - *str);
	if (line == NULL)
		return (0);
	if (tar_putone(tar, line))
		return (free(line), 0);
	*str = *end;
	return (1);		
}

int	redirection_extract(t_prog *proc, char *str)
{
	t_arr	fifo[2];
	char	*end;
	int		quotes;
	int		res;
	
	end = str;
	res = 1;
	while (*str)
	{
		quotes = str_isquoted(*end);
		if (*str && ft_strchr("<>", *str) != NULL && quotes == 0)
			res = redirection_append(&str, &end, fifo, &quotes);
		else if (*(end + 1) == '\0' || (ft_strchr("<>", *str) != NULL && quotes == 0))
			res = clearstr_append(&str, &end, fifo[1], &quotes);
		if (res == 0)
			return (tar_free(fifo), tar_free(&fifo[1]), 0);
		end++;
	}	
}

int populate_programs(t_shell *sh)
{
	t_arr	*pipes;
	int		i;

	pipes = tar_init(str_split_by_set(sh->cmd_line, "|", true));
	if (pipes->size == 0)
		return (tar_free(pipes), 0);
	sh->items = init_progs(pipes->size);
	sh->count = pipes->size;
	if (sh->items == NULL)
		return (tar_free(pipes), 0);
	while (i < pipes->size)
	{
		sh->items[i].id = i;
		if (redirection_extract(&sh->items[i], pipes->arr[i]))
			return (tar_free(pipes), free_progs(sh->items, pipes->size), 0);
			
	}
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
        	if (validate_programs(&shell))
			{
			run_programs(&shell);
			free_programs(&shell);
			}
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