/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:55:09 by aybiouss          #+#    #+#             */
/*   Updated: 2023/02/15 18:34:56 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*hay;

	i = 0;
	hay = (char *) haystack;
	if (*needle == '\0')
		return ((char *)haystack);
	while (hay[i])
	{
		j = 0;
		while (hay[i + j] == needle[j] && hay[i + j] != '\0' && len > (i + j))
		{
			if (needle[j + 1] == '\0')
				return (hay + i);
			j++;
		}
		i++;
	}
	return (0);
}
