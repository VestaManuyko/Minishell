/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strings.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:54:02 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/09 14:36:18 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRINGS_H
# define MS_STRINGS_H

void	arr_free(char **arr);
void	arr_print(char **arr);
int		arr_deepcpy(char **src, char ***dest, int dest_capacity);
t_arr	*tar_init(char **src);
int		tar_putone(t_arr *tar, char *str);
int		tar_popone(t_arr *tar, int id);

int		env_getid(char **arr, char *key);
int		env_getvalue(char **arr, char **str, int id);
char	*str_clearquotes(t_arr *env, char *str);

#endif
