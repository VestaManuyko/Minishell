/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 09:13:23 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/01 10:50:13 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ms_structs.h"

/*			Strings			*/

/* Used while looping through a string confirms if the current section of   
 * the given string is being under quotes.
 * 
 * RETURNS 
 * - 0 if no quotes are currently open 
 * - ASCII decimal value of the open quote
 */
int		str_isquoted(char c);

/*			ARRAYS			*/

/* Collapses a NULL terminated array to a single string.
 * In the process the memory of the original array is freed
 */
char	*arr_to_str(char **arr);

/* Given a string, splits it into an array using c as the delimiter.
 * The function takes in consideration the status of the quotes. 
 * char c is only taken in consideration if no quotes are open.
 * 
 * Imporant note: 
 * The function doesn't free the original string. it's the task of the caller
 * to take care of it.
 *
 * RETURNS:
 * A null terminated array. 
 */
char	**arr_split_by_c(char *str, char c);

#endif
