#include "philo.h"

int	is_all_philos_running(t_table_data *tbl_data)
{
	int	isallrun;

	isallrun = 0;
	if (pthread_mutex_lock(&tbl_data->tbl_mutex) != 0)
		error_free_exit("fail tbl_mutex lock", tbl_data);
	if (tbl_data->count_running_philos == tbl_data->num_philos)
		isallrun = 1;
	if (pthread_mutex_unlock(&tbl_data->tbl_mutex) != 0)
		error_free_exit("fail tbl_mutex unlock", tbl_data);
	return (isallrun);
}

int	philo_dead_checker(t_philo *philo, long time_begin)
{
	int		is_philo_died;
	long	starving_duration;

	is_philo_died = 0;
	if (!philo->is_max_num_of_meals)
	{
		if (philo->last_eating_time == 0)
			starving_duration = get_curr_time_ml(philo->tb_data) - time_begin;
		else
			starving_duration = get_curr_time_ml(philo->tb_data)
				- philo->last_eating_time;
		if (starving_duration > philo->tb_data->time_to_die)
			is_philo_died = 1;
	}
	return (is_philo_died);
}

void	*death_monitor_handler(void *table)
{
	t_table_data	*tbl;
	int				i;

	tbl = table;
	while (!is_all_philos_running(tbl))
		;
	while (!is_table_end(tbl))
	{
		i = 0;
		while (i < tbl->num_philos && !is_table_end(tbl))
		{
			if (philo_dead_checker(&tbl->lst_philos[i], tbl->t_begin))
			{
				print_philo_state(DIED, &tbl->lst_philos[i]);
				end_table(tbl);
			}
			i++;
		}
	}
	return (NULL);
}

void	*one_philo_th_handler(void *curr_philo)
{
	t_philo	*philo;

	philo = curr_philo;
	while (!is_all_created(philo->tb_data))
		;
	if (pthread_mutex_lock(&philo->tb_data->tbl_mutex) != 0)
		error_free_exit("fail tbl_mutex lock", philo->tb_data);
	philo->tb_data->count_running_philos = 1;
	if (pthread_mutex_unlock(&philo->tb_data->tbl_mutex) != 0)
		error_free_exit("fail tbl_mutex unlock", philo->tb_data);
	print_philo_state(TAKEFORK, philo);
	while (!is_table_end(philo->tb_data))
		usleep(1000);
	return (NULL);
}

void	handle_thinking_time(t_philo *curr_philo)
{
	if (curr_philo->tb_data->num_philos % 2 == 0)
	{
		if (curr_philo->philo_id % 2 == 0)
		{
			ft_sleep(30, curr_philo->tb_data);
		}
	}
	else
	{
		if (curr_philo->philo_id % 2)
		{
			ft_think(curr_philo, 1);
		}
	}
}
