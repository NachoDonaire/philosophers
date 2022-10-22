# ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

/*philos states
 * 0 = DEAD;
 * 1 = HUNGRY;
 * 2 = EATING;
 * 3 = THINKING;
 * 4 = SLEEPING;
 * */


typedef struct	general_data{
	pthread_t	*n_philos;
	int		n_philo;
	int	t_die;
	int		t_eat;
	int		t_sleep;
	int		n_philos_dead;
	int		pid;
	struct	timeval	start_time;
	struct	timeval	end_time;
	int		n_p_eat;
	int		n_p_dead;
	int		dead;
	int		n_eat;
	pthread_mutex_t	wrt;
	pthread_mutex_t	jutels;
	pthread_mutex_t	*forks;
	pthread_mutex_t	util;
}	t_gen_data;

typedef struct philos_data{
	t_gen_data	*gen_data;
	int	state;
	int	r_fork;
	int	l_fork;
	int	is_dead;
	struct	timeval	philo_time;
	int	piddy;
	struct	timeval	helper;
	pthread_t	pthread;
}	t_philos_data;

int	ft_atoi(char *s);
void    create_threads(char **args, t_philos_data *philos);
void    join_threads(char **args, t_philos_data *philos);
void	*routine(void	*tra);
void    fill_forks(t_philos_data *philos, int n);
void    fill_gen_philos(t_gen_data *gen_data, int n, char **s);
void    piddy_gonzalez(t_philos_data *philos, int n);
void    preliminar(t_philos_data *philos, char **s, t_gen_data *alakazam, int arg);
void	check_arg(int arg);
int dr_time(struct timeval philo_time, struct timeval start_time);
int     finder(char *s1, char *s2);
int     official_check(t_philos_data *philos);
int     tactec(struct timeval helper);
void	needed_free(t_philos_data *philos, t_gen_data *gen_data);
int	check_write(t_philos_data *philos);
int	nhummy(t_philos_data *philos);


#endif
