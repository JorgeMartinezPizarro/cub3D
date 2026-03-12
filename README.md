*This project has been created as part of the 42 curriculum by `jomarti3` and `guigonza`.*

## Description

The goal is to render a ray casting 2.5D wolfestein-like maze game in `c` using the `minilibx`.

The project includes:

- animations
- open / close doors
- playable with keyboard and mouse
- minimap

## Instructions

To compile and run the game:

```bash
make
./cub3d maps/map_name.cub
```

with an existing *.cub file.

### Advanced

The game speed can be adjusted using:

```c
# define MOVE_SPEED 0.07
# define ROT_SPEED  0.051
# define MOUSE_SENS 0.002
# define FPS 30
```

The default configuration works nice for the 42 computers at 12/03/2026. 

## Resources

- [minilibx](https://harm-smits.github.io/42docs/libs/minilibx)

- We used [chatgpt](https://chatgpt.com) to get an overview of the classical algorithms used typically. The game is created using the Ray Casting and DDA algorithms, based on the projective geometry.
