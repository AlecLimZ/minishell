/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yang <yang@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 00:32:33 by yang              #+#    #+#             */
/*   Updated: 2021/05/22 21:03:53 by yang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	char_count(int n)
{
	size_t	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

static size_t	divide(size_t count)
{
	size_t	result;

	result = 1;
	while (count--)
	{
		result *= 10;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	char		*num;
	long		number;
	size_t		count;
	size_t		power;
	size_t		i;

	number = (long)n;
	count = char_count(number);
	num = (char *)malloc(sizeof(char) * count + 1);
	if (num == NULL)
		return (NULL);
	i = 0;
	if (number == 0 || number == -0)
		num[i++] = '0';
	power = count - 1;
	if (n < 0)
	{
		number = -number;
		num[i++] = '-';
		power--;
	}
	while ((number != 0 || number != -0) && i < count)
		num[i++] = '0' + (number / divide(power--) % 10);
	num[i] = '\0';
	return (num);
}
