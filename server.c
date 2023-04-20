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

void 		receive(int signum, siginfo_t *siginfo, void *texte)
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
			if (kill(siginfo->si_pid, SIGUSR2) == -1)
				exit(ft_printf("Error while sending"));
		}
		else
		{
			if (kill(siginfo->si_pid, SIGUSR1) == -1)
			exit(ft_printf("Error while sending"));
		}
		c = 0;
		bit = 0;
	}
	else
	{
		if (kill(siginfo->si_pid, SIGUSR1) == -1)
			exit(ft_printf("Error while sending"));
	}
}

int	main(void)
{
	int pid;
	struct sigaction sa;

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