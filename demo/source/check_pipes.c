/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:42:56 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/22 15:46:35 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_commands.h"
#include <minishell.h>

int main()
{
	char str[] = "bla | something |   |  |\n";

	cmd_validate_pipes(str);
	
}