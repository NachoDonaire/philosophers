/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndonaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:46:07 by ndonaire          #+#    #+#             */
/*   Updated: 2022/10/24 16:36:44 by ndonaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	philos_log(char *s, t_philos_data *philos)
{
	pthread_mutex_lock(&philos->gen_data->wrt);
	if (official_check(philos) == 0 && check_write(philos) == 0)
	{
		death(philos);
		return ;
	}
	if (philos->gen_data->dead == -1)
		printf("%dms %d %s\n", dr_time(philos->philo_time,
				philos->gen_data->start_time), philos->piddy, s);
	if (finder(s, "is eating") == 1 && philos->gen_data->dead == -1)
	{
		eating(philos);
		return ;
	}
	else if (finder(s, "is thinking") == 1 && philos->gen_data->dead == -1)
	{
		thinking(philos);
		return ;
	}	
	else if (finder(s, "is sleeping") == 1 && philos->gen_data->dead == -1)
	{
		sleeping(philos);
		return ;
	}	
	pthread_mutex_unlock(&philos->gen_data->wrt);
}

void	check_dead(t_philos_data *philos, char **args)
{
	int	i;

	i = 0;
	while (philos->gen_data->dead == -1)
	{
		while (i < ft_atoi(args[1]))
		{
			if (tactec(philos[i].helper) >= ft_atoi(args[2]))
			{
				philos->gen_data->dead = i + 1;
			}
			i++;
		}
		i = 0;
	}
}

void	eat(t_philos_data *philos)
{
	pthread_mutex_lock(&philos->gen_data->forks[philos->r_fork]);
	philos_log("has taken a fork", philos);
	if (philos->gen_data->n_philo == 1)
	{
		while (tactec(philos->helper) <= philos->gen_data->t_die)
			;
		return ;
	}
	pthread_mutex_lock(&philos->gen_data->forks[philos->l_fork]);
	philos_log("has taken a fork", philos);
	philos_log("is eating", philos);
	pthread_mutex_unlock(&philos->gen_data->forks[philos->r_fork]);
	pthread_mutex_unlock(&philos->gen_data->forks[philos->l_fork]);
}

void	*routine(void	*tra)
{
	t_philos_data	*philos;

	philos = (t_philos_data *)tra;
	if (philos->piddy % 2 != 0)
		usleep(150);
	while (official_check(philos) == 1)
	{
		eat(philos);
		philos_log("is sleeping", philos);
		philos_log("is thinking", philos);
	}
	return (0);
}

/*
void	leaks()
{
	system("leaks philo");
}
*/

int	main(int arg, char **args)
{
	t_philos_data	*philos;
	t_gen_data		*gen_data;

	if (check_error(args, arg) == 1)
	{
		printf("Invalid input");
		return (0);
	}
	gen_data = malloc(sizeof(t_gen_data) * 1);
	philos = malloc(sizeof(t_philos_data) * ft_atoi(args[1]));
	fill_gen_philos(gen_data, ft_atoi(args[1]), args);
	preliminar(philos, args, gen_data);
	create_threads(args, philos);
	check_dead(philos, args);
	join_threads(args, philos);
	needed_free(philos, gen_data);
	return (0);
}
