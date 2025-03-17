# 🎮 Cube3D - A Raycasting Game

A 3D raycasting game inspired by Wolfenstein 3D, featuring dynamic lighting, textures, and interactive elements. Built using the MinilibX graphics library.

## 🎥 Gameplay Showcase
[![Cube3D Gameplay](https://img.youtube.com/vi/HV48BXeT3Z0/maxresdefault.jpg)](https://youtu.be/HV48BXeT3Z0)

Watch the full gameplay video on YouTube: [Cube3D Gameplay](https://youtu.be/YtjDYRPUCvg)

## 🌟 Features

### Core Gameplay
- First-person 3D perspective using raycasting
- Smooth player movement and rotation
- Collision detection with walls
- Dynamic wall textures
- Dark mode toggle for enhanced atmosphere

### Interactive Elements
- **Doors**: Open and close doors using the 'E' key
- **Enemies**: Dynamic enemy with animations
- **Combat System**:
  - Weapons with unique animations
  - Shooting mechanics with recoil effects
  - Reloading system
  - Screen shake effects for immersion
- **Scope System**: Toggle scope view with right mouse button
- **Movement Options**:
  - Walking (default)
  - Sprinting (hold SHIFT)

### Visual Effects
- Dynamic lighting system
- Smooth animations for all interactive elements
- Screen shake during shooting

### Additional Features
- Minimap for navigation
- Enemy location in minimap with realtime position
- Sound effects for door and shooting
- Multiple map support
- Error handling and validation

## 🛠️ Requirements

- Linux operating system
- GCC compiler
- Make
- MinilibX library
- X11 development libraries

## 📦 Installation

1. Clone the repository:
```bash
git clone https://github.com/radouane-tamouss/Cube3D.git
cd Cube3D
```

2. Compile the game:
```bash
make        # For the basic version
make bonus  # For the full version with all features
```

## 🎯 Usage

### Basic Version
```bash
./cub3D ll.cub
```

### Bonus Version
```bash
./cub3D_bonus bonus/ll.cub
```

### Controls

#### Movement
- `W` - Move forward
- `S` - Move backward
- `A` - Strafe left
- `D` - Strafe right
- `←` / `→` - Rotate left/right
- `SHIFT` - Sprint

#### Combat
- `Left Mouse Button` - Shoot
- `Right Mouse Button` - Toggle scope
- `R` - Reload weapon
- `E` - Interact with doors

#### Other
- `ESC` - Exit game
- `space` - Toggle dark mode
- `Mouse Movement` - Look around

## 👥 Authors

- [Radouane](https://github.com/radouane-tamouss)
- [Erabareta](https://github.com/erabareta)

## 🗺️ Map Format

The game uses `.cub` files for maps. Here's an example format:

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 225,30,0

1111111
1000001
1000001
1000001
1000001
1000001
1111111
```

- `NO`, `SO`, `WE`, `EA`: Path to wall textures
- `F`: Floor color (RGB)
- `C`: Ceiling color (RGB)
- `1`: Wall
- `0`: Empty space
- `N`, `S`, `E`, `W`: Player starting position and direction
- `D`: Door
- `2`: Enemy

## 🎨 Customization

### Textures
Place your custom textures in the `textures/` directory. Supported formats:
- XPM files for walls and sprites
- Custom color schemes for floor and ceiling

### Maps
Create your own maps using the `.cub` format and place them in the `maps/` directory.

