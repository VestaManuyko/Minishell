/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_mes.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:22:40 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/10/27 17:42:58 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_MES_H
# define ERR_MES_H

# define ER_INIT "Error\ninit_shell failure"
# define ER_QUOTES "Error\nreadline: open quotes detected"
# define ER_READLINE "Error\nreadline"
# define ER_PROMPT "Error\nget_prompt"
# define ER_SIGACT "Error\nsigaction"
# define ER_SINTAX "Error\nminishell:  syntax error near unexpected token `"
# define ER_FORK "Error\nfork"
# define ER_WAITPID "Error\nwaitpid"
# define ER_CMD "command not found"
# define ER_PERM "Error\nvalidate"
# define ER_MINI "Error\nminishell: "
# define ER_CD "Error\nminishell: cd: "
# define ER_IDENT "`=': not a valid identifier"

#endif
