#include "philo.h"

void	error_message(void)
{
	printf("INVALID ARGS\n");
	exit(EXIT_FAILURE);
}

long	ft_atoi(const char *nptr)
{
	long	result;

	result = 0;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\f' || *nptr == '\r'
		|| *nptr == '\n' || *nptr == '\v')
		nptr++;
	if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return ((long)(result));
}

int	args_check(char *str)
{
	int	i;
	int	flag;

	i = 0;
	if (str[0] == ' ' || str[0] == '\t')
		return (0);
	while (str[i] != '\0')
	{
		flag = 0;
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else if ((str[i] == ' ' || str[i] == '\t') && str[i + 1] != '\0')
		{
			if (++flag == 1)
				i++;
			else if (flag > 1)
				return (0);
		}
		else if (str[i] == '+' && (str[i + 1] >= '0' && str[i + 1] <= '9'))
			i = i + 2;
		else
			return (0);
	}
	return (1);
}

int	check_and_ret(char *str)
{
	long	num;

	num = 0;
	if (!args_check(str))
		error_message();
	num = ft_atoi(str);
	if (num < INT_MIN || num > INT_MAX)
		error_message();
	return (num);
}

void	ft_validate_fill(int arc, char **arv, t_table_data *tbl_data)
{
	if (arc == 5 || arc == 6)
	{
		tbl_data->num_philos = check_and_ret(arv[1]);
		tbl_data->time_to_die = check_and_ret(arv[2]);
		tbl_data->time_to_eat = check_and_ret(arv[3]);
		tbl_data->time_to_sleep = check_and_ret(arv[4]);
		tbl_data->number_of_times_philo_eat = -1;
		if (arc == 6)
			tbl_data->number_of_times_philo_eat = check_and_ret(arv[5]);
		if (tbl_data->time_to_die < 60 || tbl_data->time_to_eat < 60
			|| tbl_data->time_to_sleep < 60)
			error_message();
	}
	else
		error_message();
}
