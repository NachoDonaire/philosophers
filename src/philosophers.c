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

void	fill_gen_philos(t_philos_data *philos, int n)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	while (i < n)
	{
		philos[i].gen_data.forks = malloc(sizeof(pthread_mutex_t) * n);
		philos[i].piddy = i;
		while (y < n)
		{
			pthread_mutex_init(&philos[i].gen_data.forks[y], NULL);
			y++;
		}
		pthread_mutex_init(&philos[i].gen_data.util, NULL);
		i++;
	}
}


void	preliminar(t_philos_data *philos, char **s)
{
	int	n;

	n = ft_atoi(s[1]);
	fill_gen_philos(philos, n);
/*	gen_data->t_die = ft_atoi(s[2]) * 1000;
	gen_data->t_eat = ft_atoi(s[3]) * 1000;
	gen_data->t_sleep = ft_atoi(s[4]) * 1000;
	*/
//	gen_data->forks = malloc(sizeof(pthread_mutex_t ) * gen_data->n_philo);
	//gen_data->util = malloc(sizeof(pthread_mutex_t ) * gen_data->n_philo);
//	while (i < gen_data->n_philo)
//		pthread_mutex_init(&gen_data->forks[i++], NULL);
//	i = 0;
	//while (i < gen_data->n_philo)
//	pthread_mutex_init(&gen_data->util, NULL);
//	i = 0;
//	gen_data->philos = malloc(sizeof(t_philos_data) * (gen_data->n_philo + 1));
//	gen_data->n_philos = malloc(sizeof(pthread_t *) * (gen_data->n_philo + 1));
	//pthread_mutex_init(gen_data->forks, NULL);
//	gen_data->pid = 0;
//	while (i < gen_data->n_philo)
//	{
		//gen_data->n_philos[i] = i;
//		gen_data->philos[i].piddy = i;
//		gen_data->philos[i].is_dead = 0;
//		i++;
//	}
	fill_forks(philos, n);
}

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

void	eat(t_philos_data *philos)
{
//	pthread_mutex_lock(&gen_data->util);
	pthread_mutex_lock(&philos[philos->);
	pthread_mutex_lock(&gen_data->forks[gen_data->philos[gen_data->pid].l_fork]);
	printf("El filósofo %d esta jalando\n", gen_data->pid);
	usleep(2000000);
	gen_data->philos[gen_data->pid].is_dead = 1;
	pthread_mutex_unlock(&gen_data->forks[gen_data->philos[gen_data->pid].r_fork]);
	pthread_mutex_unlock(&gen_data->forks[gen_data->philos[gen_data->pid].l_fork]);
		
}

void	increment_pid(t_gen_data *gen_data)
{
	//pthread_mutex_lock(&gen_data->util);
	gen_data->n_philos_dead++;
	gen_data->pid++;
	pthread_mutex_unlock(&gen_data->util);

	//pthread_mutex_lock(&gen_data->util);
	//pthread_mutex_unlock(&gen_data->util);
}

void	*routine(void	*tra)
{
	t_philos_data	*philos
	
	philos = (t_philos_data *)tra;
	eat(gen_data);
	printf("el filosofo %d ha terminado de comer\n", gen_data->pid);
	increment_pid(gen_data);
	while (gen_data->philos[gen_data->pid].is_dead == 0)
	{
		eat(gen_data);
		printf("El filósofo %d está pensando(%d)\n", gen_data->pid, gen_data->philos[gen_data->pid].is_dead);
		//gen_data->philos[gen_data->pid].is_dead = 1;
	}
	printf("llegó: %d", gen_data->pid);
	
	//increment_pid(gen_data);
	
	return (0);
}


int	main(int arg, char **args)
{
	t_philos_data	*philos;
	int		i;

	philos = malloc(sizeof(t_philos_data) * ft_atoi(args[1]));
	i = 0;
	if (arg != 2)
		return (0);
	preliminar(philos, args);
	/*
	while (i < ft_atoi(args[1]))
	{
		printf("r:%d l:%d\n", philos[i].r_fork, philos[i].l_fork);
		i++;
	}
	*/
//	printf("%d\n", gen_data->n_philo);
	while (i < gen_data->n_philo)
	{
		if (0 != pthread_create(&gen_data->philos[i].pthread, NULL, routine, philos))
			printf("no se creo bien el hilo");
		i++;
	}
	i = 0;
	while (gen_data->pid < gen_data->n_philo)
	{
		pthread_join(gen_data->philos[i].pthread, NULL);
		i++;
	}
	return (0);
}
