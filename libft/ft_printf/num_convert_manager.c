/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_convert_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:41:13 by alrobert          #+#    #+#             */
/*   Updated: 2022/11/16 15:00:09 by alrobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../libft.h"

void	d_convert(void *arg, t_info_cur_arg *info)
{
	(void)arg;
	ft_putnbr_fd(info->_int, 1);
}

void	x_convert(void *arg, t_info_cur_arg *info)
{
	(void)arg;
	ft_puthexa(info->_int, 'a');
}

void	xx_convert(void *arg, t_info_cur_arg *info)
{
	(void)arg;
	ft_puthexa(info->_int, 'A');
}
