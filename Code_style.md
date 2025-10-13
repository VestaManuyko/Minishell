______Errors______

ALl error messages to be defined in "err_mes.h" header file as macros with this design:

# define ER_MACRO "message"
Correct usage:
-In case of system error:
message = "Error\nfunction_name"
perror(ER_MACRO);
-In function error:
message = "Error\nfunction_name:[reason if needed]"

____File_names____

Names of the functions includes to minishell.h to be named after what they handle.
Example:
-arr_deepcpy.c
-arr_free.c
-arr_printf.c
