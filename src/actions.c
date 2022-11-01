/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndonaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:33:24 by ndonaire          #+#    #+#             */
/*   Updated: 2022/10/24 16:56:38 by ndonaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	death(t_philos_data *philos)
{
	if (philos->gen_data->adv == 0)
		printf("%dms %d %s\n", dr_time(philos->philo_time,
				philos->gen_data->start_time), philos->gen_data->dead, "died");
	philos->gen_data->n_p_dead++;
	pthread_mutex_unlock(&philos->gen_data->wrt);
}

void	eating(t_philos_data *philos)
{
	gettimeofday(&philos->helper, NULL);
	philos->gen_data->n_eat++;
	pthread_mutex_unlock(&philos->gen_data->wrt);
	if (nhummy(philos) == 1)
	{
		philos->gen_data->dead = 0;
		philos->gen_data->adv = 1;
		pthread_mutex_unlock(&philos->gen_data->wrt);
		philos_log("dead", philos);
	}
	sleepy(philos->helper, philos->gen_data->t_eat);
}

void	thinking(t_philos_data *philos)
{
	pthread_mutex_unlock(&philos->gen_data->wrt);
	if (philos->gen_data->t_eat == 0 && philos->gen_data->t_sleep == 0)
	{
		write(1, "aa\n", 3);
		usleep(1500);
		return ;
	}
	while (tactec(philos->helper) < (philos->gen_data->t_eat
			+ philos->gen_data->t_sleep))
		;
}
		

void	sleeping(t_philos_data *philos)
{
	pthread_mutex_unlock(&philos->gen_data->wrt);
	sleepy(philos->helper, philos->gen_data->t_sleep + philos->gen_data->t_eat);
}
