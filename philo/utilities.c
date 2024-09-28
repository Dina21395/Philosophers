#include "philo.h"

int	is_all_created(t_table_data *tbl_data)
{
	int	isready;

	isready = 0;
	if (pthread_mutex_lock(&tbl_data->tbl_mutex) != 0)
		error_free_exit("fail tbl_mutex lock", tbl_data);
	isready = tbl_data->is_all_created;
	if (pthread_mutex_unlock(&tbl_data->tbl_mutex) != 0)
		error_free_exit("fail tbl_mutex unlock", tbl_data);
	return (isready);
}

int	is_table_end(t_table_data *tbl_data)
{
	int	is_end;

	is_end = 0;
	if (pthread_mutex_lock(&tbl_data->tbl_mutex) != 0)
		error_free_exit("fail tbl_mutex lock", tbl_data);
	is_end = tbl_data->is_tbl_end;
	if (pthread_mutex_unlock(&tbl_data->tbl_mutex) != 0)
		error_free_exit("fail tbl_mutex unlock", tbl_data);
	return (is_end);
}

void	reset_is_all_created(t_table_data *tbl_data, int val)
{
	if (pthread_mutex_lock(&tbl_data->tbl_mutex) != 0)
		error_free_exit("fail tbl_mutex lock", tbl_data);
	tbl_data->is_all_created = val;
	if (pthread_mutex_unlock(&tbl_data->tbl_mutex) != 0)
		error_free_exit("fail tbl_mutex unlock", tbl_data);
}

long	get_curr_time_ml(t_table_data *tbl_data)
{
	struct timeval	time_struct;
	long			current_time;

	current_time = 0;
	if (gettimeofday(&time_struct, NULL) != 0)
		error_free_exit("fail gettime()", tbl_data);
	current_time = time_struct.tv_sec * 1000 + time_struct.tv_usec / 1000;
	return (current_time);
}

void	error_free_exit(char *msg, t_table_data *tbl_data)
{
	printf("%s\n", msg);
	if (tbl_data->lst_philos)
		free(tbl_data->lst_philos);
	if (tbl_data->lst_forks)
		free(tbl_data->lst_forks);
	exit(EXIT_FAILURE);
}
