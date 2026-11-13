# Try of the Leaf

A 2D action game built with **C++ and SFML**.

Try of the Leaf is a personal game development project focused on implementing gameplay systems and organizing a game using a modular architecture.

## Features

- **State-based architecture** — separate states for gameplay, pause menu and settings.
- **State machine** — manages transitions between different game states.
- **Asset manager** — centralized loading and access to textures, fonts and sounds.
- **Animation system** — handles character animations based on the current player state.
- **Player combat** — melee attacks and projectile-based attacks.
- **Enemy AI** — enemies pursue the player and spawn around the playable area.
- **Collision detection** — handles interactions between the player, enemies, sword and projectiles.
- **Settings system** — includes audio volume management and character skin selection.
- **Score system** — tracks defeated enemies.
<img width="857" height="629" alt="Screenshot 2026-04-16 215106" src="https://github.com/user-attachments/assets/a8722290-4e2c-4425-8a44-31cb195f08f6" />

## Technologies

- C++
- SFML (Simple and Fast Multimedia Library)
- Object-oriented programming

## Architecture

The project is organized into several components, each responsible for a particular part of the game.

| Component | Responsibility |
|---|---|
| `Game_Engine` | Main game initialization and execution |
| `StateMachine` | Manages active game states |
| `Gamestate` | Main gameplay logic |
| `PauseState` | Pause menu |
| `SettingsState` | Game settings |
| `AssetManager` | Resource loading and management |
| `InputManager` | Input handling |
| `Animation` | Character animation management |
| `Hero` | Player behaviour and combat |

## Building

The repository includes a Visual Studio solution and project files.

1. Clone the repository:
   ```bash
   git clone https://github.com/pekkaone/Tryoftheleaf-Game.git
   ```
2. Open `Try of the leaf.sln` in Visual Studio.
3. Build the project using the available configuration.

<img width="860" height="623" alt="Screenshot 2026-04-16 215028" src="https://github.com/user-attachments/assets/6472a1f4-bc76-4328-9961-425c2b97ba14" />

**Requirements:**
- Visual Studio with C++ development tools.
- SFML.

Make sure the SFML configuration matches your compiler and build configuration.

## Project Status

This is an ongoing personal project. It serves as a practical exploration of C++ game development, game architecture and SFML.

## Author

Developed by [pekkaone](https://github.com/pekkaone).

<img width="860" height="625" alt="Screenshot 2026-04-16 215059" src="https://github.com/user-attachments/assets/0ab587ff-68ac-4584-b6dc-cda29c77e344" />

