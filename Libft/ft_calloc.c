/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 08:20:58 by aybiouss          #+#    #+#             */
/*   Updated: 2022/10/24 08:28:37 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitmes, size_t size)
{
	void	*res;

	if (size && (SIZE_MAX / size) < nitmes)
		return (NULL);
	res = malloc(nitmes * size);
	if (!res)
		return (NULL);
	ft_bzero(res, nitmes * size);
	return (res);
}
