/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_structs_support.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:03:00 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/24 12:42:35 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRUCTS_SUPPORT_H
# define MS_STRUCTS_SUPPORT_H

# include <sys/types.h>
# include "ms_structs.h"

/*
 * 							>>>>>	DISCLAIMER:
 * this header file is intended to host structures that have to be shared
 * globally but are not meant to be part of the external api for direct use.
 * any datatype / structure defined here must not need to be initialized in any
 * business logic program developed by an end user.
 */

/* This structure sole purpose is to provide a coincise way to carry on data
 * through multiple functions. It's used solely in the str_expand and its 
 * children function. 
 * 
 */
typedef struct s_quote
{
	t_arr	*env;
	t_arr	*expand;
	int		quote;
}			t_quote;

#endif
