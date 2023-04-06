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

void char_received(int signal, siginfo_t *info, void *context)
{
	static int	i = 0;
	static char c = 0;
	
	(void)context;
	(void)info;
	if (signal == SIGUSR1)
		c = c << 1 | i;
	i++;
	if (i == 8)
	{
		ft_printf("%c", c);
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction sa;

	sa.sa_sigaction = &char_received;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		ft_printf("Error: cannot handle SIGUSR1");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_printf("Error: cannot handle SIGUSR2");
	ft_printf("PID : %d\n", getpid());
	while (1)
		pause();
}