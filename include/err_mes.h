/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_mes.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:22:40 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/11/17 15:53:55 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_MES_H
# define ERR_MES_H

# define ER_INIT "Error\ninit_shell failure"
# define ER_QUOTES "Error\nminishell: open quotes detected"
# define ER_READLINE "Error\nreadline"
# define ER_PROMPT "Error\nget_prompt"
# define ER_SIGACT "Error\nsigaction"
# define ER_SINTAX "Error\nminishell:  syntax error near unexpected token `"
# define ER_FORK "Error\nfork"
# define ER_CMD "command not found"
# define ER_PERM "Error\nvalidate"
# define ER_MINI "Error\nminishell: "
# define ER_CD "Error\nminishell: cd: "
# define ER_IDENT "not a valid identifier"
# define ER_PIPE "Error\ncreate_pipes failure"
# define ER_CLOSE "Error\nclose failure"
# define ER_NOEXEC "Permission denied"
# define ER_EXP "Error\nminishell: export: "
# define ER_EXIT "minishell: exit: "
# define ER_AC "too many arguments"
# define ER_CDHM "Error\nminishell: cd: HOME not set"
# define ER_CDENV "Error\nminishell: cd: error retrieving current directory"
# define CLOSE_FDS "Close fds"

#endif
