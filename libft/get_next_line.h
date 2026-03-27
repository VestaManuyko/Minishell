/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 09:32:32 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/28 11:16:49 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

typedef struct s_gnl
{
	char	buff[BUFFER_SIZE];
	int		b_id;
	int		b_len;
	char	*line;
	int		l_ch;
	int		l_cap;
}	t_gnl;

#endif
