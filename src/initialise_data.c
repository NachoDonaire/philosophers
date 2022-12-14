/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndonaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:42:05 by ndonaire          #+#    #+#             */
/*   Updated: 2022/10/24 16:36:46 by ndonaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	fill_forks(t_philos_data *philos, int n)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	while (y < n)
	{
		philos[y].r_fork = i;
		if (i == 0)
			philos[y].l_fork = n - 1;
		else
			philos[y].l_fork = i - 1;
		y++;
		i++;
	}
}

void	fill_gen_philos(t_gen_data *gen_data, int n, char **s)
{
	int	i;

	gettimeofday(&gen_data->start_time, NULL);
	i = 0;
	gen_data->forks = malloc(sizeof(pthread_mutex_t) * (n + 1));
	while (i < n)
		pthread_mutex_init(&gen_data->forks[i++], NULL);
	pthread_mutex_init(&gen_data->wrt, NULL);
	pthread_mutex_init(&gen_data->util, NULL);
	pthread_mutex_init(&gen_data->jutels, NULL);
	pthread_mutex_init(&gen_data->zajo, NULL);
	gen_data->n_philo = ft_atoi(s[1]);
	gen_data->t_die = ft_atoi(s[2]);
	gen_data->t_eat = ft_atoi(s[3]);
	gen_data->t_sleep = ft_atoi(s[4]);
	gen_data->dead = -1;
	gen_data->n_eat = 0;
	gen_data->adv = 0;
	if (s[5])
		gen_data->n_p_eat = ft_atoi(s[5]);
}

void	piddy_gonzalez(t_philos_data *philos, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		philos[i].piddy = i + 1;
		philos[i].state = 1;
		gettimeofday(&philos[i].helper, NULL);
		philos[i].is_dead = 0;
		i++;
	}
}

void	preliminar(t_philos_data *philos, char **s, t_gen_data *a)
{
	int	n;
	int	i;

	if (ft_atoi(s[1]) == 0)
		exit (0);
	i = 0;
	n = ft_atoi(s[1]);
	piddy_gonzalez(philos, n);
	fill_forks(philos, n);
	while (i < n)
		philos[i++].gen_data = a;
}
