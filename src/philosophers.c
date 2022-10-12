#include "../includes/philosophers.h"

void	*routineA()
{
	int 	i;
	int	a;

	a = 0;
	i = 0;
	
	while (i++ < 2000)
		a++;
	return (0);
}
/*
void	*routineB()
{
	int	i;

	i = 0;
	while (i < 2001)
	{
		i++;
		a--;
	}
	return (0);
}
*/

void	fill_forks(t_gen_data *gen_data)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	while (y < gen_data->n_philo)
	{
		gen_data->philos[y].r_fork = i;
		if (i == 0)
			gen_data->philos[y].l_fork = gen_data->n_philo - 1;
		else
			gen_data->philos[y].l_fork = i - 1;
		y++;
		i++;
	}
}

void	preliminar(t_gen_data *gen_data, char **s)
{
	int	i;

	i = 0;
	gen_data->n_philo = ft_atoi(s[1]);
	gen_data->n_philos_dead = 0;
	gen_data->forks = malloc(sizeof(pthread_mutex_t ) * gen_data->n_philo);
	//gen_data->util = malloc(sizeof(pthread_mutex_t ) * gen_data->n_philo);
	while (i < gen_data->n_philo)
		pthread_mutex_init(&gen_data->forks[i++], NULL);
	i = 0;
	//while (i < gen_data->n_philo)
	pthread_mutex_init(&gen_data->util, NULL);
//	i = 0;
	gen_data->philos = malloc(sizeof(t_philos_data) * (gen_data->n_philo + 1));
	gen_data->n_philos = malloc(sizeof(pthread_t *) * (gen_data->n_philo + 1));
	//pthread_mutex_init(gen_data->forks, NULL);
	gen_data->pid = 0;
	while (i < gen_data->n_philo)
	{
		gen_data->n_philos[i] = i;
		gen_data->philos[i].is_dead = 0;
		i++;
	}
	gen_data->n_philos[i] = -1;
	fill_forks(gen_data);
}

void	check_arg(int arg)
{
	if (arg < 5 || arg > 6)
	{
		printf("Arguments needed");
		exit(0);
	}
}

void	needed_free(t_gen_data *gen_data)
{
	/*while (i < gen_data->n_philo)
	{
		if (gen_data->philos[i].r_fork)
			free(gen_data->philos[i].r_fork);
		if (gen_data->philos[i].l_fork)
			free(gen_data->philos[i].l_fork);
		i++;
	}*/
	free(gen_data->philos);
	if (gen_data->n_philos)
		free(gen_data->n_philos);
	if (gen_data->forks)
		free(gen_data->forks);
}

void	eat(t_gen_data	*gen_data)
{
	//pthread_mutex_lock(&gen_data->forks[gen_data->philos[gen_data->pid].r_fork]);
	//pthread_mutex_lock(&gen_data->forks[gen_data->philos[gen_data->pid].l_fork]);
	pthread_mutex_lock(&gen_data->util);
	printf("El filósofo %d esta jalando\n", gen_data->pid);
	usleep(2000000);
	gen_data->philos[gen_data->pid].is_dead = 1;
	pthread_mutex_unlock(&gen_data->util);
	//pthread_mutex_unlock(&gen_data->forks[gen_data->philos[gen_data->pid].r_fork]);
	//pthread_mutex_unlock(&gen_data->forks[gen_data->philos[gen_data->pid].l_fork]);
}

void	increment_pid(t_gen_data *gen_data)
{
	pthread_mutex_lock(&gen_data->util);
	gen_data->pid++;
	pthread_mutex_unlock(&gen_data->util);
}

void	*routine(void	*tra)
{
	t_gen_data	*gen_data;
	
	gen_data = (t_gen_data *) tra;
	eat(gen_data);
	printf("el filosofo %d ha terminado de comer\n", gen_data->pid);
	gen_data->pid++;
	/*while (gen_data->philos[gen_data->pid].is_dead == 0)
	{
		eat(gen_data);
		printf("El filósofo %d está pensando(%d)\n", gen_data->pid, gen_data->philos[gen_data->pid].is_dead);
		//gen_data->philos[gen_data->pid].is_dead = 1;
	}
	printf("llegó: %d", gen_data->pid);
	*/
	//increment_pid(gen_data);
	
	return (0);
}



int	main(int arg, char **args)
{
	t_gen_data	*gen_data;
	int		i;

	i = 0;
	gen_data = malloc(sizeof(t_gen_data) * 1);
	if (arg != 2)
		return (0);
	preliminar(gen_data, args);
	/*while (i < gen_data->n_philo)
	{
		printf("r:%d l:%d\n", gen_data->philos[i].r_fork, gen_data->philos[i].l_fork);
		i++;
	}*/
//	printf("%d\n", gen_data->n_philo);
	while (i < gen_data->n_philo)
	{
		if (0 != pthread_create(&gen_data->philos[i].pthread, NULL, routine, gen_data))
			printf("no se creo bien el hilo");
		i++;
//		gen_data->pid++;
	}
	i = 0;
	while (gen_data->pid < gen_data->n_philo)
	{
		pthread_join(gen_data->philos[i].pthread, NULL);
		i++;
	}
	return (0);
}
