### CUB3D

My first ray casting 2.5D wolfestein-like maze.

### USAGE

To compile and run the game:

```bash
make
./cub3d
```

### IDEAS

From the solong code, an example of map validation:

```c
///////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////
static int	is_bounded_by_walls(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->game.raw_cols)
	{
		if (vars->game.clone[0][i] != '1'
			|| vars->game.clone[vars->game.raw_rows - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < vars->game.raw_rows)
	{
		if (vars->game.clone[i][0] != '1'
			|| vars->game.clone[i][vars->game.raw_cols - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

///////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////
static int	is_well_formed(t_vars *vars)
{
	int	i;
	int	j;
	int	count_p;
	int	count_e;

	i = 0;
	count_e = 0;
	count_p = 0;
	while (i < vars->game.raw_rows)
	{
		j = 0;
		while (j < vars->game.raw_cols)
		{
			if (vars->game.clone[i][j] == 'P')
				count_p++;
			else if (vars->game.clone[i][j] == 'E')
				count_e++;
			j++;
		}
		i++;
	}
	return (count_e == 1 && count_p == 1);
}

///////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////
static int	flood_fill_map(t_vars *vars, int r, int c, int *exit_reachable)
{
	char	tile;
	int		reached;

	reached = 0;
	if (r < 0 || r >= vars->game.raw_rows || c < 0 || c >= vars->game.raw_cols)
		return (0);
	tile = vars->game.clone[r][c];
	if (tile == '1' || tile == 'F' || tile == 'v')
		return (0);
	if (tile == 'E')
	{
		*exit_reachable = 1;
		return (0);
	}
	if (tile == 'C')
		reached = 1;
	vars->game.clone[r][c] = 'v';
	reached += flood_fill_map(vars, r + 1, c, exit_reachable);
	reached += flood_fill_map(vars, r - 1, c, exit_reachable);
	reached += flood_fill_map(vars, r, c + 1, exit_reachable);
	reached += flood_fill_map(vars, r, c - 1, exit_reachable);
	return (reached);
}

static int	contain_valid_chars(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->game.raw_rows)
	{
		j = 0;
		while (j < vars->game.raw_cols)
		{
			if (char_to_tile(vars->game.clone[i][j]) < 0)
			{
				ft_putstr_fd("Error\nInvalid char '", 2);
				ft_putchar_fd(vars->game.clone[i][j], 2);
				ft_putstr_fd("' found. Invalid map provided.\n", 2);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

///////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////
int	is_valid_map(t_vars *vars)
{
	int	exit_reachable;
	int	is_bounded;
	int	reached;
	int	well_formed;

	if (!contain_valid_chars(vars))
		return (0);
	well_formed = is_well_formed(vars);
	is_bounded = is_bounded_by_walls(vars);
	exit_reachable = 0;
	reached = flood_fill_map(vars, vars->game.position.y / SIZE,
			vars->game.position.x / SIZE, &exit_reachable);
	if (!well_formed)
		ft_putstr_fd("Error\nPlayer or exit are not unique. Invalid map.\n", 2);
	else if (vars->game.consumables == 0)
		ft_putstr_fd("Error\nNo food found. Invalid map.\n", 2);
	else if (!exit_reachable)
		ft_putstr_fd("Error\nThe player cannot exit. Invalid map.\n", 2);
	else if (reached != vars->game.consumables)
		ft_putstr_fd("Error\nFood is not accesible. Invalid map.\n", 2);
	return (vars->game.consumables != 0 && well_formed && exit_reachable
		&& is_bounded && reached == vars->game.consumables);
}
```