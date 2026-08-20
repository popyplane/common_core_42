# So_long

A small 2D top-down game: move a player across a map, collect all items, then reach the exit. Map layout, validity checks (rectangular shape, walled border, exactly one player, one exit, at least one collectible, exit and collectibles reachable via flood fill) and win/move-counting logic are hand-written for this 42 School project.

## Status

The game logic itself (map parsing, validation, flood-fill reachability check) was already correct and untouched here. What needed work was the graphics layer: this project originally used `minilibx-linux`, an X11-based library that only runs on Linux and was never checked into this repo, so it couldn't be built or run at all on this machine. Migrated to [MLX42](https://github.com/codam-coding-college/MLX42) (AI-assisted, Claude), the same modern, cross-platform library already used for this repo's `cub3d`:

- **Textures converted from XPM to PNG.** MLX42 doesn't load the classic X11 XPM format the original assets were in; converted all five tile sprites with ImageMagick to 32-bit RGBA PNGs, which `mlx_load_png` reads directly.
- **Display model rewritten around MLX42's persistent images.** The original code re-blitted every tile to the window on every frame via a loop hook, since old-style mlx used a manually swapped framebuffer. MLX42 instead keeps images resident on screen as "instances" once attached, so the redraw-every-frame approach doesn't apply, walls and floor tiles are built once at startup, the player is a single instance whose position is updated directly on movement, and collectibles are individual instances that get disabled (not redrawn) once picked up. This is an adaptation to the new library's model, not a bug fix, the visual result and game rules are unchanged.
- **Input handling ported from X11 keysyms to MLX42's key hook** (`MLX_KEY_UP`/`DOWN`/`LEFT`/`RIGHT`/`ESCAPE` instead of `XK_*`), still gated on key release so holding a direction doesn't spam moves via OS key-repeat, matching the original's behavior.
- **The score counter** (top-left "moves : N" text) now uses MLX42's built-in `mlx_put_string`, replacing the old library's `mlx_string_put` plus a manual pixel-clear loop that doesn't have an equivalent in MLX42's image-based model, the old text image is simply deleted and replaced each time the move count changes.

## Verified

- All three shipped maps (`basic.ber`, `basic2.ber`, `basic5.ber`) build and launch cleanly: textures load without error, window opens, and the process stays stable and responsive with no crash.
- All nine invalid maps under `maps/err/` (too many/few players, exits or collectibles, non-rectangular map, missing border walls, unreachable exit, unknown characters) still print the correct validation error and exit, this logic wasn't touched by the migration.
- Movement, collection, and win-condition code was traced line by line against the original (verified-working) logic to confirm the port preserves it exactly. Full interactive gameplay wasn't automatable in this environment (no permission to simulate keystrokes into a native window here), so this is code-level verification rather than a live playthrough.

## Build & run

```bash
make
./so_long <map_name>          # map file must live in maps/, pass just its filename
```
