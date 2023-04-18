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

void 		use_sigusr1(int signum, siginfo_t *siginfo, void *texte)
{
	static int	i;

	i = 0;
	(void)texte;
	(void)siginfo;
	while (i < 8)
	{
		if(signum == SIGUSR1)
		{
			i++;
			ft_printf("Signal recu : %d	", signum);
		}
		else if(signum == SIGUSR2)
		{
			i++;
			ft_printf("Signal recu : %d	", signum);
		}
	}
	ft_printf("8bit recu : %d	", i);
}

int	main(void)
{
	pid_t pid;
	struct sigaction sa;

    pid = getpid();
	ft_printf("Le PID est : %d\n", pid);
	sa.sa_sigaction = use_sigusr1;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
	
    while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
	}
    return (0);
}