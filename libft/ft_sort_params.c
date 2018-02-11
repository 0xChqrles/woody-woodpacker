/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/07 17:41:29 by clanier           #+#    #+#             */
/*   Updated: 2017/01/07 16:41:48 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	**ft_sort_params(char **folderss, int n)
{
	int		i;
	int		find;
	char	*tmp;

	i = 0;
	find = 1;
	while (find)
	{
		find = 0;
		i = 1;
		while (n > i)
		{
			if (ft_strcmp(folders[i], folders[i + 1]) > 0)
			{
				tmp = folders[i];
				folders[i] = folders[i + 1];
				folders[i + 1] = tmp;
				find = 1;
			}
			i++;
		}
	}
	return (folders);
}
