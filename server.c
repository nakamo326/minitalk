#include "minitalk.h"

int	output_error(char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	return (EXIT_FAILURE);
}

void	send_received(siginfo_t *info)
{
	if (kill(info->si_pid, SIGUSR1) == -1)
		exit(output_error("failed to send signal to client."));
}

void	handler(int signo, siginfo_t *info, void *ctx)
{
	unsigned char	c;
	static int		num = 0;
	static int		digit = 0;

	(void)ctx;
	if (digit < 8)
	{
		num = num << 1;
		if (signo == SIGUSR2)
			num += 1;
		digit++;
	}
	if (digit == 8)
	{
		c = num;
		if (c == '\0')
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			send_received(info);
		}
		else
			ft_putchar_fd(c, STDOUT_FILENO);
		num = 0;
		digit = 0;
	}
}

bool	set_signal(void)
{
	struct sigaction	act;

	if (sigemptyset(&act.sa_mask) == -1)
		return (false);
	act.sa_sigaction = handler;
	act.sa_flags = SA_RESTART | SA_SIGINFO;
	if (sigaction(SIGUSR1, &act, NULL) == -1)
		return (false);
	if (sigaction(SIGUSR2, &act, NULL) == -1)
		return (false);
	return (true);
}

int	main(int argc, char const *argv[])
{
	pid_t	pid;

	if (argc != 1 || argv[1] != NULL)
		return (output_error("Invalid argument."));
	pid = getpid();
	ft_putstr_fd("pid: ", STDOUT_FILENO);
	ft_putnbr_fd(pid, STDOUT_FILENO);
	ft_putendl_fd("", STDOUT_FILENO);
	if (!set_signal())
		return (output_error("failed to set signal."));
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
