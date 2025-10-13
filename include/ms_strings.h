/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strings.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:54:02 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/13 16:29:08 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRINGS_H
# define MS_STRINGS_H

# include "ms_structs.h"
# include <sys/types.h>

ssize_t	arr_size(char **arr);
void	arr_free(char **arr);
void	arr_print(char **arr);
char	**arr_deepcpy(char **src);

/* Initializes a t_arr structure with a deepcopy of the input array.
 * It's the responsibility of the caller to free the source array.
 * If the parameter is passed as NULL an empty array of size 8 will be built.
 */
t_arr	*tar_init(char **src);

/* Add a copy of the given string is appended at the end of the array.
 * if the array reaches it's capacity the funct will automatically double it.
 * Please note the original string is not free'd
 * 
 * RETURNS:
 * - 1 on success;
 * - 0 on error, please note the t_arr* is not free'd;
 */
int		tar_putone(t_arr *tar, char *str);

/* Remove an item from the t_arr and rebase all the other strings to keep 
 * the content contiguous.
 * 
 * RETURNS:
 * - 1 on success;
 * - 0 in case the array is empty or the id is beyond the size of the array. 
 */
int		tar_popone(t_arr *tar, int id);

/* Given a string that includes any pair of quotes, a new string 
 * cleared from the paired quotes is returned.
 * In case a '$' sign is found within a region without quotes or within 
 * double quotes it's value is searched in the environment and if found
 * returned to the string.
 * special charaters after '$' sign such as '?' or '$' will also be resolved.
 *
 * RETURNS:
 * - a pointer to the realized string in case of success;
 * - a NULL pointer on failure.
 */ 
char	*str_clearquotes(t_arr *env, char *str);

#endif
