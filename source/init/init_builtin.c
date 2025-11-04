/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:43:23 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/27 18:32:39 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_structs.h"
#include <minishell.h>

void	init_bltn_list(t_bltn *list)
{
	list[0] = (t_bltn){"echo", bltn_echo};
	list[1] = (t_bltn){"cd", bltn_cd};
	list[2] = (t_bltn){"pwd", bltn_pwd};
	list[3] = (t_bltn){"export", bltn_export};
	list[4] = (t_bltn){"unset", bltn_unset};
	list[5] = (t_bltn){"env", bltn_env};
	list[6] = (t_bltn){"exit", bltn_exit};
}
