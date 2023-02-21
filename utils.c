/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:24:04 by aybiouss          #+#    #+#             */
/*   Updated: 2023/02/13 21:58:16 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while(str[i])
        i++;
    return(i);
}

int		ft_strcmp(char *s1, char *s2)
{
 	int	i;
 
 	i = 0;
	if(!s1 || !s2)
		return (-1);
 	while (s1[i] == s2[i] && s1[i] && s2[i])
 		i++;
 	return (s1[i] - s2[i]);
}

int ft_strchr (char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i++] == c)
			return(1);
	}
	return(0);
}

int	ft_lstsize(t_shell *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
char	*ft_strjoin(char *left_str, char *buff)
{
	int		i;
	int		j;
	char	*str;

	if (!left_str || !buff)
		return (0);
	str = malloc(ft_strlen(left_str) + ft_strlen(buff) + 1);
	if (!str)
		return (0);
	i = -1;
	j = 0;
	while (left_str[++i] != '\0')
		str[i] = left_str[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(left_str) + ft_strlen(buff)] = '\0';
	return (str);
}