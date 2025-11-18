/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell_extract.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:49:37 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/21 16:53:22 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* this function must be replaced with a different one that does the dup2 directly at child execution
 * it is much safer in case of sig coming in there are no risks of keeping fd's open by chance.
 */
int cmd_openfile(t_red *red, t_prog *proc)
{
	if (red->type == out_create || red->type == out_append)
	{
		if (red->type == out_create)
			red->fd = open(red->val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (red->type == out_append)
			red->fd = open(red->val, O_CREAT | O_WRONLY | O_APPEND, 0644);
		proc->f_stdout = red->fd;
	}
	else
	{
		if (red->type == in_file)
			red->fd = open(red->val, O_RDONLY);
		else
		 	red->fd = -1; // TODO: waiting for heredoc function
		proc->f_stdin = red->fd;
	}
	if (red->fd == -1)
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
		if (!red_raw2val(tmp, env))
			return (0);
		if (!cmd_openfile(tmp, proc))
			return (0);
		i++;
	}
	if (!red_closeunusedfd(redirect, proc))
		return (0);
	return (1);		
}
