/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 09:13:23 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/27 09:38:02 by fpaglia          ###   ########.fr       */
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

# define MS_METACHAR "\n|<>"
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
 */
int		get_command(t_shell *shell);

/*
 * Prints an error message with perror if not NULL
 * checks if anything needs to be freed and cleans up,
 * then exits.
*/
void	clean_exit(char *message, t_shell *shell, int status);

/*
 * Checks for input containing only spaces or empty input
 * If only spaces or empty returns 1, otherwise 0.
*/
int		is_only_space(char	*line);

/*
 * Reads input from stdin until a limiter is met.
 * If limiter was quoted expands the environment variables.
 * Return value:
 * 0 on error, 1 on success or EOF;
*/
int		heredoc(char *raw_lim, char *limiter, char *tmp_filename, t_shell *sh);

/*
 * Creates a tmp_filename for heredoc using the programs pid
 * and random int number.
 * Return value:
 * NULL on error,
 * freeable pointer to a string containing the tmp_filename.
*/
char	*get_filename(void);

/*
 * Creates tmp_files for the amount of heredocs,
 * then calles a child process, which calls heredoc function
 * for all of the heredoc, that eads from stdin until a delimiter is met
 * and writes into the tmp_file provided.
 * In the parent process waits for the child to terminate, if
 * all the heredocs were succesful and no signal interruption occured
 * during the child process, then sets all the tmp_file named for further
 * redirection execution into the redirect struct and updates
 * the exit status of the child.
 * Return value:
 * 0 on error, 1 on success.
*/
int		handle_heredocs(t_shell *shell, t_arr *redirect, int hd, t_arr *cmds);

/*			INIT			*/

/*
 * Initialisation of the t_shell struct;
 * RETURN:
 * 0 on failure, 1 on success;
 */
int		init_shell(t_shell *shell, char **env);

/*
 * Signal handling for the main shell
 */
void	signal_set(int is_child, t_shell *shell);

/*
 * Hook function to call after a signal interrupted readline.
*/
int		rl_hook(void);

/*
 * Allocates memory for a 2d array of size nbr of commands - 1.
 * Then creates pipes and initialises the 2d array with piped fds.
 * Return value:
 * 0 on error, 1 on success.v
*/
int		create_pipes(t_shell *sh);

/*     EXECUTION     */

/* 
 * Validates if the programs are executable, 
 * if yes executes it and sets the exit status to g_return.
 */
void	exec_programs(t_shell *shell);

/*
 * Called by parent, sets the exit status of a child process.
*/
void	set_status(int status, t_shell *sh);

/*
 * Dup_fds function checks the existing programs fds
 * and calls dup2 if needed for duplicating an fd to stdin or stdout.
 * Return value:
 * 0 on error 1 on success.
*/
int		dup_fds(t_prog *item);

/*
 * Closes fds for redirections.
*/
void	cl_red_fds(t_shell *sh);

/*
 * Close all opened fds.
*/
void	close_fds(t_shell *sh);

/*
 * Called from a child process to close all unused fds by that process.
 * Return value:
 * 0 on error, 1 0n success.
*/
void	close_unused_fds(t_prog *item, t_shell *sh);

/*
 * Checks if the redirection files are valid and
 * sets all the needed fds for execution of a program.
 * Return value:
 * Filename failed to open on error, NULL on success
 * (if no opening file failed).
*/
char	*set_redirect(t_prog *item);

/*
 * Executes a single child process if not built-in.
 * In the parent sets the exit status of the last process.
 * Return value:
 * 0 on error, 1 on success.
*/
int		exec_single(t_shell *shell);

/*
 * Executes multiple programs and redirects the stdin stdout
 * from the pipe between the processes.
 * In the parent sets the exit status of the last process.
 * Return value:
 * 0 on error, 1 on success.
*/
int		exec_pipeline(t_shell *sh);

/*
 * All the built in functions.
*/
int		bltn_echo(t_arr *args, t_shell *sh);
int		bltn_cd(t_arr *args, t_shell *sh);
int		bltn_pwd(t_arr *args, t_shell *sh);
int		bltn_export(t_arr *args, t_shell *sh);
int		bltn_unset(t_arr *args, t_shell *sh);
int		bltn_env(t_arr *args, t_shell *sh);
int		bltn_exit(t_arr *args, t_shell *sh);

#endif
