/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 07:28:28 by rsanchez          #+#    #+#             */
/*   Updated: 2021/12/10 00:12:16 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include <unistd.h>

int	print_buffer(t_buff *buff, int fd)
{
	write(fd, buff->str, buff->i);
	buff->totalsize += buff->i;
	buff->i = 0;
	return (buff->totalsize);
}

void	write_str_buffer(t_buff *buff, const char *str, int size)
{
	int	i2;

	i2 = 0;
	if (size < 0)
	{
		while (str[i2])
		{
			buff->str[buff->i] = str[i2];
			buff->i++;
			i2++;
			if (buff->i == BUFFER_SIZE)
				print_buffer(buff, 1);
		}
	}
	while (i2 < size)
	{
		buff->str[buff->i] = str[i2];
		buff->i++;
		i2++;
		if (buff->i == BUFFER_SIZE)
			print_buffer(buff, 1);
	}
}

void	write_char_buffer(t_buff *buff, char c, int nb)
{
	int	i2;

	i2 = 0;
	while (i2 < nb)
	{
		buff->str[buff->i] = c;
		buff->i++;
		if (buff->i == BUFFER_SIZE)
			print_buffer(buff, 1);
		i2++;
	}
}

void	init_buffer(t_buff *buff)
{
	buff->i = 0;
	buff->totalsize = 0;
}

void	write_longint_buffer(t_buff *buff, long int nb)
{
	if (nb < 0)
	{
		write_char_buffer(buff, '-', 1);
		nb *= -1;
	}
	if (nb >= 10)
		write_longint_buffer(buff, nb / 10);
	write_char_buffer(buff, (nb % 10) + '0', 1);
}
