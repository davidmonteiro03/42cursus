/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 08:59:40 by dcaetano          #+#    #+#             */
/*   Updated: 2024/04/23 10:31:13 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	main(void)
{
	int	my_ret;
	int	cc_ret;

	printf("ft_printf: $");
	fflush(stdout);
	my_ret = ft_printf(" Name: %d  ", 5000);
	printf("$\n");
	printf("  printf : $");
	cc_ret = printf(" Name: %d  ", 5000);
	printf("$");
	printf("\n----------------\n");
	printf("my_ret: %d\n", my_ret);
	printf("cc_ret: %d\n", cc_ret);
	return (0);
}
