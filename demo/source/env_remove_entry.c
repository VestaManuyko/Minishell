#include "ms_environment.h"
#include "ms_init.h"
#include "ms_strings.h"
#include <minishell.h>


/* this small demostrator remove from the env the key PATH and LS_COLORS
 */
int main(int ac, char **av, char **env)
{
	t_shell	sh;

	(void)ac;
	(void)av;
	init_shell(&sh, env);
	if (sh.env == NULL)
		return (1);
	arr_print((char**)sh.env->arr);
	env_entry_remove(sh.env, "PATH");
	env_entry_remove(sh.env, "LS_COLORS");
	// env_entry_remove(sh.env, "");
	arr_print((char**)sh.env->arr);
	free_shell(&sh);
	return (0);
}