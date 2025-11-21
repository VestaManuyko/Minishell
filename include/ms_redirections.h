/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 01:50:34 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/23 13:50:21 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_REDIRECTIONS_H
# define MS_REDIRECTIONS_H

# include "ms_structs.h"

/* Initialize a t_red* struct.
 * parametere:
 * - type:		a t_redtype is to set the value of the redirection, 
 * 				none is used as default (read as error if not modified)
 * - raw:		if not NULL links the incomint str to the field char *raw.
 */
t_red	*red_init(t_redtype type, char *raw);

void	red_free(void *item);

void	red_perror(char token);

/* Given a string that includes the redirection char as str[0,1], 
 * convert the symbol into its t_redtype enum to define the redirection.
 * put in the remaining string (cleaned by any unquoted blank) into
 * the field char *raw.
 */
t_red	*red_str2struct(char *str);

/* Expands into the val field the data set in the raw field.
 * $ and quotes are getting expanded with the exception of the heredoc case
 * where only quotes are expanded.
 */
int		red_raw2val(t_red *item, t_shell *sh);

#endif