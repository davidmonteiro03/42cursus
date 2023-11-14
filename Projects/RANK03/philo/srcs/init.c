/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:56:28 by dcaetano          #+#    #+#             */
/*   Updated: 2023/11/14 17:38:55 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_forks(t_inf **inf)
{
	int	i;

	if (!*inf)
		return (1);
	i = -1;
	while (++i < (*inf)->num_ph)
		pthread_mutex_init(&(*inf)->f[i], NULL);
	return (0);
}

int	init_philos(t_inf **inf)
{
	int	i;

	if (!*inf)
		return (1);
	i = -1;
	while (++i < (*inf)->num_ph)
	{
		(*inf)->ph[i].inf = *inf;
		(*inf)->ph[i].ph_id = i + 1;
		(*inf)->ph[i].lf = &((*inf)->f[i]);
		(*inf)->ph[i].rf = &((*inf)->f[(i + 1) % (*inf)->num_ph]);
	}
	return (0);
}

int	init_inf(t_inf **inf, int ac, char **av)
{
	*inf = (t_inf *)malloc(sizeof(t_inf));
	if (!*inf)
		return (1);
	(*inf)->num_ph = ph_atoi(av[1]);
	(*inf)->time_die = ph_atoi(av[2]);
	(*inf)->time_eat = ph_atoi(av[3]);
	(*inf)->time_sleep = ph_atoi(av[4]);
	(*inf)->num_meals_ph = -1;
	if (ac == 6 && av[5] && *av[5])
		(*inf)->num_meals_ph = ph_atoi(av[5]);
	(*inf)->ph = (t_ph *)malloc(sizeof(t_ph) * (*inf)->num_ph);
	if (!(*inf)->ph)
		return (free(*inf), 1);
	(*inf)->f = (t_mutex *)malloc(sizeof(t_mutex) * (*inf)->num_ph);
	if (!(*inf)->f)
		return (free((*inf)->ph), free(*inf), 1);
	(*inf)->th = (t_th *)malloc(sizeof(t_th) * (*inf)->num_ph);
	if (!(*inf)->th)
		return (free((*inf)->f), free((*inf)->ph), free(*inf), 1);
	if (init_forks(inf) != 0 || init_philos(inf) != 0)
		return (free((*inf)->th), free((*inf)->f), free((*inf)->ph), \
			free(*inf), 1);
	return (0);
}
