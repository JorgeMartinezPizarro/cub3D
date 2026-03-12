/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guigonza <guigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:53:34 by jomarti3          #+#    #+#             */
/*   Updated: 2026/03/09 17:32:18 by guigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(char c)
{
	return (c == ' '
		|| c == '\t'
		|| c == '\n'
		|| c == '\f'
		|| c == '\r'
		|| c == '\v'
	);
}

int	ft_atoi(const char *str)
{
	long	sol;
	int		sign;

	sign = 1;
	sol = 0;
	while (ft_isspace(*str) == 1)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		sol = sol * 10 + (*str - '0');
		str++;
	}
	return ((int)(sol * sign));
}
