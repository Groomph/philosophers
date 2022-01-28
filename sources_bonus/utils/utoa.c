/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:27:02 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/28 15:26:27 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	utoa_rec(unsigned int nb, char *dest, char *base)
{
	int	i;

	i = 0;
	if (nb >= 10)
		i = utoa_rec(nb / 10, dest, base);
	dest[i] = base[nb % 10];
	return (i + 1);
}

static int	utoa_end(unsigned int nb, char *dest, char *base)
{
	int	i;

	i = utoa_rec(nb, dest, base);
	dest[i] = '\0';
	return (i);
}

void	set_sem_name(t_philo *philo)
{
	char static const	meals[] = "mEaLsID";
	char static const	timer[] = "tImErID";
	int					i;

	i = 0;
	while (i < 7)
	{
		philo->meals_name[i] = meals[i];
		philo->timer_name[i] = timer[i];
		i++;
	}
	utoa_end(philo->id, &(philo->meals_name[i]), "0123456789");
	utoa_end(philo->id, &(philo->timer_name[i]), "0123456789");
}
