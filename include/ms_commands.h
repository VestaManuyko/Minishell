/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_commands.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:41:04 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/23 10:30:07 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_COMMANDS_H
# define MS_COMMANDS_H

# include <libft.h>

/*
 * Given a string evaluates if there are some chars between the portion of it 
 * limited by "|,\n,\0"   
 *
 * RETURNS:
 * - 1 if the portion of string is not empty.
 * - 0 otherwise.
 */
int	cmd_validate_pipes(char *str);

#endif
