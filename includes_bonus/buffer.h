/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:30:16 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/09 21:17:24 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H

# define BUFFER_SIZE 50

typedef struct s_buffer
{
	int			i;
	char		str[BUFFER_SIZE];
}				t_buff;

int				print_buffer(t_buff *buff, int fd);
void			write_str_buffer(t_buff *buff, const char *str, int size);
void			write_char_buffer(t_buff *buff, char c, int nb);
void			write_longint_buffer(t_buff *buff, long int nb);
void			init_buffer(t_buff *buff);

#endif
