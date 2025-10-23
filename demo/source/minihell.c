/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:48:20 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/23 11:51:40 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_structs.h"
#include <minishell.h>

void print_a_prog(t_prog pr)
{
	int i = -1;
	t_red *tmp;
	
	printf("\n==================>> PROG id:%2d <<==================\n", pr.id);
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
	printf("\n------------------->> ARRAY <<---------------------\n");
	arr_print((char **)pr.prog->arr);
	printf("\n");
}

void programs_print(t_shell sh)
{
	int i = 0;

	while (i <sh.count)
	{
		print_a_prog(sh.items[i]);
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

int	extract_red(char **str, char **end, t_arr *tar, int *quotes)
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

int append_prog(char *str, char *end, t_arr *tar)
{
	char *line;

	line = ft_strncpy(str, end - str + 1);
	if (line == NULL)
		return (0);
	if (!tar_putstr(tar, line))
		return (free(line), 0);
	free(line);
	return (1);
}

int	cmd_split_redirect(t_prog *proc, char *str, t_arr *redirect)
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
			res = extract_red(&str, &end, redirect, &quotes);
		else if (*(end + 1) == '\0' || (quotes == 0 && (
			ft_strchr(MS_METACHAR, *(end + 1)) || ft_strchr(MS_BLANKS, *(end + 1)))))
		{
			res = append_prog(str, end, proc->prog);
			str = end + 1;
		}
		if (res == 0)
			return (0);
		end++;
	}
	return (1);
}

/* 
 * Takes the path returned by the heredoc function and substitute
 * the value param (originally the EOF pattern) with the 
 * newly created file.
 */
int	cmd_fillheredoc(t_red *tmp)
{
	char *path;

	// path = heredoc(tmp->raw, tmp->val);
	path = ft_strjoin("MISSING HEREDOC | pattern: ", tmp->val);
	if (path == NULL)
		return (0);
	free(tmp->val);
	tmp->val = path;
	return (1);
}

/* For each redirection but heredoc, the funciton 
 * takes the string saved in the raw param and expands it 
 * substituting first the env var then clearing the quotes
 * into the val param of the t_red struct.
 * 
 * In case the redirection is an heredoc,
 * the heredoc procedure is called and the path to the 
 * written file is returned.
 */
int cmd_parse_redirect(t_arr *redirect, t_prog *proc, t_arr *env)
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

/* separate the incoming string of a single process (pipe separated) into 
 * 2 arrays:
 * - redirect:	t_arr that stores all the redirections
 * - prog:		t_arr that stores all the separated tokens that form the
 * 				char** to pass to execve
 * 
 * RETURNS:
 * - 1 on success
 * - 0 on error.
 */
int	cmd_str2prog(t_prog *proc, char *str, t_shell *sh)
{
	proc->redirect = tar_init(NULL, red_free);
	if (proc->redirect == NULL)
		return (0);
	proc->prog = tar_init(NULL, free);
	if (proc->prog == NULL)
		return (0);
	if (!cmd_split_redirect(proc, str, proc->redirect))
		return (0);
	if (!cmd_parse_redirect(proc->redirect, proc, sh->env))
		return (0);
	return (1);
}

t_arr *split_commands(char *str)
{
	t_arr	*cmds;
	char	**arr;
	
	arr = str_split_by_set(str, "|", true);
	if (arr == NULL)
		return (NULL);
	cmds = tar_init(arr, free);
	arr_free(arr);
	if (cmds == NULL)
		return (NULL);
	if (cmds->size == 0)
		return (tar_free(cmds), NULL);
	return (cmds);
}

int programs_populate(t_shell *sh)
{
	t_arr	*cmds;
	int		i;

	if (!cmd_validate_pipes(sh->cmd_line))
		return (0);
	cmds = split_commands(sh->cmd_line);
	if (cmds == NULL)
		return (0);
	sh->count = cmds->size;
	sh->items = init_progs(cmds->size);
	if (sh->items == NULL)
		return (tar_free(cmds), 0);
	i = 0;
	while (i < cmds->size)
	{
		sh->items[i].id = i;
		if (i == cmds->size -1)
			sh->items[i].go_to = end;
		if (!cmd_str2prog(&sh->items[i], cmds->arr[i], sh))
			return (tar_free(cmds), free_progs(sh->items, cmds->size), 0);
		i++;
	}
	tar_free(cmds);
	return (1);
}



int validate_programs()
{
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

	 */
	return (1);
}

int main(int ac, char **av, char **env)
{
	t_shell	sh;
	int i = 0;

	(void)ac;
	(void)av;
	if (!init_shell(&sh, env))
	{
		ft_putendl_fd(ER_INIT, 2);
		return (1);
	}
	while (i < 1)
    {
    	if (get_command(&sh))
      	{
			
			{
			if (!programs_populate(&sh))
				return (free_shell(&sh), 1);
			programs_print(sh);
			}
        	// if (validate_programs(&sh))
			// {
			// 	run_programs(&sh);
			// }
			reset_shell(&sh);
		}
		i++;
    }
	free_shell(&sh);
	return (0);
}
