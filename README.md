*This project has been created as part of the 42 curriculum by `jomarti3` and `guigonza`.*

![Demo de Cub3D](assets/Cub3D.gif)

## Description

The goal is to render a ray casting 2.5D wolfestein-like maze game in `c` using the `minilibx`.

The project includes:

- animations
- open / close doors
- playable with keyboard and mouse
- minimap

Code summary:

| File type | Lines of Code |
|----------|--------------:|
| `.c`     |          2195 |
| `.h`     |           323 |
| `.sh`     |           125 |
| Makefile |            82 |
| **TOTAL**|        **2725** |

## Instructions

To compile and run the game:

```bash
make
./cub3d maps/level[1-9].cub
```

with an existing *.cub file.

## Gameplay

The game speed can be adjusted using:

```c
# define MOVE_SPEED 0.1493
# define ROT_SPEED  0.0689
# define FPS 24
# define MOUSE_SENS 0.0021
```

The default configuration works nice for the 42 computers at 03/09/2026. 

To toggle mouse usage on, press `m`. (It works properly on linux, but fails in WSL)

To open the doors, you may press `e`. The game consists on opening all the doors.

## Resources

- [minilibx](https://harm-smits.github.io/42docs/libs/minilibx)

- We used [chatgpt](https://chatgpt.com) to get an overview of the classical algorithms used typically. The game is created using the Ray Casting and DDA algorithms, based on the projective geometry.
