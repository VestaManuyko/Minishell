/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strings.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:54:02 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/09 16:10:03 by fpaglia          ###   ########.fr       */
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
 * it's the responsibility of the caller to free the source array.
 * If the parameter is passed as NULL an empty array of size 8 will be built.
 */
t_arr	*tar_init(char **src);

/* Add a copy of the given string is appended at the end of the array.
 * if the array reaches it's capacity the funct will automatically double it.
 * 
 * RETURNS:
 * - 1 on success;
 * - 0 on error, please note the original t_arr is not freed;
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

/* Given the environment array search for the id of the string that 
 * begins with *key.
 * 
 * RETURNS:
 * - the id of the string in the array on success;
 * - -1 in case the *key is not found.
 */
int		env_getid(char **arr, char *key);

/* Given an id found with env_getid, stores in **str a copy of the value 
 * found after the '=' sign.
 * RETURNS:
 * - 1 on success, please note that a NULL is returned if no data 
 * 		is stored as value. 
 * - 0 in case of error.
 */
int		env_getvalue(char **arr, char **str, int id);


char	*str_clearquotes(t_arr *env, char *str);

#endif
