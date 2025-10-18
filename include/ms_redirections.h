/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 01:50:34 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/18 01:50:59 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_REDIRECTIONS_H
# define MS_REDIRECTIONS_H

#include "ms_structs.h"

void	red_perror(char token);
t_red	*red_init(t_redtype type, char *str);
void	red_free(void *item);
t_red	*red_str2struct(char *str);

#endif