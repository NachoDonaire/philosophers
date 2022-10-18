#include "../includes/philosophers.h"

void	check_arg(int arg)
{
	if (arg < 5 || arg > 6)
	{
		printf("Arguments needed");
		exit(0);
	}
}

void	needed_free(t_gen_data *gen_data, t_philos_data *philos,  int n)
{
	int	i;

	i = 0;
	if (gen_data->n_philos)
		free(gen_data->n_philos);
	if (gen_data->forks)
		free(gen_data->forks);
	while (i < n)
	{
		free(philos[i++].gen_data);
	}
	free(gen_data);
	free(philos);
}


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



void	philos_log(char *s, t_philos_data *philos)
{
	pthread_mutex_lock(&philos->gen_data->wrt);
	gettimeofday(&philos->philo_time, NULL);
	if (finder(s, "is eating") == 1)
	{
		if (((philos->philo_time.tv_sec * 1000) + (philos->philo_time.tv_usec / 1999)) - (philos->gen_data->start_time.tv_sec * 1000 + philos->gen_data->start_time.tv_usec / 1000) >= philos->gen_data->t_die)
		{
			philos->state = 0;
			printf("%ldms %d %s\n", (philos->philo_time.tv_sec * 1000 + philos->philo_time.tv_usec / 1000) - (philos->gen_data->start_time.tv_sec * 1000 + philos->gen_data->start_time.tv_usec / 1000) , philos->piddy, "dead");
			exit (0);
		}
	}
//		check_dead(philos);
	//printf("philos_time:%ldstart:%ldresta:%ldsujeto:%daccion:%s\n", philos->philo_time.tv_sec, philos->gen_data->start_time.tv_sec, (philos->philo_time.tv_usec / 1000) - (philos->helper.tv_usec / 1000), philos->piddy, s);
	printf("%ldms %d %s\n", (philos->philo_time.tv_sec * 1000 + philos->philo_time.tv_usec / 1000) - (philos->gen_data->start_time.tv_sec * 1000 + philos->gen_data->start_time.tv_usec / 1000) , philos->piddy, s);
	if (finder(s, "is eating") == 1)
		gettimeofday(&philos->helper, NULL);
	pthread_mutex_unlock(&philos->gen_data->wrt);
}

void	check_dead(t_philos_data *philos)
{
	pthread_mutex_lock(&philos->gen_data->util);
	gettimeofday(&philos->philo_time, NULL);
	//printf("--%ld--\n", (philos->philo_time.tv_usec - philos->helper.tv_usec));
	if ((philos->philo_time.tv_usec - philos->helper.tv_usec) >= philos->gen_data->t_die * 1000)
	{
		philos->state = 0;
		printf("%ldms %d %s\n", (philos->philo_time.tv_sec * 1000) - (philos->gen_data->start_time.tv_sec * 1000) , philos->piddy, "dead");
		pthread_mutex_unlock(&philos->gen_data->util);
		exit (0);
	//	exit(0);
	}
	if (philos->n_eat == philos->gen_data->n_p_eat && philos->gen_data->n_p_eat > 0)
	{
		philos->state = 0;
	}
	pthread_mutex_unlock(&philos->gen_data->util);
}



void	eat(t_philos_data *philos)
{
	//philos_log("is thinking", philos);
	pthread_mutex_lock(&philos->gen_data->forks[philos->r_fork]);
	pthread_mutex_lock(&philos->gen_data->forks[philos->l_fork]);
	philos->n_eat++;
	philos_log("has taken a fork", philos);
	//check_dead(philos);
	philos_log("is eating", philos);
	if (philos->state != 0)
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
			philos_log("is thinking", philos);
		}
		else if (philos->state == 0)
		{
			philos_log("dead", philos);
			exit (0);
		}
	}
	return (0);
}

void	check_dead_main(t_philos_data *philos, int n)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	while (1)
	{
		while (i < n)
		{
			if (philos[i].state == 0)
			{
				exit (0);
			}
			i++;
		}
		if (y == n)
			exit (0);
		i = 0;
	}
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
	check_dead_main(philos, ft_atoi(args[1]));
	join_threads(args, philos);
	needed_free(gen_data, philos, ft_atoi(args[1]));
	return (0);
}
