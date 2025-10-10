/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearquotes.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:37:05 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/09 13:05:31 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEARQUOTES_H
# define CLEARQUOTES_H

# include <ms_structs.h>

typedef struct s_quote
{
	t_arr	*env;
	t_arr	*expand;
	int		quote;
}			t_quote;

#endif
