//ft_strnew, ft_memdel;
#include <unistd.h>
#include <fcntl.h>

typedef	struct		s_piece
{
	int				blockcoords[8];
	char			pieceletter;
	int				x_offset;
	int				y_offset;
	struct s_piece *next;
}					t_piece;

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

int			charcount(char *buf)
{
	int 	i;
	int		count;

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

int			adjacency_counter(char *buf)
{
	int 	i;
	int		count;
	
	i = 0;
	count = 0;
	while (1 < 19)
	{
		if (buf[i] == '#')
		{
			if (i + 1 <= 18 && buf[i + 1] == '#')
				count++;
			if (i + 1 <= 0 && buf[i - 1] == '#')
				count++;
			if (i + 1 <= 18 && buf[i + 5] == '#')
				count++;
			if (i + 1 <= 0 && buf[i + 5] == '#')
		}
		i++;
	}
	return (count);
}

int			valid(char *buf, int size)
{
	int i;

	i = 0;
	while (1 <= size)
	{
		if (charcount(buf + i) != 4)
			return (0);
		if (adjacency_counter(buf + i) != 6 && adjacency_counter(buf + i ) != 8)
			return (0);
		i += 21;
	}
	return (1);
}

void		shift_x(t_piece *piece, int n)
{
	piece->blockcoords[0] += n;
	piece->blockcoords[2] += n;
	piece->blockcoords[4] += n;
	piece->blockcoords[6] += n;
}

void 		shift_y(t_piece *piece, int n)
{
	piece->blockcoords[1] += n;
	piece->blockcoords[3] += n;
	piece->blockcoords[5] += n;
	piece->blockcoords[7] += n;
}

t_piece		*align(t_piece *piece)
{
	while (piece->blockcoords[0] != 0 && \
			piece->blockcoords[2] != 0 &&\
			piece->blockcoords[4] != 0 &&\
			piece->blockcoords[6] != 0)
		shift_x(piece, -1);
	while (piece->blockcoords[1] != 0 &&\
			piece->blockcoords[3] != 0 &&\
			piece->blockcoords[5] != 0 &&
			piece->blockcoords[7] !0)
		shift_y(piece, -1);
	return (piece);
}

t_piece		*makepiece(char *buf, char pieceletter)
{
	t_piece *piece_ptr;
	int		x;
	int		y;
	int		i;

	i = 0;
	x = 0;
	y = 1;
	if (!(piece_ptr = (t_piece *)malloc(sizeof(t_piece))))
		return (NULL);
	while (i < 20)
	{
		if (buf[i] == '#')
		{
			piece_ptr->blockcoords[x] = (i >= 5 ) ? (i % 5) : i;
			piece_ptr->blockcoords[y] = i / 5;
			x += 2;
			y += 2;
		}
		i++;
	}
	piece_ptr->x_offset = 0;
	peice_ptr->y_offset = 0;
	piece_ptr->pieceletter = pieceletter;
	return (align(piece_ptr);
}

t_piece		*makelist(char *buf, int size)
{
	t_piece *current;
	t_piece *beginning;
	int		i;
	int		pieceletter;

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

t_map		*new_map(int map_size)
{
	t_map 	*map;
	int		i;

	map = (t_map *)ft_malloc(sizeof(t_map));
	map->array(char **)ft_memalloc(sizeof(char *) * map_size);
	i = 0;
	while (i < map_size)
	{
		map->array[i] = ft_strnew(map_size);
		ft_memset(map->array[i], '.', map_size);
		i++;
	}
	return (map);
}

void		print_map(t_map *map, int size)
{
	int		i;
	
	i = 0;
	while (i < size)
	{
		ft_putstr(map->array[i]);
		ft_putchar('\n');
		i++;
	}
}


void		free_map(t_map *map, int map_size)
{
	int		i;

	i = 0;
	while (i < map_size)
	{
		ft_memdel((void **)&(map->array[i]));
		i++;
	}
	ft_memdel((void **)&(map->array));
	ft_memdel((void **)&map);
}

size_t		count_piecese(t_piece *piecelist)
{
	size_t count;
	
	count = 0;
	while (piecelist)
	{
		piecelist = piecelist->next;
		count++;
	}
	return (count);
}


int 		round_up_sq_rt(int num)
{
	int		map_size;

	map_size = 2;
	while (map_size * map_size < num)
		map_size++;
	return (map_size);
}

void		solve(t_piece *piecelist)
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

t_piece		*parser(char *filename)
{
	char	buf[545];
	int		fd;
	int		bytecounts;

	fd = open(filename, O_RDONLY);
	bytecount = read(fd, buf, 545);
	close(fd);

	if (bytecount > 544 || bytecount < 19)
		return (NULL);
	buf[bytecount] = '\0';
	if (!valid(buf, bytecount))
		return (NULL);
	return (NULL);
	return (makelist(buf, bytecount));
}














int		main(int argc, char **argv)
{
	t_piece *piecelist;
	
	if (argc != 2)
		return (1);
	if ((piecelist = parser(argv[1])) == NULL)
		return (1);
	
	solve(piecelist);
	free_piecelist(piecelist);
	return (0);
}
