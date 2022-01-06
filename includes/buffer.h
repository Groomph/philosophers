/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:30:16 by rsanchez          #+#    #+#             */
/*   Updated: 2021/12/10 00:07:27 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H

# define BUFFER_SIZE 1024

typedef struct s_buffer
{
	int			i;
	int			totalsize;
	char		str[BUFFER_SIZE];
}				t_buff;

int				print_buffer(t_buff *buff, int fd);
void			write_str_buffer(t_buff *buff, const char *str, int size);
void			write_char_buffer(t_buff *buff, char c, int nb);
void			write_longint_buffer(t_buff *buff, long int nb);
void			init_buffer(t_buff *buff);

#endif
