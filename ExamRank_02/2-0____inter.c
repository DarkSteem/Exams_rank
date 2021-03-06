/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-0____inter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evgenkarlson <RTFM@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 12:33:14 by evgenkarlson      #+#    #+#             */
/*   Updated: 2021/01/04 23:13:53 by evgenkarlson     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** 


Assignment name  : inter
Expected files   : inter.c
Allowed functions: write
--------------------------------------------------------------------------------

Напишите программу, которая принимает две строки и отображает без двойных 
символов символы, которые появляются в обеих строках, в порядке, в котором 
они появляются в первой.

За ним последует новая строка.

Если количество аргументов не равно 2, программа отображает новую строку.


Примеры:

$>./inter "padinton" "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
padinto$
$>./inter ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
df6ewg4$
$>./inter "rien" "cette phrase ne cache rien" | cat -e
rien$
$>./inter | cat -e
$


   ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */

#include <unistd.h>

/* Функция проверки наличия повторяющегося символа в массиве. Проверка идет до тех пор пока счетчик не равен индексу */
int		ft_verif_char(char *str, char c, int index)	/* Принимаем адресс массива, символ, и порядковый номер символа(его индекс) */
{
	int		i;										/* обьявим переменную для счетчика */

	i = 0;											/* инициализируем счетчик нулем */
	while (i < index)								/* запускаем цикл, который ищет символ в массиве до тех пор пока счетчик 
													 * не будет равен индексу */
	{
		if (str[i] == c)							/* Проверяем есть ли в массве похожий символ */
			return (0);								/* если есть ворзвращаем 0 */
		i++;										/* если нет проверяем дальше пока счетчик не будет равен индексу либо мы не дойдем до конца массива */
	}
	return (1);										/* если похожего символа не нашли возвращаем 1 */
}

/* Функция принимает две строки и отображает без двойных символов символы, которые
 * появляются в обеих строках, в порядке, в котором они появляются в первой. (символы не должны повторяться) */
void	ft_inter(char *s1, char *s2)				/* принимаем адреса строк и записываем их в указатели */
{
	int		i;										/* обьявим переменную для счетчика i */
	int		j;										/* обьявим переменную для счетчика j */

	i = 0;											/* инициализируем переменную счетчика для первого массива нулем */
	while (s1[i])									/* Запускаем цикл. Он будет искать символы из первой строки во второй строке и
                                        			** напечатает их(в том порядке в котором они идут) если найдет пока не дойдет до конца */
	{
		if (ft_verif_char(s1, s1[i], i))			/* Проверяем появлялся ли ранее в первой строке текущий символ, если такой же символ был 
													** ранее то мы игнорируем этот символ и переходим к след ячейке, если нет то запускаем код 
													** ниже который проверит есть ли этот символ во второй строке и после, если найдет, напечатает его */
		{
			j = 0;									/* инициализируем переменную счетчика второго массива нулем */
			while (s2[j])							/* запускаем цикл который будет проверять наличие во втором массиве символа из первого массива  */
			{
				if (s1[i] == s2[j])					/* если во втором массиве символ найден */
				{
					write(1, &s1[i], 1);			/* то печатаем его */
					break ;							/* и завершаем цикл */
				}
				j++;								/* Если в текущей ячейке второго массива `s2` не найден символ из ячейки `s1[i]`, то мы проходимся 
													** дальше по другим ячейкам строки `s2`. продолжая в ней поиск символа из ячейки `s1[i]` до тех пор 
													** пока не дойдем до конца массива `s2` */
			}
		}
		i++;										/* Переходим к следующему символу первого массива для проверки нахождения его во втором массиве */
	}
}

int		main(int argc, char **argv)			/* здесь принимаем количество строк в массиве и сам массив со строками */
{
	if (argc == 3)							/* Проверяем есть ли кроме имени программы в аргументах еще и две нужные нам строки */
		ft_inter(argv[1], argv[2]);			/* Если все нужные аргументы на месте отправляем их в функцию */
	write(1, "\n", 1);						/* Печатаем символ перехода на новую строку */
	return (0);								/* Завершаем программу */
}


/* ************************************************************************** */
/* ****************************_OR_THAT:)_*********************************** */
/* ************************************************************************** */


#include <unistd.h>


/* Функция проверки наличия повторяющегося символа в массиве. Проверка идет до тех пор пока счетчик не равен индексу (или индекс не равен -1) */
int     ft_verif_char(char *str, char c, int index)	/* Принимаем адресс массива, символ, и порядковый номер символа(его индекс) */
{
    int     i;                              		/* Обьявим переменную для счетчика */
    
    i = 0;                                  		/* Инициализируем счетчик нулем */
    while (str[i] && (i < index || index == -1))	/* Запускаем цикл, который ищет символ в массиве до тех пор пока счетчик не указывает на  
													** ячейку с символом конца массива И пока счетчик не равен индексу(или индекс не равен -1) */
    {
	    if (str[i] == c)							/* Проверяем есть ли в массве похожий символ */
            return (0);                             /* если есть ворзвращаем 0 */
		i++;										/* Если нет проверяем дальше пока счетчик не будет равен индексу либо мы не дойдем до конца массива */
    }
	return (1);										/* Если похожего символа не нашли возвращаем 1 */
}


/* Функция принимает две строки и отображает без двойных символов символы, которые
 * появляются в обеих строках, в порядке, в котором они появляются в первой. (символы не должны повторяться) */
void	ft_inter(char *s1, char *s2)				/* Принимаем адреса строк и записываем их в указатели */
{
    int     i;                          			/* Обьявим переменную для счетчика */
    
	i = 0;                          				/* Инициализируем счетчик нулем чтобы начать с нулевой ячейки массива */
	while(s1[i])               						/* Запускаем цикл. Он будет искать символы из первой строки во второй строке и 
													** напечатает их если найдет в том порядке в котором они идут пока не дойдет до конца */
	{
		if (ft_verif_char(s1, s1[i], i) && !ft_verif_char(s2, s1[i], -1))	/* Проверяем. если в первом массиве ранее таких символов
																			** небыло, а во втором такой символ есть */
			write(1, &s1[i], 1);											/* То печатаем этот символ */
		i++;										/* Переходим к следующему символу первого массива для проверки нахождения его во втором массиве */
	}
}


int		main(int argc, char **argv)			/* здесь принимаем количество строк в массиве и сам массив со строками */
{
	if (argc == 3)							/* Проверяем есть ли кроме имени программы в аргументах еще и две нужные нам строки */
		ft_inter(argv[1], argv[2]);			/* Если все нужные аргументы на месте отправляем их в функцию */
	write(1, "\n", 1);						/* Печатаем символ перехода на новую строку */
	return (0);								/* Завершаем программу */
}
