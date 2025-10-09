/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:48:20 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/09 18:43:52 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <fcntl.h>
void tpro_print(t_prog pr)
{
	printf("id: %d, go_to: %s \n", pr.id, pr.go_to == end ? "end" : "ispipe");
	arr_print(pr.prog);
	printf("=================================================================\n");
}

/* Compile the code then do the following:
 * echo 'cd $HOME | ls -a -l -s" | grep *.out |" wc -l' > lines.txt
 * minihell.out lines.txt | cat -e
 */
int main(int ac, char **av, char **env)
{
	int fd;
	char *line;
	t_arr *proc_line;
	t_prog *proc;
	t_shell shell;
	int i = 0;

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
			(proc + i)->id = i;
			if (i < proc_line->size -1)
				(proc + i)->go_to = ispipe;
			else
				(proc + i)->go_to = end;
			(proc + i)->prog = str_split_by_c((proc_line->arr)[i], ' ', 1);
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
