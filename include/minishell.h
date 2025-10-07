/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:36:57 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/10/07 18:25:02 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <libft.h>
# include "ms_structs.h"
# include "ms_strings.h"

/*			STRINGS			*/

/* Used while looping through a string confirms if the current section of   
 * the given string is being under quotes.
 * 
 * RETURNS 
 * - 0 if no quotes are currently open 
 * - ASCII decimal value of the open quote
 */
int		str_isquoted(char c);

/* Collapses a NULL terminated array to a single string.
 * In the process the memory of the original array is freed
 */
char	*arr_to_str(char **arr);

/* Given a string, splits it into an array using c as the delimiter.
 * The function takes in consideration the status of the quotes. 
 * char c is only taken in consideration if no quotes are open.
 * The quote analisys can be muted with the boolen eval_quote, 
 * setting it to false to ignore them.
 * 
 * Imporant note: 
 * The function doesn't free the original string. it's the task of the caller
 * to take care of it.
 *
 * RETURNS:
 * A null terminated array. 
 */
char	**arr_split_by_c(char *str, char c, bool eval_quote);

/*			INPUT			*/

/* 
Calls get_prompt, which gets the USER env variable and appends it with 
the shell_prompt, so that readline may display prompt as example:
	USER/minishell>;
then calls readline and appends the returned line to history 
and adds it to the shell->cmd_line string upon success.
Reminder!
	After calling remember to rl_clear_history() and free(shell->cmd_line); 
Return value:
	1 on error, 0 in case of success.
*/
int	get_command(t_shell *shell);

#endif
