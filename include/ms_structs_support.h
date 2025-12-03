/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_structs_support.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:03:00 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/27 15:48:14 by fpaglia          ###   ########.fr       */
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
	int		*status;
}	t_quote;

typedef struct s_reder
{
	int		quotes;
	t_pipe	proctype;
	int		res;
	t_shell	*sh;

}	t_reder;

#endif
