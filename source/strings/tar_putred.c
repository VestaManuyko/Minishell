
#include "ms_redirections.h"
#include "ms_strings.h"
#include "ms_structs.h"
#include <minishell.h>

int tar_putred(t_arr *arr, char *str)
{
	t_red *item;

	item = red_str2struct(str);
	if (item == NULL)
		return (0);
	if (!tar_linkone(arr, item))
		return (0);
	return (1);
}