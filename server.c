/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsion <nsion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:33:53 by nsion             #+#    #+#             */
/*   Updated: 2023/03/30 19:29:36 by nsion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_error(siginfo_t *siginfo, int signal)
{
	(void)(siginfo);
	if (kill(siginfo->si_pid, signal) == -1)
		exit(ft_printf("Error while sending"));
}

void	receive(int signum, siginfo_t *siginfo, void *texte)
{
	static int	bit = 0;
	static char	c = 0;

	(void)texte;
	if (signum == SIGUSR1)
		c = c | (1 << bit);
	else if (signum == SIGUSR2)
		c = c | (0 << bit);
	if (++bit == 8)
	{
		ft_printf("%c", c);
		if (c == '\0')
		{
			send_error(siginfo, SIGUSR2);
		}
		else
			send_error(siginfo, SIGUSR1);
		c = 0;
		bit = 0;
	}
	else
		send_error(siginfo, SIGUSR1);
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	pid = getpid();
	ft_printf("Le PID est : %d\n", pid);
	sa.sa_sigaction = receive;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
	}
	return (0);
}
