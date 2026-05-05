# TerrariaClone

A 2D tile-based platformer built with C++ and SFML 3, inspired by Terraria.

## Features

- **Tile-based world** — 2D grid world with 40×40px tiles, loaded from `.txt` level files
- **Multiple tile types** — dirt (brown), stone (gray), empty space
- **Chunk system** — world is split into 32×50 tile chunks stored in a `std::map`
- **Physics** — gravity, velocity, jumping with realistic feel
- **AABB collision** — per-tile collision detection between player and world
- **Player movement** — walk left/right, jump, with smooth stop on key release
- **Sprite animation** — spritesheet-based frame animation with row/column indexing
- **Sprite flipping** — player sprite mirrors horizontally based on movement direction
- **Game loop** — fixed framerate (60 FPS) with delta time for smooth updates

## Controls

| Key | Action |
|-----|--------|
| `A` | Move left |
| `D` | Move right |
| `Space` | Jump |
| `Escape` | Quit |

## Project Structure

```
SFMLTutorials/
├── main.cpp            — entry point
├── GameWorld.h/cpp     — main game loop (ProcessEvents / Update / Render)
├── Player.h/cpp        — player entity
├── Physics.h/cpp       — gravity, velocity, jump
├── Collider.h/cpp      — AABB collision
├── Animation.h/cpp     — spritesheet animation
├── WorldRenderer.h/cpp — chunk rendering
├── parser.h/cpp        — level loading from .txt
└── level1.txt          — level map (0=empty, 1=dirt, 2=stone)
```

## Built With

- [SFML 3](https://www.sfml-dev.org/) — graphics, window, input
- C++17
- Visual Studio 2022
