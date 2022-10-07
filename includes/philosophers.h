# ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct philos_data{
	int	state;
}	t_philos_data;

typedef struct	general_data{
	pthread_t	*n_philos;
	t_philos_data	*philos;
}	t_gen_data;

int	ft_atoi(char *s);

#endif
