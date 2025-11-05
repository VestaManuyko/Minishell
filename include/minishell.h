/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 09:13:23 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/05 12:19:12 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <asm-generic/errno-base.h>
# include <fcntl.h>

# include <libft.h>
# include "ms_structs.h"
# include "err_mes.h"
# include "ms_strings.h"
# include "ms_environment.h"
# include "ms_init.h"
# include "ms_redirections.h"
# include "ms_commands.h"

# define MS_METACHAR "\n|&;()<>"
# define MS_BLANKS " \t\n"
# define MS_METAERR "&;()\\"

extern sig_atomic_t volatile	g_return;

/*			STRINGS			*/

/* 
 * Used while looping through a string confirms if the current section of   
 * the given string is being under quotes.
 * 
 * RETURNS 
 * - 0 if no quotes are currently open 
 * - ASCII decimal value of the open quote
 */
int		str_isquoted(char c);

/* 
 * Collapses a NULL terminated array to a single string.
 * if add_space is set to 1 the strings will be concatenated with an 
 * additional space char, if set to 0 the concatenation will be contiguous.
 * 
 * In the process the memory of the original array is freed.
 * 
 * RETURNS:
 * A pointer to a new string on success
 * NULL on faiullure. 
 */
char	*arr_to_str(char **arr, int add_space);

/* 
 * Given a string, splits it into an array using c as the delimiter.
 * The function takes in consideration the status of the quotes. 
 * char c is only taken in consideration if no quotes are open.
 * The quote analisys can be muted with the boolen eval_quote, 
 * setting it to false to ignore them.
 * 
 * Imporant note: 
 * The function doesn't free the original string. it's the task of the caller
 * to take care of it.
 *
 * RETURNS:
 * A null terminated array. 
 */
char	**str_split_by_c(char *str, char c, bool eval_quote);

/*
 * Given a string, splits it into an array using a set of chars as the delimiter.
 * The function takes in consideration the status of the quotes. 
 * the set is only taken in consideration if no quotes are open.
 * The quote analisys can be muted with the boolen eval_quote, 
 * setting it to false to ignore them.
 * 
 * Imporant note: 
 * The function doesn't free the original string. it's the task of the caller
 * to take care of it.
 *
 * RETURNS:
 * A null terminated array. 
 */
char	**str_split_by_set(char *str, char *set, bool eval_quote);

/*			INPUT			*/

/* 
 * Calls get_prompt, which gets the USER env variable and appends it with 
 * the shell_prompt, so that readline may display prompt as example:
 * USER/minishell> ;
 * then calls readline and appends the returned line to history 
 * and adds it to the shell->cmd_line string upon success.
 * Reminder!
 * After calling remember to rl_clear_history() and free(shell->cmd_line); 
 * 
 * Return value:
 * 1 on success, 0 on error.
 * If ctrl D(EOF) encountered cleans up and exits.
 * On system function call error cleans up and exits the shell.
 */
int	get_command(t_shell *shell);

/*
 * Reads input from stdin until a limiter is met into a tmp_file.
 * If limiter was quoted expands the environment variables.
 * Return value:
 * NULL on error, otherwise a freeeable pointer to a string 
 * with tmp_filename.
*/
char	*heredoc(char *raw_limiter, char *limiter, t_arr *env);

/*			INIT			*/

/*
 * Initialisation of the t_shell struct;
 * RETURN:
 * 0 on failure, 1 on success;
 */
int		init_shell(t_shell *shell, char **env);

int		bltn_echo(t_arr *args, t_shell *sh);
int		bltn_cd(t_arr *args, t_shell *sh);
int		bltn_pwd(t_arr *args, t_shell *sh);
int		bltn_export(t_arr *args, t_shell *sh);
int		bltn_unset(t_arr *args, t_shell *sh);
int		bltn_env(t_arr *args, t_shell *sh);
int		bltn_exit(t_arr *args, t_shell *sh);

/*
 * Signal handling for the main shell
 */
void	signal_set(int is_child);

/*     EXECUTION     */

/* Validates if the programs are executable, 
 * if yes executes it and sets the exit value
 * Return value:
 * 0 on error, 1 on success.
 */
void	exec_programs(t_shell *shell);

#endif
