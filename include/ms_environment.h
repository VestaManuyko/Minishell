/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_environment.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:24:15 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/13 18:50:40 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ENVIRONMENT_H
# define MS_ENVIRONMENT_H

# include "ms_structs.h"

/* Given the environment array search for the id of the string that
 * begins with *key.
 *
 * RETURNS:
 * - the id of the string in the array on success;
 * - -1 in case the *key is not found.
 */
int		env_getid(char **arr, char *key);

/* Given an id found with env_getid, stores at the address of **str
 * a copy of the value found after the '=' sign.
 *
 * RETURNS:
 * - 1	on success, please note that a NULL is returned if no data
 * 		is stored as value.
 * - 0	in case of error.
 */
int		env_getvalue(char **arr, char **str, int id);

/* Modifies the env array based on the parameter string.
 * if the key is not found the string is appended in its entirety
 * else it's substituted with the new string.
 *
 * RETURNS:
 * - 1 on success;
 * - 0 on error, please note the source env, str will need to be free'd
 *     by the caller. 
 */
int		env_entry_update(t_arr *env, char *str);

int		env_entry_remove(t_arr *env, char *key);

char	*env_getkey(char *str);

#endif
