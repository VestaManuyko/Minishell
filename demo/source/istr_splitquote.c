#include "ms_structs.h"
#include <minishell.h>
sig_atomic_t volatile g_return = 0;

void print_istr(t_arr *istr)
{
	int i;
	t_istr *tmp;

	i = 0;
	while (i < istr->size)
	{
		tmp = (t_istr *)istr->arr[i];
		printf("quotes: %c\tconnectivity: %d\n%s\n-----------------\n", 
			tmp->type, tmp->connect, tmp->str);
		i++;
	}

}

int main(int ac, char **av, char **env)
{
	t_shell	sh;
	t_arr	*istr;

	(void)ac;
	(void)av;
	if (!init_shell(&sh, env))
		return (ft_putendl_fd(ER_INIT, 2), 1);
	signal_set(0, &sh);
	while (g_return != -1)
    {
    	if (get_command(&sh))
      	{
			istr = str_split_by_quote(sh.cmd_line);
			if (istr == NULL)
				break;
			print_istr(istr);
		}
		else
			break ;
    }
	free_shell(&sh);
	return (0);
}