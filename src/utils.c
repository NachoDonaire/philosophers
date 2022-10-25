/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndonaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:48:11 by ndonaire          #+#    #+#             */
/*   Updated: 2022/10/24 16:43:52 by ndonaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philosophers.h"

int	finder(char *s1, char *s2)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (s1[i])
	{
		while (s1[i] == s2[y] && s1[i] && s2[y])
		{
			y++;
			i++;
		}
		i++;
	}
	if (s2[y] == '\0')
		return (1);
	return (0);
}

int	dr_time(struct timeval philo_time, struct timeval start_time)
{
	unsigned long long	i;

	gettimeofday(&philo_time, NULL);
	i = ((philo_time.tv_sec * 1000) + (philo_time.tv_usec / 1000))
		- (start_time.tv_sec * 1000 + start_time.tv_usec / 1000);
	return (i);
}

void	sleepy(struct timeval helper, int time)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	while (dr_time(current, helper) < time)
		;
}

int	official_check(t_philos_data *philos)
{
//	pthread_mutex_lock(&philos->gen_data->util);
	if (philos->gen_data->dead == -1)
	{
//		pthread_mutex_unlock(&philos->gen_data->util);
		return (1);
	}
	else
	{
//		pthread_mutex_unlock(&philos->gen_data->util);
		return (0);
	}
}

int	check_write(t_philos_data *philos)
{
	pthread_mutex_lock(&philos->gen_data->jutels);
	if (philos->gen_data->n_p_dead == 0)
	{
		pthread_mutex_unlock(&philos->gen_data->jutels);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philos->gen_data->jutels);
		return (1);
	}
	pthread_mutex_unlock(&philos->gen_data->jutels);
	return (0);
}
