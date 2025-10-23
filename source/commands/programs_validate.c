/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   programs_validate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:51:58 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/23 12:54:22 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_structs.h"
#include <minishell.h>


int programs_validate(t_shell *sh)
{
	(void)sh;
	/*in this stage we must verify that each first item is a 
	 * proper program.
	 * cases like "." or "/" or "./" > return errors and moves to
	 * the next pipe item.
	 * here some insightfull examples :
		paglia@c1r1p5:~$ |
		bash: syntax error near unexpected token `|'
		fpaglia@c1r1p5:~$ a | |
		bash: syntax error near unexpected token `|'
		fpaglia@c1r1p5:~$ a | .|
		> 
		> a
		bash: .: filename argument required
		.: usage: . filename [arguments]
		a: command not found
		a: command not found
		fpaglia@c1r1p5:~$ .
		bash: .: filename argument required
		.: usage: . filename [arguments]
		fpaglia@c1r1p5:~$ /
		bash: /: Is a directory
		fpaglia@c1r1p5:~$ ./
		bash: ./: Is a directory
		fpaglia@c1r1p5:~$ a | ./
		bash: ./: Is a directory
		a: command not found
	This program should also define if a call is going to a 
	built in!
	 */
	return (1);
}