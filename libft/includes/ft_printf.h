/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 13:17:58 by clanier           #+#    #+#             */
/*   Updated: 2017/01/31 18:45:14 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <wchar.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdbool.h>
# include <inttypes.h>
# include "libft.h"

typedef struct				s_pline
{
	va_list					ap;
	int						i;
	int						iflag;
	int						size;
	int						count;
	bool					color;

	int						len;
	int						dlen;
	int						dotv;
	int						spaces;
	bool					csign;
	bool					bspace;

	bool					star;
	bool					lstar;
	int						lvstar;
	bool					dstar;
	int						dvstar;

	bool					plus;
	bool					neg;
	bool					minus;
	bool					ht;
	bool					zero;
	bool					dot;
	bool					dotb;

	bool					l;
	bool					ll;
	bool					h;
	bool					hh;
	bool					j;
	bool					z;

	bool					nbase;

	int						id;
	short int				hid;
	signed char				hhid;
	long int				lid;
	long long int			llid;
	intmax_t				jid;
	size_t					zid;

	double					f;

	unsigned int			u;
	unsigned short int		hu;
	unsigned char			hhu;
	unsigned long int		lu;
	unsigned long long int	llu;
	uintmax_t				ju;
	size_t					zu;

	unsigned int			x;
	unsigned short int		hx;
	unsigned char			hhx;
	unsigned long int		lx;
	unsigned long long int	llx;
	uintmax_t				jx;
	size_t					zx;

	unsigned int			o;
	unsigned short int		ho;
	unsigned char			hho;
	unsigned long int		lo;
	unsigned long long int	llo;
	uintmax_t				jo;
	size_t					zo;

	void					*p;

	char					*s;
	wchar_t					*ls;
}							t_pline;

int							ft_iscolor(t_pline *pline, char *msg);
void						ft_print_hex(int n, char c);
void						ft_pline_init(t_pline *pline);
int							ft_wintlen(wchar_t chr);
int							ft_wcharlen(wchar_t *str);
int							ft_l_strlen(t_pline *pline, wchar_t *str);
int							ft_s_strlen(t_pline *pline, char *str);
int							ft_pnbrlen(t_pline *pline, int n);
int							ft_ll_nbrlen(t_pline *pline, long long int n);
int							ft_l_nbrlen(t_pline *pline, long int n);
int							ft_hh_nbrlen(t_pline *pline, signed char n);
int							ft_h_nbrlen(t_pline *pline, short int n);
int							ft_j_nbrlen(t_pline *pline, intmax_t n);
int							ft_u_nbrlen(t_pline *pline, unsigned int n);
int							ft_ull_nbrlen(t_pline *pline,
							unsigned long long int n);
int							ft_ul_nbrlen(t_pline *pline, unsigned long int n);
int							ft_uhh_nbrlen(t_pline *pline, unsigned char n);
int							ft_uh_nbrlen(t_pline *pline,
							unsigned short int n);
int							ft_uj_nbrlen(t_pline *pline, uintmax_t n);
int							ft_z_nbrlen(t_pline *pline, size_t n);
int							ft_floatlen(t_pline *pline);
int							ft_ull_octlen(t_pline *pline,
							unsigned long long int n);
int							ft_ul_octlen(t_pline *pline, unsigned long int n);
int							ft_uhh_octlen(t_pline *pline, unsigned char n);
int							ft_uh_octlen(t_pline *pline,
							unsigned short int n);
int							ft_uj_octlen(t_pline *pline, uintmax_t n);
int							ft_z_octlen(t_pline *pline, size_t n);
int							ft_u_octlen(t_pline *pline, unsigned int n);
int							ft_ull_hexlen(t_pline *pline,
							unsigned long long int n);
int							ft_ul_hexlen(t_pline *pline, unsigned long int n);
int							ft_uhh_hexlen(t_pline *pline, unsigned char n);
int							ft_uh_hexlen(t_pline *pline,
							unsigned short int n);
int							ft_uj_hexlen(t_pline *pline, uintmax_t n);
int							ft_z_hexlen(t_pline *pline, size_t n);
int							ft_u_hexlen(t_pline *pline, unsigned int n);
int							ft_ptrlen(t_pline *pline, void *ptr);
int							ft_flag_s(t_pline *pline);
wchar_t						*ft_wchardup(wchar_t *s, int *dup);
int							ft_flag_ls(t_pline *pline);
int							ft_flag_c(t_pline *pline, int c);
int							ft_flag_lc(t_pline *pline, wchar_t c);
int							ft_flag_llu(t_pline *pline);
int							ft_flag_lu(t_pline *pline);
int							ft_flag_hhu(t_pline *pline);
int							ft_flag_hu(t_pline *pline);
int							ft_flag_ju(t_pline *pline);
int							ft_flag_zu(t_pline *pline);
int							ft_flag_u(t_pline *pline);
void						ft_long_overflow(t_pline *pline, char c);
int							ft_flag_llid(t_pline *pline);
int							ft_flag_lid(t_pline *pline);
int							ft_flag_hhid(t_pline *pline);
int							ft_flag_hid(t_pline *pline);
int							ft_flag_jid(t_pline *pline);
int							ft_flag_zid(t_pline *pline);
int							ft_flag_id(t_pline *pline);
void						ft_round_f(t_pline *pline);
void						ft_f_putnbr(t_pline *pline);
int							ft_flag_f(t_pline *pline);
int							ft_flag_llo(t_pline *pline);
int							ft_flag_lo(t_pline *pline);
int							ft_flag_hho(t_pline *pline);
int							ft_flag_ho(t_pline *pline);
int							ft_flag_jo(t_pline *pline);
int							ft_flag_zo(t_pline *pline);
int							ft_flag_o(t_pline *pline);
int							ft_flag_llx(t_pline *pline, char c);
int							ft_flag_lx(t_pline *pline, char c);
int							ft_flag_hhx(t_pline *pline, char c);
int							ft_flag_hx(t_pline *pline, char c);
int							ft_flag_jx(t_pline *pline, char c);
int							ft_flag_zx(t_pline *pline, char c);
int							ft_flag_x(t_pline *pline, char c);
int							ft_flag_p(t_pline *pline);
int							ft_flag_percent(t_pline *pline);
int							ft_get_size(t_pline *pline, char c);
int							ft_get_type(t_pline *pline, const char *msg);
void						ft_invalid_flag(t_pline *pline, char c);
void						ft_call_id_flag(t_pline *pline, char c);
void						ft_call_u_flag(t_pline *pline, char c);
void						ft_call_o_flag(t_pline *pline, char c);
void						ft_call_x_flag(t_pline *pline, char c);
void						ft_call_c_flag(t_pline *pline, char c);
void						ft_call_s_flag(t_pline *pline, char c);
void						ft_check_sign(t_pline *pline, char c);
void						ft_print_plus(t_pline *pline, char c);
void						ft_print_width(t_pline *pline, char c);
void						ft_print_prec(t_pline *pline, char c);
void						ft_print_ht(t_pline *pline, char c);
void						ft_get_values(t_pline *pline, char c);
void						ft_print_space(t_pline *pline, const char *msg);
int							ft_check_flags(t_pline *pline, char *msg);
char						ft_format_flags(t_pline *pline, const char *msg);
void						ft_flags(t_pline *pline, const char *msg);
int							ft_printf(const char *msg, ...);

#endif
