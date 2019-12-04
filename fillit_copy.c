# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef struct	s_piece
{
	int				blockcoords[8];
	char			pieceletter;
	int				x_offset;
	int				y_offset;
	struct s_piece	*next;
}				t_piece;

typedef struct	s_map
{
	char		**array;
}				t_map;

int				in_bounds(t_piece *piece, int map_size, char axis);
int				overlap(t_map *map, t_piece *piece);
int				solve_map(t_map *map, t_piece *piecelist, int map_size);
void			place(t_piece *piece, t_map *map, char letter);
size_t			count_pieces(t_piece *piecelist);
void			print_map(t_map *map, int size);
int				round_up_sq_rt(int num);
t_map			*new_map(int size);
void			solve(t_piece *piecelist);
t_piece			*parser(char *filename);
t_piece			*makepiece(char *buf, char pieceletter);
t_piece			*makelist(char *buf, int size);
t_piece			*align(t_piece *piece);
void			shift_x(t_piece *piece, int n);
void			shift_y(t_piece *piece, int y);
int				valid(char *buf, int size);
int				charcount(char *buf);
int				adjacency_counter(char *buf);
void			free_piecelist(t_piece *list);
void			free_map(t_map *map, int map_size);


//==============================================================================
int		charcount(char *buf)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (i < 19)
	{
		if (buf[i] && buf[i] != '\n' && buf[i] != '#' && buf[i] != '.')
			return (0);
		if (buf[i] == '\n' && !(((i + 1) % 5) == 0))
			return (0);
		if (buf[i] == '#')
			count++;
		i++;
	}
	if (!buf[i] || buf[i] != '\n')
		return (0);
	return (count);
}

/*
**	Checks each '#' character to see if it's adjacent to another
**	Returns a count of these adjacencies to validate piece shape
**	A valid piece with 4 '#' characters will either have 6 or 8 adjacencies
*/

int		adjacency_counter(char *buf)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < 19)
	{
		if (buf[i] == '#')
		{
			if (i + 1 <= 18 && buf[i + 1] == '#')
				count++;
			if (i - 1 >= 0 && buf[i - 1] == '#')
				count++;
			if (i + 5 <= 18 && buf[i + 5] == '#')
				count++;
			if (i - 5 >= 0 && buf[i - 5] == '#')
				count++;
		}
		i++;
	}
	return (count);
}

/*
**	Iterates through buf 21 char (one piece chunk) at a time
**	Calls checking functions to confirm validity
**	Returns false (0) if any checks are failed
*/

int		valid(char *buf, int size)
{
	int i;

	i = 0;
	while (i <= size)
	{
		if (charcount(buf + i) != 4)
			return (0);
		if (adjacency_counter(buf + i) != 6 && adjacency_counter(buf + i) != 8)
			return (0);
		i += 21;
	}
	return (1);
}

//==============================================================================


int		overlap(t_map *map, t_piece *piece)
{
	int i;
	int x;
	int y;

	i = 0;
	x = 0;
	y = 0;
	x = piece->blockcoords[i] + piece->x_offset;
	y = piece->blockcoords[i + 1] + piece->y_offset;
	while (i <= 6 && map->array[y][x] == '.')
	{
		i += 2;
		x = piece->blockcoords[i] + piece->x_offset;
		y = piece->blockcoords[i + 1] + piece->y_offset;
	}
	return (i != 8);
}

void	place(t_piece *piece, t_map *map, char letter)
{
	int i;
	int x;
	int y;

	i = 0;
	x = 0;
	y = 0;
	while (i <= 6)
	{
		x = piece->blockcoords[i] + piece->x_offset;
		y = piece->blockcoords[i + 1] + piece->y_offset;
		map->array[y][x] = letter;
		i += 2;
	}
}

int		in_bounds(t_piece *piece, int map_size, char axis)
{
	if (axis == 'y')
		return (piece->blockcoords[1] + piece->y_offset < map_size &&
				piece->blockcoords[3] + piece->y_offset < map_size &&
				piece->blockcoords[5] + piece->y_offset < map_size &&
				piece->blockcoords[7] + piece->y_offset < map_size);
	else
		return (piece->blockcoords[0] + piece->x_offset < map_size &&
				piece->blockcoords[2] + piece->x_offset < map_size &&
				piece->blockcoords[4] + piece->x_offset < map_size &&
				piece->blockcoords[6] + piece->x_offset < map_size);
}

/*
** While in bounds, if it doesn't overlap place the piece. Use recursion
** to check if the rest can fit with the current piece placed where it is.
**  Otherwise it backtracks and moves current piece
** then checks if all the pieces that come after fit with current piece moved.
** place() can either place the piece or place '.' to clear a piece.
*/

int		solve_map(t_map *map, t_piece *piece, int map_size)
{
	if (!piece)
		return (1);
	piece->x_offset = 0;
	piece->y_offset = 0;
	while (in_bounds(piece, map_size, 'y'))
	{
		while (in_bounds(piece, map_size, 'x'))
		{
			if (!overlap(map, piece))
			{
				place(piece, map, piece->pieceletter);
				if (solve_map(map, piece->next, map_size))
					return (1);
				else
				{
					place(piece, map, '.');
				}
			}
			piece->x_offset++;
		}
		piece->x_offset = 0;
		piece->y_offset++;
	}
	return (0);
}

/*
** Start with the smallest map map_size for number of blocks in pieces.
*/

