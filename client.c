#include "minitalk.h"

int	put_error(char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	return (EXIT_FAILURE);
}

void	send_byte(int *byte, pid_t serv)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (byte[i] == 0)
		{
			if (kill(serv, SIGUSR1) == -1)
				exit(put_error("failed to send signal"));
		}
		else
		{
			if (kill(serv, SIGUSR2) == -1)
				exit(put_error("failed to send signal"));
		}
		usleep(300);
		i++;
	}
}

int	send_string(pid_t serv, const char *str)
{
	unsigned char	c;
	int				byte[8];
	int				i;
	int				j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		c = (unsigned char)str[i];
		while (j < 8)
		{
			if (c % 2 == 0)
				byte[7 - j] = 0;
			else
				byte[7 - j] = 1;
			c /= 2;
			j++;
		}
		send_byte(byte, serv);
		i++;
	}
	ft_bzero(byte, 4 * 8);
	send_byte(byte, serv);
	return (EXIT_SUCCESS);
}

void	get_answer(int signo)
{
	(void)signo;
	ft_putendl_fd("sending message ended.", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char const *argv[])
{
	pid_t	serv;

	if (argc != 3)
		return (put_error("invalid arguments."));
	serv = ft_atoi(argv[1]);
	signal(SIGUSR1, get_answer);
	send_string(serv, argv[2]);
	pause();
	return (EXIT_SUCCESS);
}
