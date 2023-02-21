/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:21:41 by aybiouss          #+#    #+#             */
/*   Updated: 2023/02/12 12:21:41 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_putnstr(char *str, int n)
{
	int		i;

	i = -1;
	if (n < 0)
	{
		while (str[++i] && i < (int)ft_strlen(str) + n)
			ft_putchar(str[i]);
	}
	else
	{
		while (str[++i] && i < n)
			ft_putchar(str[i]);
	}
}

void    is_quote(char c)
{
    return (c == '"' || c == '\'')
}

void    echo(char **str, int pos)
{
    int		start;
	int		end;
	int		strl;

    start = is_quote(str[pos][0]);
    strl = ft_strlen(str[pos]);
    end = is_quote(str[pos][strl - 1]);
    if (end && start)
		ft_putnstr(str[pos] + 1, -1);
	else if (end)
		ft_putnstr(str[pos], -1);
	else if (start)
		ft_putstr(str[pos] + 1);
	else
		ft_putstr(str[pos]);
}

int    echo_builtin(char **cmd)
(
    int i:
    int flag;

    flag = 0;
    if (!cmd[0])
    {
        write(1, '\n', 1);
        return (1);
    }
    else if (cmd[0][0] == '-' && cmd[0][1] == "n" && cmd[0][2] == '\0')
        flag = 1;
    i = -1;
	if (flag)
		++i;
    while (cmd[++i])
    {
		echo(cmd, i);
		if (!cmd[i + 1] && flag)
			ft_putchar('\n');
	}
    return (1);
)
