#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TAKEFORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIED 5

typedef struct s_table_data	t_table_data;

typedef struct s_fork
{
	int						fork_id;
	pthread_mutex_t			fork_mutex;
}							t_fork;

typedef struct s_philo
{
	int						philo_id;
	pthread_t				philo_thread;
	t_fork					*r_fork;
	t_fork					*l_fork;
	long					last_eating_time;
	int						num_of_eaten;
	int						is_max_num_of_meals;
	pthread_mutex_t			philo_mutex;
	t_table_data			*tb_data;
}							t_philo;

struct						s_table_data
{
	int						num_philos;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
	int						number_of_times_philo_eat;
	long					t_begin;
	int						is_tbl_end;
	int						is_all_created;
	int						count_running_philos;
	pthread_mutex_t			tbl_mutex;
	pthread_mutex_t			tbl_mutex_print;
	t_philo					*lst_philos;
	t_fork					*lst_forks;
	pthread_t				death_monitor_thread;
};

void						ft_validate_fill(int arc, char **arv,
								t_table_data *tbl_data);
void						error_free_exit(char *msg, t_table_data *tbl_data);

void						ft_tbl_data_init(t_table_data *tbl_data);
void						ft_dining_start(t_table_data *tbl_data);
void						reset_is_all_created(t_table_data *tbl_data,
								int val);
int							is_table_end(t_table_data *tbl_data);
int							is_all_created(t_table_data *tbl_data);
long						get_curr_time_ml(t_table_data *tbl_data);
void						ft_sleep(long time_sleep, t_table_data *tbl);
void						print_philo_state(int philo_state,
								t_philo *curr_philo);
void						*philo_th_handler(void *curr_philo);
void						*death_monitor_handler(void *table);
void						*one_philo_th_handler(void *curr_philo);
void						ft_clean_memory(t_table_data *tbl);
void						ft_think(t_philo *curr_philo, int befor_begin);
void						handle_thinking_time(t_philo *curr_philo);
void						lock_forks(t_philo *curr_philo);
void						unlock_fork(t_philo *curr_philo);
void						create_threads(t_table_data *tbl_data);
void						end_table(t_table_data *tbl_data);
#endif