/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_convert_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:42:18 by alrobert          #+#    #+#             */
/*   Updated: 2022/11/16 15:43:53 by alrobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../libft.h"

void	c_convert(void *arg, t_info_cur_arg *info)
{
	(void)info;
	ft_putchar_fd(*((char *)arg), 1);
}

void	s_convert(void *arg, t_info_cur_arg *info)
{
	(void)arg;
	if (!info->_char)
		ft_putstr_fd("(null)", 1);
	ft_putstr_fd(info->_char, 1);
}

void	p_convert(void *arg, t_info_cur_arg *info)
{
	(void)arg;
	if (!(unsigned long int)arg)
		ft_putstr_fd("(nil)", 1);
	else
	{
		ft_putstr_fd("0x", 1);
		info->len += 2;
		ft_puthexa((unsigned long int)arg, 'a');
	}
}

void	prc_convert(void *arg, t_info_cur_arg *info)
{
	(void)arg;
	(void)info;
	ft_putchar_fd('%', 1);
}
