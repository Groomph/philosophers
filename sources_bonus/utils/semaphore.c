/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:18:05 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/11 18:28:38 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

BOOL	safe_create(sem_t **sem, char *name, int value)
{
	*sem = sem_open(name, O_CREAT | O_EXCL, S_IRWXU, value);
	if (*sem == SEM_FAILED)
		return (error(NULL, FALSE, name, -1));
	return (TRUE);
}

BOOL	safe_open(sem_t **sem, char *name)
{
	*sem = sem_open(name, O_RDWR);
	if (*sem == SEM_FAILED)
		return (error(NULL, FALSE, name, -1));
	return (TRUE);
}

BOOL	safe_close(sem_t *sem)
{
	if (sem_close(sem) == -1)
		return (error(NULL, FALSE, "close semaphore", -1));
	return (TRUE);
}
