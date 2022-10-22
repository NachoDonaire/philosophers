#include "../includes/philosophers.h"

void	philos_log(char *s, t_philos_data *philos)
{
	pthread_mutex_lock(&philos->gen_data->wrt);
	if (official_check(philos) == 0 && check_write(philos) == 0) 
	{
		printf("%dms %d %s\n", dr_time(philos->philo_time, philos->gen_data->start_time) , philos->piddy, "died");
		philos->gen_data->n_p_dead++;
		pthread_mutex_unlock(&philos->gen_data->wrt);
		return ;
	}
	if (philos->gen_data->dead == 1)
		printf("%dms %d %s\n", dr_time(philos->philo_time, philos->gen_data->start_time) , philos->piddy, s);
	if (finder(s, "is eating") == 1 && philos->gen_data->dead == 1)
	{
		gettimeofday(&philos->helper, NULL);
		philos->gen_data->n_eat++;
		if (nhummy(philos) == 1)
		{
			philos->gen_data->dead = 0;
			pthread_mutex_unlock(&philos->gen_data->wrt);
			philos_log("dead", philos);
		}
		//sleepy(philos->helper, philos->gen_data->t_eat);
		pthread_mutex_unlock(&philos->gen_data->wrt);
		usleep(philos->gen_data->t_eat * 1000);
		return ;
	}
	else if (finder(s, "is sleeping") == 1 && philos->gen_data->dead == 1)
	{
		pthread_mutex_unlock(&philos->gen_data->wrt);
		//sleepy(philos->helper, philos->gen_data->t_sleep);
		usleep(philos->gen_data->t_sleep * 1000);
		return ;
	}	
	pthread_mutex_unlock(&philos->gen_data->wrt);

}

void	check_dead(t_philos_data *philos, char **args)
{
	int	i;

	i = 0;
	while (philos->gen_data->dead == 1)
	{
		while (i < ft_atoi(args[1]))
		{
			if (tactec(philos[i].helper) >= ft_atoi(args[2]))// || tuctateca(philos) == 1)
			{
				philos->gen_data->dead = 0;
			}
			i++;
		}
		i = 0;
	}
}

void	eat(t_philos_data *philos)
{
	pthread_mutex_lock(&philos->gen_data->forks[philos->r_fork]);
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
	if (philos->piddy % 2 == 0)
		usleep(1500);
	while (official_check(philos) == 1)
	{
		eat(philos);
		philos_log("is sleeping", philos);
		philos_log("is thinking", philos);
	}
	return (0);
}

int	main(int arg, char **args)
{
	t_philos_data	*philos;
	t_gen_data	*gen_data;

	gen_data = malloc(sizeof(t_gen_data ) * 1);
	philos = malloc(sizeof(t_philos_data) * ft_atoi(args[1]));
	fill_gen_philos(gen_data, ft_atoi(args[1]), args);
	preliminar(philos, args, gen_data, arg);
	create_threads(args, philos);
	check_dead(philos, args);
	join_threads(args, philos);
	needed_free(philos, gen_data);
	return (0);
}
