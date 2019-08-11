/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 03:45:15 by jaelee            #+#    #+#             */
/*   Updated: 2019/08/11 09:46:07 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		atoi_hex(char *str)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		nbr = nbr << 4;
		if (ft_isdigit(str[i]))
			nbr |= str[i] - '0';
		else
		{
			if (str[i] >= 'A' && str[i] <= 'F')
				nbr |= str[i] - 'A' + 10;
			else
				nbr |= str[i] - 'a' + 10;
		}
		i++;
	}
	return (nbr);
}

int		ft_atoi_skip(char **str)
{
	int		i;
	int		neg;
	int		number;

	number = 0;
	neg = 1;
	i = 0;
	while (**str == 32 || (**str >= 9 && **str <= 13))
		((*str)++);
	if (**str == '-')
	{
		neg = -1;
		((*str)++);
	}
	else if (**str == '+')
		((*str)++);
	while (**str >= '0' && **str <= '9')
	{
		number = number * 10 + **str - '0';
		((*str)++);
	}
	return (number * neg);
}

static int	check_color(const char *str)
{
	int	i;
	int	len;

	len = (int)ft_strlen(str);
	if (len < 3 || len > 8)
		return (FAIL);
	if (str[0] != '0' && str[1] != 'x')
		return (FAIL);
	i = 2;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !((str[i] >= 'A' && str[i] <= 'F')
			|| ( str[i] >= 'a' && str[i] <= 'f' )))
			return (FAIL);
		i++;
	}
	return (VALID_COLOR);
}

static int	check_height(const char *str)
{
	int	i;

	i = 0;
	if(str[0] == '+' || str[0] == '-')
	{
		if (!str[1])
			return (FAIL);
		i++;
	}
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return(FAIL);
	}
	return (VALID_HEIGHT);
}

int			check_input(char *str, int *color_flag)
{
	char	**split;
	int		cnt;

	if(ft_strchr(str, COMMA))
	{
		if (!(split = ft_strsplit(str, COMMA)))
			return (FAIL);
		cnt = 0;
		while (split[cnt])
			cnt++;
		if (cnt != 2 || !check_height(split[0]) || !check_color(split[1]))
		{
			ft_splitdel(split);
			return (FAIL);
		}
		else
		{
			*color_flag = ON;
			ft_splitdel(split);
			return (VALID_HEIGHT_COLOR);
		}
	}
	else
		return(check_height(str));
}
