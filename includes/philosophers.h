# ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct	general_data{
	pthread_t	*n_philos;
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

typedef struct philos_data{
	t_gen_data	gen_data;
	int	state;
	int	r_fork;
	int	l_fork;
	int	is_dead;
	int	piddy;
	pthread_t	pthread;
}	t_philos_data;

int	ft_atoi(char *s);

#endif
