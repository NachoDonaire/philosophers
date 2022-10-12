# ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct philos_data{
	int	state;
	int	r_fork;
	int	l_fork;
	int	is_dead;
	pthread_t	pthread;
}	t_philos_data;

typedef struct	general_data{
	pthread_t	*n_philos;
	t_philos_data	*philos;
	int		n_philo;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		n_philos_dead;
	int		pid;
	char		**args;
	pthread_mutex_t	*forks;
	pthread_mutex_t	util;
}	t_gen_data;

int	ft_atoi(char *s);

#endif
