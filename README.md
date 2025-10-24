<div align="center">

# ```Wolfepstein```

**A real-time 3D graphics engine inspired by the classic Wolfenstein 3D, built from the ground up using raycasting.**

[![Made with C](https://img.shields.io/badge/Made%20with-C-blue.svg?style=for-the-badge&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Graphics with MiniLibX](https://img.shields.io/badge/Graphics-MiniLibX-yellow.svg?style=for-the-badge)](https://github.com/42Paris/minilibx-linux)

</div>

<div align="center">

## ```Wolfenstein : ``` original game

![Alt text](https://media3.giphy.com/media/v1.Y2lkPTc5MGI3NjExaHAyOTYxZ3pyZ25ud3AyNnVtdzdlY25kNTZvOGVkczRpaTNmZ2JreCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/3o85xyFuIzQQ2NmIBW/giphy.gif)

</div>

---

## About The Project

**Wolfepstein** is a 3D graphics project that implements a raycasting engine to render a 3D first-person perspective from a 2D map, similar to the groundbreaking game **Wolfenstein 3D**. This project was built to explore the core principles of 3D graphics, real-time rendering, and low-level engine development.

---

## Key Features

- **Real-time 3D Raycasting**: Renders a 3D world using the Digital Differential Analysis (DDA) algorithm.
- **Textured Walls**: Applies XPM textures to walls based on their orientation (North, South, East, West).
- **Smooth Movement & Collision**: Navigate the world with WASD controls and solid wall collision detection.
- **360° Camera Rotation**: Look around freely with smooth camera rotation.
- **Customizable Environment**: Easily change floor and ceiling colors via the map file.
- **Dynamic Map System**: Parses game environments and configurations from `.cub` files.

---

## Built With

This project was built using the following technologies:

- **[C](https://en.wikipedia.org/wiki/C_(programming_language))**: For core logic and performance-critical code.
- **[MiniLibX](https://github.com/42Paris/minilibx-linux)**: A simple graphics library used for window management and pixel rendering.
- **[GCC](https://gcc.gnu.org/) & [Make](https://www.gnu.org/software/make/)**: For compiling the project on Linux/macOS.

---

## Follow these steps to get a local copy up and running.

### Prerequisites

You'll need the following tools installed on your system:
- **GCC Compiler**
- **Make**
- **X11** (for Linux) or **AppKit** (for macOS)
- **MiniLibX**: Ensure the MiniLibX library is correctly set up in your environment.

### Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/your_username/Wolfepstein.git
   cd Wolfepstein
   ```

2. Compile the project:
   ```sh
   make
   ```
   This will create the `cub3D` executable.

---

## Usage

To run the game, provide a map file as an argument:

```sh
./cub3D maps/example_map.cub
```

---

## Controls

| Key | Action            |
|-----|-------------------|
| `W` | Move Forward      |
| `S` | Move Backward     |
| `A` | Strafe Left       |
| `D` | Strafe Right      |
| `←` | Rotate Left       |
| `→` | Rotate Right      |
| `ESC`| Exit Game         |

---

## Map File Format

The game uses `.cub` files to define the map and its properties. The file format is as follows:

- **Textures**: Paths to the `.xpm` texture files for each cardinal direction.
  ```
  NO ./textures/north.xpm
  SO ./textures/south.xpm
  WE ./textures/west.xpm
  EA ./textures/east.xpm
  ```

- **Colors**: RGB values for the floor and ceiling.
  ```
  F 220,100,0
  C 225,30,0
  ```

- **Map Grid**: A 2D grid representing the level layout.
  - `0`: Empty space
  - `1`: Wall
  - `N`, `S`, `E`, `W`: Player start position and initial orientation.

  Example Map:
  ```
  1111111111
  1001000001
  10N0000001
  1111111111
  ```

---

## Technical Implementation

- **Raycasting**: Implements the **DDA (Digital Differential Analysis)** algorithm for efficient wall detection and distance calculation.
- **Texture Mapping**: Correctly samples and scales textures based on the ray's intersection point and wall orientation.
- **Rendering**: Renders the scene by drawing textured vertical slices for each ray cast from the player's field of view (FOV).
- **Player Physics**: Handles movement and grid-based collision to prevent walking through walls.
- **Graphics**: Uses **MiniLibX** for window creation, image handling, and pixel-by-pixel rendering.
- **Field of View (FOV)**: Set to 66 degrees for a classic, immersive feel.

---

## Project Structure

```
cub3D/
├── includes/
│   └── cub3D.h
├── lib/
│   └── minilibx/      # MiniLibX source or library
├── maps/
│   └── example.cub
├── src/
│   ├── initialization/
│   │   ├── init_player.c
│   │   ├── init_mapgame.c
│   │   └── creating_win_tex.c
│   ├── movement/
│   │   └── moving.c
│   ├── raycasting/
│   │   ├── raycasting.c
│   │   └── ...
│   ├── rendering/
│   │   ├── render_walls.c
│   │   └── ...
│   └── main.c
├── textures/
│   ├── north.xpm
│   ├── south.xpm
│   ├── east.xpm
│   └── west.xpm
└── Makefile
```
