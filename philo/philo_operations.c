#include "philo.h"

void	ft_think(t_philo *curr_philo, int befor_begin)
{
	long	time_to_think;

	time_to_think = 0;
	if (!befor_begin)
		print_philo_state(THINK, curr_philo);
	if (curr_philo->tb_data->num_philos % 2 != 0)
	{
		time_to_think = (curr_philo->tb_data->time_to_eat * 2)
			- curr_philo->tb_data->time_to_sleep;
		if (time_to_think < 0)
			time_to_think = 0;
		ft_sleep(time_to_think * 0.42, curr_philo->tb_data);
	}
}

void	ft_eat(t_philo *curr_philo)
{
	lock_forks(curr_philo);
	if (pthread_mutex_lock(&curr_philo->philo_mutex) != 0)
		error_free_exit("fail philo mutex lock", curr_philo->tb_data);
	curr_philo->last_eating_time = get_curr_time_ml(curr_philo->tb_data);
	if (pthread_mutex_unlock(&curr_philo->philo_mutex) != 0)
		error_free_exit("fail philo mutex unlock", curr_philo->tb_data);
	curr_philo->num_of_eaten++;
	print_philo_state(EAT, curr_philo);
	ft_sleep(curr_philo->tb_data->time_to_eat, curr_philo->tb_data);
	if (curr_philo->tb_data->number_of_times_philo_eat != -1
		&& (curr_philo->num_of_eaten
			== curr_philo->tb_data->number_of_times_philo_eat))
	{
		if (pthread_mutex_lock(&curr_philo->philo_mutex) != 0)
			error_free_exit("fail philo mutex lock", curr_philo->tb_data);
		curr_philo->is_max_num_of_meals = 1;
		if (pthread_mutex_unlock(&curr_philo->philo_mutex) != 0)
			error_free_exit("fail philo mutex unlock", curr_philo->tb_data);
	}
	unlock_fork(curr_philo);
}

void	print_philo_state(int philo_state, t_philo *curr_philo)
{
	long	curr_elapsed_timestamp;

	curr_elapsed_timestamp = get_curr_time_ml(curr_philo->tb_data)
		- curr_philo->tb_data->t_begin;
	if (curr_philo->is_max_num_of_meals)
		return ;
	if (pthread_mutex_lock(&curr_philo->tb_data->tbl_mutex_print) != 0)
		error_free_exit("fail tbl_mutex_print lock", curr_philo->tb_data);
	if (philo_state == TAKEFORK && !is_table_end(curr_philo->tb_data))
		printf("%-6ld %d has taken a fork\n", curr_elapsed_timestamp,
			curr_philo->philo_id);
	else if (philo_state == EAT && !is_table_end(curr_philo->tb_data))
		printf("%-6ld %d is eating\n", curr_elapsed_timestamp,
			curr_philo->philo_id);
	else if (philo_state == SLEEP && !is_table_end(curr_philo->tb_data))
		printf("%-6ld %d is sleeping\n", curr_elapsed_timestamp,
			curr_philo->philo_id);
	else if (philo_state == THINK && !is_table_end(curr_philo->tb_data))
		printf("%-6ld %d is thinking\n", curr_elapsed_timestamp,
			curr_philo->philo_id);
	else if (philo_state == DIED)
		printf("%-6ld %d died\n", curr_elapsed_timestamp, curr_philo->philo_id);
	if (pthread_mutex_unlock(&curr_philo->tb_data->tbl_mutex_print) != 0)
		error_free_exit("fail tbl_mutex_print unlock", curr_philo->tb_data);
}

void	*philo_th_handler(void *curr_philo)
{
	t_philo	*philo;

	philo = curr_philo;
	while (!is_all_created(philo->tb_data))
		;
	if (pthread_mutex_lock(&philo->tb_data->tbl_mutex) != 0)
		error_free_exit("fail tbl_mutex lock", philo->tb_data);
	philo->tb_data->count_running_philos++;
	if (pthread_mutex_unlock(&philo->tb_data->tbl_mutex) != 0)
		error_free_exit("fail tbl_mutex unlock", philo->tb_data);
	handle_thinking_time(philo);
	while (!is_table_end(philo->tb_data))
	{
		if (philo->is_max_num_of_meals)
			break ;
		ft_eat(philo);
		print_philo_state(SLEEP, philo);
		ft_sleep(philo->tb_data->time_to_sleep, philo->tb_data);
		ft_think(philo, 0);
	}
	return (NULL);
}

void	ft_dining_start(t_table_data *tbl_data)
{
	int	i;

	i = 0;
	if (tbl_data->number_of_times_philo_eat == -1
		|| tbl_data->number_of_times_philo_eat > 0)
	{
		create_threads(tbl_data);
		tbl_data->t_begin = get_curr_time_ml(tbl_data);
		reset_is_all_created(tbl_data, 1);
		while (i < tbl_data->num_philos)
		{
			if (pthread_join(tbl_data->lst_philos[i].philo_thread, NULL) != 0)
				error_free_exit("fail thread join", tbl_data);
			i++;
		}
		end_table(tbl_data);
		if (pthread_join(tbl_data->death_monitor_thread, NULL) != 0)
			error_free_exit("fail thread join", tbl_data);
	}
}
