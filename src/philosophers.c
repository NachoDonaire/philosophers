#include "../includes/philosophers.h"

void	check_arg(int arg)
{
	if (arg < 5 || arg > 6)
	{
		printf("Arguments needed");
		exit(0);
	}
}
/*
void	needed_free(t_gen_data *gen_data)
{
	while (i < gen_data->n_philo)
	{
		if (gen_data->philos[i].r_fork)
			free(gen_data->philos[i].r_fork);
		if (gen_data->philos[i].l_fork)
			free(gen_data->philos[i].l_fork);
		i++;
	
	free(gen_data->philos);
	if (gen_data->n_philos)
		free(gen_data->n_philos);
	if (gen_data->forks)
		free(gen_data->forks);
}
*/

void	philos_log(char *s, t_philos_data *philos)
{
	pthread_mutex_lock(&philos->gen_data->wrt);
	//printf("--%d--\n", philos->piddy);
	gettimeofday(&philos->philo_time, NULL);
//	printf("philos_time:%ldstart:%ldresta:%ldsujeto:%daccion:%s\n", philos->philo_time.tv_usec, philos->gen_data->start_time.tv_usec, philos->philo_time.tv_usec - philos->gen_data->start_time.tv_usec, philos->piddy, s);
	printf("%ld %d %s\n", philos->philo_time.tv_usec - philos->helper.tv_usec, philos->piddy, s);
	gettimeofday(&philos->helper, NULL);
	pthread_mutex_unlock(&philos->gen_data->wrt);
}
void	check_dead(t_philos_data *philos)
{
	pthread_mutex_lock(&philos->gen_data->util);
	//gettimeofday(&philos->gen_data->end_time[philos->piddy], NULL);
	gettimeofday(&philos->philo_time, NULL);
	if (philos->philo_time.tv_usec - philos->helper.tv_usec >= philos->gen_data->t_die * 1000)
	{
		philos->state = 0;
		philos_log("died", philos);
		pthread_mutex_unlock(&philos->gen_data->util);
		exit(0);
	}
	if (philos->n_eat == philos->gen_data->n_p_eat && philos->gen_data->n_p_eat > 0)
	{
		philos->state = 0;
	}
	pthread_mutex_unlock(&philos->gen_data->util);
}



void	eat(t_philos_data *philos)
{
	pthread_mutex_lock(&philos->gen_data->forks[philos->r_fork]);
	pthread_mutex_lock(&philos->gen_data->forks[philos->l_fork]);
	philos->n_eat++;
	check_dead(philos);
	philos_log("has taken a fork", philos);
	philos_log("is eating", philos);
	usleep(philos->gen_data->t_eat * 1000);
	pthread_mutex_unlock(&philos->gen_data->forks[philos->r_fork]);
	pthread_mutex_unlock(&philos->gen_data->forks[philos->l_fork]);
		
}

void	*routine(void	*tra)
{
	t_philos_data	*philos;
	
	philos = (t_philos_data *)tra;
	while (philos->state != 0)
	{
		eat(philos);
		if (philos->state != 0)
		{
			philos->state = 4;
			philos_log("is sleeping", philos);
			usleep(philos->gen_data->t_sleep * 1000);
		}
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
	join_threads(args, philos);
	return (0);
}
