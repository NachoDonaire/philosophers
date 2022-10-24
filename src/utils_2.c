/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndonaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:52:26 by ndonaire          #+#    #+#             */
/*   Updated: 2022/10/24 15:10:40 by ndonaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	tactec(struct timeval helper)
{
	struct timeval	eff;

	gettimeofday(&eff, NULL);
	return ((eff.tv_sec * 1000 + eff.tv_usec / 1000)
		- (helper.tv_sec * 1000 + helper.tv_usec / 1000));
}

int	nhummy(t_philos_data *philos)
{
	if (philos->gen_data->n_eat >= (philos->gen_data->n_p_eat
			* philos->gen_data->n_philo) && philos->gen_data->n_p_eat > 0)
		return (1);
	return (0);
}