void	solve(t_piece *piecelist)
{
	t_map	*map;
	int		map_size;

	map_size = round_up_sq_rt(count_pieces(piecelist) * 4);
	map = new_map(map_size);
	while (!solve_map(map, piecelist, map_size))
	{
		free_map(map, map_size);
		map_size++;
		map = new_map(map_size);
	}
	print_map(map, map_size);
	free_map(map, map_size);
}


//==============================================================================

void	shift_x(t_piece *piece, int n)
{
	piece->blockcoords[0] += n;
	piece->blockcoords[2] += n;
	piece->blockcoords[4] += n;
	piece->blockcoords[6] += n;
}

/*
**	Shifts a piece 'n' places along the y-axis
*/

void	shift_y(t_piece *piece, int n)
{
	piece->blockcoords[1] += n;
	piece->blockcoords[3] += n;
	piece->blockcoords[5] += n;
	piece->blockcoords[7] += n;
}

//==============================================================================
void		free_piecelist(t_piece *list)
{
	t_piece *tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

/*
**	Aligns piece to upper-left corner of its field using shifters
*/

t_piece		*align(t_piece *piece)
{
	while (piece->blockcoords[0] != 0 && \
			piece->blockcoords[2] != 0 && \
			piece->blockcoords[4] != 0 && \
			piece->blockcoords[6] != 0)
		shift_x(piece, -1);
	while (piece->blockcoords[1] != 0 && \
			piece->blockcoords[3] != 0 && \
			piece->blockcoords[5] != 0 && \
			piece->blockcoords[7] != 0)
		shift_y(piece, -1);
	return (piece);
}

/*
** Mallocs a new piece struct
** Finds & stores coordinates of '#' characters
** Initializes offsets to zero
** Returns aligned piece struct
*/

t_piece		*makepiece(char *buf, char pieceletter)
{
	t_piece	*piece_ptr;
	int		x;
	int		y;
	int		i;

	i = 0;
	x = 0;
	y = 1;
	if (!(piece_ptr = (t_piece*)malloc(sizeof(t_piece))))
		return (NULL);
	while (i < 20)
	{
		if (buf[i] == '#')
		{
			piece_ptr->blockcoords[x] = (i >= 5) ? (i % 5) : i;
			piece_ptr->blockcoords[y] = i / 5;
			x += 2;
			y += 2;
		}
		i++;
	}
	piece_ptr->x_offset = 0;
	piece_ptr->y_offset = 0;
	piece_ptr->pieceletter = pieceletter;
	return (align(piece_ptr));
}

/*
** Passes the buffer to makepiece() one piece-chunk at a time (21 chars)
** Assigns letter to the made piece
** Returns a linked list of piece structs
*/

t_piece		*makelist(char *buf, int size)
{
	t_piece *current;
	t_piece *beginning;
	int		i;
	char	pieceletter;

	i = 0;
	pieceletter = 'A';
	while (i < size)
	{
		if (pieceletter == 'A')
		{
			beginning = makepiece(buf + i, pieceletter);
			current = beginning;
		}
		else
		{
			current->next = makepiece(buf + i, pieceletter);
			current = current->next;
		}
		pieceletter++;
		i += 21;
	}
	current->next = NULL;
	return (beginning);
}

/*
** Control function for all file parsing functions
** Opens & reads file into a buffer of size 545 (max file size + 1)
** Rejects a file if too small or too large
** Calls valid() to check validity of file
** returns list of piece structs
*/

t_piece		*parser(char *filename)
{
	char	buf[545];
	int		fd;
	int		bytecount;

	fd = open(filename, O_RDONLY);
	bytecount = read(fd, buf, 545);
	close(fd);
	if (bytecount > 544 || bytecount < 19)
		return (NULL);
	buf[bytecount] = '\0';
	if (!valid(buf, bytecount))
		return (NULL);
	return (makelist(buf, bytecount));
}

//==============================================================================
int		round_up_sq_rt(int num)
{
	int	map_size;

	map_size = 2;
	while (map_size * map_size < num)
		map_size++;
	return (map_size);
}

/*
** Use malloc to make space for the map.
** Use malloc to make space for 2D map array.
** then you need to malloc out the rows of the map based on map_size as well,
** plus newline with strnew(). Set it all to .
*/

t_map	*new_map(int map_size)
{
	t_map	*map;
	int		i;

	map = (t_map *)ft_memalloc(sizeof(t_map));
	map->array = (char**)ft_memalloc(sizeof(char*) * map_size);
	i = 0;
	while (i < map_size)
	{
		map->array[i] = ft_strnew(map_size);
		ft_memset(map->array[i], '.', map_size);
		i++;
	}
	return (map);
}

size_t	count_pieces(t_piece *piecelist)
{
	size_t	count;

	count = 0;
	while (piecelist)
	{
		piecelist = piecelist->next;
		count++;
	}
	return (count);
}

/*
** Print the map one row at a time followed by newline.
*/

void	print_map(t_map *map, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		ft_putstr(map->array[i]);
		ft_putchar('\n');
		i++;
	}
}

void	free_map(t_map *map, int map_size)
{
	int i;

	i = 0;
	while (i < map_size)
	{
		ft_memdel((void **)&(map->array[i]));
		i++;
	}
	ft_memdel((void **)&(map->array));
	ft_memdel((void **)&map);
}

//==============================================================================

int		main(int argc, char **argv)
{
	t_piece	*piecelist;

	if (argc != 2)
	{
		ft_putstr("usage: ./fillit source_file\n");
		return (1);
	}
	if ((piecelist = parser(argv[1])) == NULL)
	{
		ft_putstr("error\n");
		return (1);
	}
	solve(piecelist);
	free_piecelist(piecelist);
	return (0);
}
