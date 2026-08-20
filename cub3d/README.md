# cub3d

A raycasting engine written in C, in the style of the original Wolfenstein 3D: a 2D map file turned into a real-time first-person 3D view. 42 School project.

## Status

This repo started as 42 coursework and got the map parsing and a 2D top-down renderer built. The raycasting engine itself, player movement, and a handful of underlying bugs were completed with AI assistance (Claude) to finish the project for portfolio purposes. Documented here rather than left unstated:

- The DDA raycasting algorithm, camera/player state, and movement/collision (`src/raycast.c`, `src/player.c`) are the completed part.
- Walls render as solid, direction-shaded colors rather than image textures: the map format parses texture file paths, but the sample map only ships placeholder paths with no actual image files, so texture image-mapping wasn't in scope here.
- Fixed along the way: a dangling-pointer bug in texture path parsing (raw pointers into a line buffer that was immediately freed after), an off-by-one in the map height calculation, a type mismatch between `t_img` and `t_img *` that meant the original code never actually compiled, and a hook callback receiving the wrong pointer type.
- The project originally targeted a classic X11/Cocoa minilibx fork, whose render loop called raw `glFlush()` after drawing instead of actually presenting the frame to the compositor, meaning every frame rendered correctly internally but never reached the screen, a persistent black window. After patching that and still hitting further platform-specific rendering issues, the graphics backend was switched entirely to [MLX42](https://github.com/codam-coding-college/MLX42), an actively-maintained, cross-platform replacement built by Codam specifically to avoid this class of bug. `src/main.c`, `src/hooks.c`, `src/img.c`, and `src/render.c` were adapted to its API (a cleaner one: single unified key hook with press/release actions, a built-in close-window hook, direct `mlx_put_pixel` instead of manual framebuffer byte-packing).

## Architecture

For each vertical strip of the screen, a ray is cast from the player's position using the DDA (Digital Differential Analysis) algorithm: it steps through the map grid one cell at a time, always advancing into whichever neighboring cell is closer, until it hits a wall. The perpendicular distance to that wall determines how tall the wall slice is drawn, correcting for the fisheye distortion a naive Euclidean distance would produce.

```
player + direction vector + camera plane
  -> per-column ray direction (camera_x sweeps the plane across the FOV)
  -> DDA step through the grid, tracking whether the hit was N/S or E/W facing
  -> perpendicular distance -> wall slice height, shaded by distance and orientation
```

Movement (WASD to move/strafe, arrow keys to rotate) is collision-checked against the map grid on each axis independently, so sliding along a wall doesn't get stuck. Closing the window (via `Esc` or the window's close button) cleanly stops the program.

## Maps

`maps/` has a few to try, from a minimal sanity check to something that actually exercises the renderer:

| Map | What it is |
| --- | --- |
| `simple.cub` | A single small enclosed room. Minimal case, good first check that rendering works at all. |
| `rooms.cub` | Two rooms joined by a corridor. Walking down the corridor and turning into the second room is a decent test of perspective and collision at a turn. |
| `arena.cub` | A large open room with a 3x3 pillar in the middle. Tests occlusion and walking around an obstacle from every angle. |
| `test.cub` | The original coursework map, kept for history. Irregular edges, not fully enclosed. |

## Build & run

Requires `cmake` and `glfw` (MLX42's dependencies): `brew install cmake glfw` on macOS.

```bash
make
./cub3d maps/rooms.cub
```

Controls: `W`/`A`/`S`/`D` to move, `←`/`→` to rotate, `Esc` to quit.
