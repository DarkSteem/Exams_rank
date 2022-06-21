/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5-1____check_mate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evgenkarlson <RTFM@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 12:33:14 by evgenkarlson      #+#    #+#             */
/*   Updated: 2021/02/25 20:16:15 by evgenkarlson     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* ************************************************************************** */
/* ************************************************************************** **


Assignment name  : checkmate 
Expected files   : *.c, *.h
Allowed functions: write, malloc, free
--------------------------------------------------------------------------------

Напишите программу, в которой аргументы принимаются за строки шахматной 
доски, и проверьте, находится ли ваш король в проверочной позиции.

В шахматы играют на шахматной доске, квадратной доске длиной 8 квадратов 
с определенными фигурами на ней: король, королева, епископ, рыцарь, ладья 
и пешки.

В этом упражнении вы будете играть только с пешками, слонами, ладьями и 
королевой ... и, очевидно, с королем.

У каждой части есть определенный метод движения, и все образцы захвата 
подробно описаны в файле examples.txt.

Часть может захватить только первую вражескую фигуру, которую она находит 
на своих образцах захвата.

Доска имеет переменный размер, но остается квадратом. Есть только один 
король, а все остальные фигуры против. Все остальные символы, кроме 
используемых для фигур, считаются пустыми квадратами.

Король считается находящимся в контрольном положении, когда другая 
вражеская фигура может захватить его. В этом случае вы напечатаете 
«Success» на стандартном выводе, за которым следует новая строка, 
в противном случае вы напечатаете «Fail», за которым следует новая 
строка.

Если аргументов нет, программа напечатает только новую строку.


Пример:

$> ./chessmate '..' '.K' | cat -e
Fail$
$> ./chessmate 'R...' '..P.' '.K..' '....' | cat -e
Success$
$> ./chessmate 'R...' 'iheK' '....' 'jei.' | cat -e
Success$
$> ./chessmate | cat -e
$
$>



Примеры:

Пешка / Pawn (P):

	. . . . . . .
	. . . . . . .
	. . X . X . .
	. . . P . . .
	. . . . . . .
	. . . . . . .
	. . . . . . .

СЛОН / Bishop (B):

	X . . . . . X
	. X . . . X .
	. . X . X . .
	. . . B . . .
	. . X . X . .
	. X . . . X .
	X . . . . . X

Ладья(Епископ) / Rook (R):

	. . . X . . .
	. . . X . . .
	. . . X . . .
	X X X R X X X
	. . . X . . .
	. . . X . . .
	. . . X . . .

Королева / Queen (Q)

	X . . X . . X
	. X . X . X .
	. . X X X . .
	X X X Q X X X
	. . X X X . .
	. X . X . X .
	X . . X . . X 


** ************************************************************************** */
/* ************************************************************************** */


#include <stdlib.h>
#include <unistd.h>


void	ft_putchar(char c)
{
	write(1, &c, 1);
}


void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (*(str + i))
		i++;
	write(1, str, i);
}

int		checkmate(int size, char **map)
{
	int		i;
	int		y;
	int		x;

	y = 0;
	x = 0;
	// поиск Короля
	while (y < size)
	{
		x = 0;
		while (map[y][x] && (map[y][x] != 'K'))
			x++;
		if (map[y][x] == 'K')
			break;
		y++;
	}
	// проверяем, угрожает ли Королю Пешка
	if (map[y + 1][x + 1] == 'P' || map[y + 1][x - 1] == 'P')
		return (0);
	i = 0;
	// проверяем, угрожают ли Королю другие фигуры
	while (i < size)
	{
		// проверяем, угрожают ли Королю фигуры расположенные над ним, расположеные под ним и расположеные по краям от него
		if (map[y][i] == 'Q' || map[y][i] == 'R' || map[i][x] == 'Q' || map[i][x] == 'R')
			return (0);
		// проверяем, угрожают ли Королю фигуры расположенные по диагонали в верхней половине шахматной доски
		if (i < y)
		{
			// проверяем диагональ сверху слева от Короля
			if ((x > i) && ((map[y - i - 1][x - i - 1] == 'B') || (map[y - i - 1][x - i - 1] == 'Q')))
				return (0);
			// проверяем диагональ сверху справа от Короля
			if (x + i < size && ((map[y - i - 1][x + i + 1] == 'B') || (map[y - i - 1][x + i + 1] == 'Q')))
				return (0);
		}
		// проверяем, угрожают ли Королю фигуры расположенные по диагонали в нижней половине шахматной доски
		if (i >= y)
		{
			// проверяем диагональ снизу слева от Короля
			if ((x < i) && ((map[y + i + 1] [x - i - 1] == 'B') || (map[y + i + 1] [x - i - 1] == 'Q')))
				return (0);
			// проверяем диагональ снизу справа от Короля
			if (x + i < size && ((map[y + i + 1] [x + i + 1] == 'B') || (map[y + i + 1] [x + i + 1] == 'Q')))
				return (0);
		}
		i++;
	}
	return (1);
}

