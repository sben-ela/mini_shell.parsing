/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_couts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 11:40:53 by sben-ela          #+#    #+#             */
/*   Updated: 2023/02/21 16:51:54 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	count_words(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str [i])
	{
		while (str [i] && str [i] == c)
			i++;
		if (str [i])
			count ++;
		while (str[i] && str [i] != c)
		i++;
	}
	return(count);
}

// ls -l'a | echo "salah'"
int count_char(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while(str[i])
	{
		if(str[i] == c)
			count++;
		i++;
	}
	return(count);
}

char *handle_param(char *str, char c)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	j = 0;
	dst = malloc(ft_strlen(str) - count_char(str, c) + 1);
	if(!dst)
		return(0);
	while(str[i])
	{
		if(str[i] != c)
		{
			dst[j++] = str[i];
		}
		i++;
	}
	dst[j] = '\0';
	return(dst);
}

int	count_single_couts(char *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while(line[i])
	{
		if(line[i] == '\"' && count == 0)
		{
			i++;
			while(line[i] && line[i] != '\"')
				i++;
			i++;
		}
		if(line[i] == '\'')
			count++;
		i++;
	}
	//printf("SINGLE : %d\n", count);
	return(count % 2);
}

int	count_double_couts(char *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while(line[i])
	{
		if(line[i] == '\'' && count == 0)
		{
			i++;
			while(line[i] && line[i] != '\'')
				i++;
			i++;
		}
		if(line[i] == '\"')
			count++;
		i++;
	}
	//printf("DOUBLE : %d\n", count);
	return(count % 2);
}