/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_commands.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:41:04 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/25 13:42:50 by fpaglia          ###   ########.fr       */
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
int		cmd_str2prog(t_prog *proc, char *str, t_shell *sh, t_arr *cmds);

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
int		cmd_parse_red(t_arr *redirect, t_prog *proc, t_shell *sh, t_arr *cmds);

/* For each t_prog structure expand the input array based on:
 * the usage of variable and quotations returning the final data to 
 * pass to the execution process.
 */
int		cmd_parse_progs(t_prog *proc, t_shell *sh);

/* Take a string and split it in a tarr of strings based on expansion.
 * Any str that is not in quote is expanded as many rows as needed.
 * Connectivity to bridge the first and last token are executed in case
 * no MS_BLANKS are found at the beginning and / or at the end of the
 * string:
 * 0 no connectivity
 * 1 start of str connects with previous;
 * 2 end of str connect with next;
 * 3 both ends are to be reconnected
 */
t_arr	*cmd_elaborate_line(char *str, t_shell *sh);

/* given the program array clears it from quotes and dollar expansion 
 * for any other task but export.
 */
t_arr	*cmd_expand_prog(t_arr *arr, t_shell *sh);

/* given the program array clears it from quotes and dollar expansion 
 * following the rules of the export built in:
 * 
 * case 1: key has no $ or quotes (var=)
 * case 2: key has $ or quotes (var"= ; $var= 'var'=)
 * 
 * case 1 
 * The value will always return a single string regardless MS_BLANK 
 * case 2
 * Key and value will be expanded resulting in an arbitrary 
 * amount of strings depending on the expansion of unquoted variables.
 * 
 * The resulting strings will be owned by the t_arr that will grow as
 * per needs.
 */
t_arr	*cmd_expand_export(t_arr *arr, t_shell *sh);

#endif