void	ft_print_tab(int size, char **tab)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_putstr(tab[i++]);
		ft_putchar('\n');
	}
}


int		main(int ac, char **av)
{
	if ((ac % 2) && checkmate(ac - 1, av + 1))
		write(1, "Success\n", 8);
	else if (ac == 1)
		ft_putchar('\n');
	else
		write(1, "Fail\n", 5);
	// ft_print_tab(ac - 1, av + 1);
	return (0);
}



/*------------------------------------------------------------------------------

-=РАБОТАЕТ=-

$> gcc checkmate.c && ./a.out 'R...' '..P.' '....' 'K...' | cat -e
Success$
$>

     0 | 1 2 3 4
    ---|--------------> (x)
     1 | R . . .
     2 | . . P .
     3 | . . . .
     4 | K . . .
       |
      \|/
	   '
      (y) 

--------------------------------------------------------------------------------

-=РАБОТАЕТ=-

$> gcc checkmate.c && ./a.out 'R...' 'iheK' '....' 'jeiR' | cat -e
Fail$
$>

     0 | 1 2 3 4
    ---|--------------> (x)
     1 | R . . .
     2 | . . . K
     3 | . . . .
     4 | . . . R
       |
      \|/
	   '
      (y) 

--------------------------------------------------------------------------------

-=РАБОТАЕТ=-

$> gcc checkmate.c && ./a.out 'R...' 'iheK' '....' 'jei.' | cat -e
Success$
$>

     0 | 1 2 3 4
    ---|--------------> (x)
     1 | R . . .
     2 | . . . K
     3 | . . . .
     4 | . . . .
       |
      \|/
	   '
      (y) 

--------------------------------------------------------------------------------

-=РАБОТАЕТ=-

$> gcc checkmate.c && ./a.out '..R.' '.Q..' '..BK' '...P' | cat -e
Success$
>$

     0 | 1 2 3 4
    ---|--------------> (x)
     1 | . . R .
     2 | . Q . .
     3 | . . B K
     4 | . . . P
       |
      \|/
	   '
      (y) 

--------------------------------------------------------------------------------

-=РАБОТАЕТ=-

$> gcc checkmate.c && ./a.out '..R.' '.Q..' '..BK' '..P.' | cat -e
Fail$
$>

     0 | 1 2 3 4
    ---|--------------> (x)
     1 | . . R .
     2 | . Q . .
     3 | . . B K
     4 | . . P .
       |
      \|/
	   '
      (y) 

--------------------------------------------------------------------------------

-=РАБОТАЕТ=-

$> gcc checkmate.c && ./a.out 'R...' '..P.' '.K..' '....' | cat -e
Success$
$>

     0 | 1 2 3 4
    ---|--------------> (x)
     1 | R . . .
     2 | . . P .
     3 | . K . .
     4 | . . . .
       |
      \|/
	   '
      (y) 
	  
--------------------------------------------------------------------------------


-=РАБОТАЕТ c другим размером карты=-

$> gcc checkmate.c && ./a.out 'B.......' '........' '.....Q..' '........' '........' '........' '......K.' '...P.....'
Fail
$>

     0 | 1  2  3  4  5  6  7  8
    ---|------------------------> (x)
     1 | B  .  .  .  .  .  .  .
     2 | .  .  .  .  .  .  .  .
     3 | .  .  .  .  .  Q  .  .
     4 | .  .  .  .  .  .  .  .
     5 | .  .  .  .  .  .  .  .
     6 | .  .  .  .  .  .  .  .
     7 | .  .  .  .  .  .  K  .
     8 | .  .  .  P  .  .  .  .
       |
      \|/
	   '
      (y) 


--------------------------------------------------------------------------------


-=РАБОТАЕТ c другим размером карты=-

$> gcc checkmate.c && ./a.out '........' '........' '.....Q..' '........' '........' '........' '......K.' '...P.....'
Success
$>

     0 | 1  2  3  4  5  6  7  8
    ---|------------------------> (x)
     1 | .  .  .  .  .  .  .  .
     2 | .  .  .  .  .  .  .  .
     3 | .  .  .  .  .  Q  .  .
     4 | .  .  .  .  .  .  .  .
     5 | .  .  .  .  .  .  .  .
     6 | .  .  .  .  .  .  .  .
     7 | .  .  .  .  .  .  K  .
     8 | .  .  .  P  .  .  .  .
       |
      \|/
	   '
      (y) 



------------------------------------------------------------------------------*/

