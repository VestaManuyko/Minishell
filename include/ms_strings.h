/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strings.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:54:02 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/13 15:49:42 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRINGS_H
# define MS_STRINGS_H

# include "ms_structs.h"
# include "ms_structs_support.h"
# include <sys/types.h>

/****************************************************************************
 *                     STRINGS, ARRAYS & META ARRAYS (t_arr)                *
 *                                                                          *
 * This file includes the definition of the functions that manipulate       *
 * strings (char*), array of strings (char**) and arrays that can accept    *
 * any type of content. The array itself is type defined as t_arr* and      *
 * its function are prefixed with tar.                                      *
 *                                                                          *
 ***************************************************************************/

/************************************************
 *                    STRINGS                   *
 ***********************************************/

/* Given a string that includes any pair of quotes, a new string 
 * cleared from the paired quotes is returned.
 * In case a '$' sign is found within a region without quotes or within 
 * double quotes it's value is searched in the environment and if found
 * returned to the string.
 * special charaters after '$' sign such as '?' will also be resolved.
 *
 * RETURNS:
 * - a pointer to the realized string in case of success;
 * - a NULL pointer on failure.
 */
char	*str_clearquotes(t_arr *env, char *str, int use_quote);

/* 
 * Given a string returns a new string based on the pointer function given.
 * currently there are 2 available pointer functions that can be used:
 * quotes:	to clear the content from any quote type
 * dollar:	to expand to the env var or special char paired with the $ sign.
 * 			currently the $$ and $? are not yet returned. 
 *
 * RETURNS:
 * - a pointer to the realized string in case of success;
 * - a NULL pointer on failure.
 */
char	*str_expand(int (*f)(t_quote *data, char *str, int use_quote),
			t_arr *env, char *str, int use_quote);
int		quotes(t_quote *data, char *str, int use_quote);
int		dollar(t_quote *data, char *str, int use_quote);

/*
 ************************************************
 *                    ARRAYS                    *
 ***********************************************/

ssize_t	arr_size(char **arr);
void	arr_free(char **arr);
void	arr_print(char **arr, char separator, int newline);
char	**arr_deepcpy(char **src);

/* return an array size that is double the size of the give capacity 
 */
void	**arr_double(void **src, int capacity);

/*
 ************************************************
 *                META ARRAYS (TAR)             *
 ***********************************************/

/* Initializes a t_arr structure of a void **arr and its metadata.
 * If the parameter is passed as NULL an empty array of size 8 *(void *) 
 * will be built.
 * If a char **arr is passed to it a deepcopy of the input array 
 * will be performed and can be used by casting it.
 * It's the responsibility of the caller to free the source array.
 * as it is a void type of data also a method to free the items must be
 * passed to inform the free tool on how to use such data type.
 * The method should be able to free the content stored in each pointer.
 */
t_arr	*tar_init(char **src, void (*u_free)(void *item));

void	tar_free(t_arr *tar);
void	tar_print_char(t_arr *tar);

/* Append a copy of the string *str at the end of the t_arr.
 * if the array reaches it's capacity the funct will automatically double it.
 * Please note the original string is not free'd
 * 
 * RETURNS:
 * - 1 on success;
 * - 0 on error, please note the t_arr* is not free'd;
 */
int		tar_putstr(t_arr *tar, char *str);

/* Remove an item from the t_arr and rebase all the other strings to keep 
 * the content contiguous.
 * 
 * RETURNS:
 * - 1 on success;
 * - 0 in case the array is empty or the id is beyond the size of the array. 
 */
int		tar_popone(t_arr *tar, int id);

/* This function is to be considered an itermediate step to build 
 * functions that are closer to the business level.
 * the goal of this function is to provide a mechanism to attach any datatype
 * to a t_arr.
 */
int		tar_linkone(t_arr *tar, void *item);

int		tar_putred(t_arr *arr, char *str);

#endif
