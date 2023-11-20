/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:46:43 by dcaetano          #+#    #+#             */
/*   Updated: 2023/11/20 13:21:46 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	*routine(void *philo)
{
	t_ph	*ph;

	ph = (t_ph *)philo;
	thinking(ph);
	sleeping(ph);
	return (NULL);
}

void	ph_1(t_inf **inf)
{
	(*inf)->time_start = gettime();
	status(&(*inf)->ph[0], THINK);
	usleep((*inf)->time_die * 1000);
	status(&(*inf)->ph[0], DIED);
}

int	simulation(t_inf **inf)
{
	int	i;

	if ((*inf)->num_ph == 1)
		return (ph_1(inf), 1);
	(*inf)->time_start = gettime();
	i = -1;
	while (++i < (*inf)->num_ph)
		pthread_create(&(*inf)->th[i], NULL, &routine, &(*inf)->ph[i]);
	return (0);
}

int	main(int ac, char **av)
{
	t_inf	*inf;
	int		status;
	bool	type;

	if (ac != 5 && ac != 6)
		return (error("Error usage"));
	if (!check_args(ac, av))
		return (error("Error in arguments"));
	inf = NULL;
	if (init_inf(&inf, ac, av) != 0)
		return (1);
	start();
	type = true;
	if (simulation(&inf) == 1)
		type = false;
	status = clean_inf(&inf, type);
	end();
	return (status);
}
