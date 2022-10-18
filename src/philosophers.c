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

int dr_time(struct timeval philo_time, struct timeval start_time)
{
	unsigned long long i;

	i = ((philo_time.tv_sec * 1000) + (philo_time.tv_usec / 1000)) - (start_time.tv_sec * 1000 + start_time.tv_usec / 1000);
	return (i);
}



int	magic(t_philos_data *philos)
{
	int	i;

	i = philos->gen_data->t_die - (philos->gen_data->t_eat + philos->gen_data->t_sleep);
	return (i);
}

void	case_think(t_philos_data *philos)
{
	while (dr_time(philos->philo_time, philos->helper) < magic(philos))
	{
		gettimeofday(&philos->philo_time, NULL);
		if (dr_time(philos->philo_time, philos->helper) >= magic(philos) - 20)
			break ;
		usleep(5);
	}
}


void	philos_log(char *s, t_philos_data *philos)
{
	pthread_mutex_lock(&philos->gen_data->wrt);
	gettimeofday(&philos->philo_time, NULL);
	if (dr_time(philos->philo_time, philos->helper) >= philos->gen_data->t_die)
	{
		printf("ey");
		philos->state = 0;
		printf("%dms %d %s\n",dr_time(philos->philo_time, philos->helper), philos->piddy, s);
		pthread_mutex_unlock(&philos->gen_data->wrt);
		return ;
	}
	printf("%ldms %d %s\n", (philos->philo_time.tv_sec * 1000 + philos->philo_time.tv_usec / 1000) - (philos->gen_data->start_time.tv_sec * 1000 + philos->gen_data->start_time.tv_usec / 1000) , philos->piddy, s);
	if (finder(s, "is eating") == 1)
		gettimeofday(&philos->helper, NULL);
	pthread_mutex_unlock(&philos->gen_data->wrt);

}

void	check_dead(t_philos_data *philos, char **args, t_gen_data *gen_data)
{
	int	i;

	i = 0;
	while (1)
	{
		while (i < ft_atoi(args[1]))
		{
			if (philos[i].state == 0)
				break ;
			i++;
		}
		i = 0;
	}
	join_threads(args, philos);
	needed_free(gen_data, philos, ft_atoi(args[1]));
	exit (0);
}



void	eat(t_philos_data *philos)
{
//	case_think(philos);
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
			//philos_log("is thinking", philos);
		}
/*		else if (philos->state == 0)
		{
			philos_log("dead", philos);
			exit (0);
		}*/
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
	check_dead(philos, args, gen_data);
	return (0);
}
