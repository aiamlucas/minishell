/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbueno-m <lbueno-m@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 22:57:54 by lbueno-m          #+#    #+#             */
/*   Updated: 2025/06/07 14:37:18 by lbueno-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H 

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	dispatcher(char specifier, va_list args);
int	dispatch_char(va_list args);
int	dispatch_string(va_list args);
int	dispatch_int(va_list args);
int	dispatch_percent(void);
int	dispatch_unsigned(va_list args);
int	dispatch_hex(va_list args, int is_uppercase);
int	dispatch_pointer(va_list args);
int	ft_putstr_len(char *str);
int	ft_putchar_len(char c);
int	ft_putnbr_len(int n);
int	ft_putunsigned_len(unsigned int n);
int	ft_puthex_len(unsigned int n, int is_uppercase);
int	ft_putpointer_len(void *p);

#endif
