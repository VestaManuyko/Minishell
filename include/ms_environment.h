/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_environment.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:24:15 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/25 14:13:03 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ENVIRONMENT_H
# define MS_ENVIRONMENT_H

# include "ms_structs.h"

/* 
 * Given the environment array search for the id of the string that
 * begins with *key.
 *
 * RETURNS:
 * - the id of the string in the array on success;
 * - -1 in case the *key is not found.
 */
int		env_getid(char **arr, char *key);

/* 
 * Given an id found with env_getid, stores at the address of **str
 * a copy of the value found after the '=' sign.
 *
 * RETURNS:
 * - 1	on success, please note that a NULL is returned if no data
 * 		is stored as value.
 * - 0	in case of error.
 */
int		env_getvalue(char **arr, char **str, int id);

/* 
 * Modifies the env array based on the provided string.
 * if the key is not found the string is appended in its entirety
 * else it's substituted with the new string.
 *
 * RETURNS:
 * - 1 on success;
 * - 0 on error, please note the source env, str will need to be free'd
 *     by the caller. 
 */
int		env_entry_update(t_arr *env, char *key);

/* 
 * Search through the env for the provided key, if found will remove the
 * string from the env array.
 * The key is expanded via str_clearquotes before is analized.
 *
 * RETURNS:
 * - 1 on success
 * - 0 on missing key
 */
int		env_entry_remove(t_arr *env, char *key);

/* 
 * Given a string finds the portion of it that preceeds the equal sign.
 * The key is expanded via str_clearquotes before is analized.
 * The string must be compliant with a valid key structure:      
 * starts with '_' or a ft_isalpha() char and includes only  ft_isalphanum()
 * and '_'.
 * If the original string is empty or the '=' char is the first one, 
 * an error is returned and Errno is set to: EINVAL
 * It is the responsibility of the caller to free the original string.
 *
 * RETURNS:
 * - a pointer to the newly allocated string;
 * - NULL in case the the key is wrongly doesn't respect the convention. 
 */
char	*env_getkey(char *str);

/*
 * From the t_arr environment structure returns a char **array of all
 * the paths included in the environment and separated by the ':' character.
 */
char	**env_getpaths(t_arr *env, t_shell *sh);

#endif
