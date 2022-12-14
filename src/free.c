/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndonaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:39:54 by ndonaire          #+#    #+#             */
/*   Updated: 2022/10/24 14:56:03 by ndonaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	needed_free(t_philos_data *philos, t_gen_data *gen_data)
{
	int	i;

	i = 0;
	while (i < gen_data->n_philo)
		pthread_mutex_destroy(&gen_data->forks[i++]);
	pthread_mutex_destroy(&gen_data->util);
	pthread_mutex_destroy(&gen_data->jutels);
	pthread_mutex_destroy(&gen_data->wrt);
	if (gen_data->n_philos)
		free(gen_data->n_philos);
	if (gen_data->forks)
		free(gen_data->forks);
	free(gen_data);
	free(philos);
}
