/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:39:25 by dcaetano          #+#    #+#             */
/*   Updated: 2023/11/20 13:18:53 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

void	status(t_ph *ph, char *status)
{
	pthread_mutex_lock(ph->inf->action_lock);
	printf("| %9ldms | %-5d | %-25s |\n", \
		(gettime() - ph->inf->time_start) / 1000, \
		ph->ph_id, \
		status \
	);
	pthread_mutex_unlock(ph->inf->action_lock);
}
