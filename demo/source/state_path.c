/* The goal of this demo is to evaluate if the given path is
 * a directory, a file or doesn't exist at all.
 */

 #include "libft.h"
#include "ms_structs.h"
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
 #include <minishell.h>
#include <unistd.h>

sig_atomic_t volatile g_return;

 int main(int ac, char **av, char **env)
 {
	int ret;
	struct stat info;
	t_shell sh;
	
	init_shell(&sh, env);
	get_command(&sh);
	char **line = str_split_by_set(sh.cmd_line, MS_BLANKS, 0);
	ret = stat(line[0], &info);
	if (ret == -1)
		perror("stat");
	else
		printf("%d\n", ret);
	if S_ISDIR(info.st_mode)
		printf("minishell: %s Is a directory\n", line[0]);
	if (!(S_ISREG(info.st_mode) || S_ISLNK(info.st_mode)))
		printf("Minishell: %s permissione denied\n", line[0]);
	if (access(line[0], X_OK) == -1)
		printf("Minishell: %s permissione denied\n", line[0]);
	if (execve(av[1], line, env) == -1)
		perror("minishell"), printf("errno: %d\n", errno);
	return (0);
 }