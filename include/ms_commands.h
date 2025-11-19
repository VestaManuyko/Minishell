/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_commands.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:41:04 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/28 13:25:45 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_COMMANDS_H
# define MS_COMMANDS_H

# include "ms_structs.h"

t_prog	*programs_init(int count);
void	programs_free(t_prog *items, int count);
void	programs_print(t_shell sh);

int		programs_populate(t_shell *sh);
int		program_validate(t_shell *sh, t_prog *proc);

void	cmd_perror(char *pre, char *str, char *err);

/*
 * Given a string evaluates if there are some chars between the portion of it 
 * limited by "|,\n,\0"   
 *
 * RETURNS:
 * - 1 if the portion of string is not empty.
 * - 0 otherwise.
 */
int		cmd_validate_pipes(char *str);

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
int		cmd_str2prog(t_prog *proc, char *str, t_shell *sh);

int		cmd_split_tokens(t_prog *proc, char *str, t_arr *redirect);

/* For each redirection but heredoc, the funciton 
 * takes the string saved in the raw param and expands it 
 * substituting first the env var then clearing the quotes
 * into the val param of the t_red struct.
 * 
 * In case the redirection is an heredoc,
 * the heredoc procedure is called and the path to the 
 * written file is returned.
 */
int		cmd_parse_redirect(t_arr *redirect, t_prog *proc, t_shell *sh);

int		cmd_parse_progs(t_prog *proc, t_shell *sh);

#endif
