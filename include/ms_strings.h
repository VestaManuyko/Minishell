/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strings.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:54:02 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/26 11:53:19 by fpaglia          ###   ########.fr       */
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
char	*str_clearquotes(char *str, int use_quote, t_shell *sh);

int		str_isquoted_mute(char c, int ignore);

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
			char *str, int use_quote, t_shell *sh);
int		quotes(t_quote *data, char *str, int use_quote);
int		dollar(t_quote *data, char *str, int use_quote);

/* Given a string splitps it's content based on the quotation types:
 * single, double or no quotes and returns a t_arr of t_istr items for further
 * analysis and processing.
 * The intent of this function is to support in the decision making of how to 
 * merge the string back as it my resolve in a string or an array depending on
 * executable to be used.
 * Please see description of the t_istr structure data type to understand
 * the inner content
 */
t_arr	*str_split_by_quote(char *str);

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

/* return an array that is the sum of the 2 given ones.
 * NULL arrays can be passed.
 * in case all the source array are empty an array of size 1 will be returned.
 */
char	**arr_merge(char **arr1, char **arr2);

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

/* Append at the end of dest array all the strings from source array.
 * RETURNS:
 * - 1 on success;
 * - 0 on allocation error;
 */
int		tar_merge_strarr(t_arr *dest, t_arr *src);

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

int		tar_putred(t_arr *arr, char *str, char next);

int		tar_putinfostr(t_arr *arr, char *str, int value, int connect);

void	istr_free(void *item);

/* given a tar of istrings (informed strings) expand every raw to their
 * final value and introduce connectivity informations to determine how
 * each line should be treated.
 */
int		istr_expand_var(t_arr *istr, t_shell *sh);

#endif
