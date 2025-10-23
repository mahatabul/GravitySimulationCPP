# Gravity Orbit Simulator

The Gravity Orbit Simulator is a C++ application that visualizes particles orbiting a central gravity source, simulating gravitational dynamics. Built using the SFML (Simple and Fast Multimedia Library), the simulator allows users to interactively adjust the gravity strength and the number of particles through a graphical user interface.

![SCreenShot](ss.png)

## Features
- **Particle Simulation**: Particles orbit a central gravity source based on Newtonian gravitational mechanics.
- **Interactive UI**: A panel in the top-left corner allows users to modify:
  - **Gravity Strength**: Adjust the gravitational force applied to particles.
  - **Number of Particles**: Change the number of orbiting particles.
- **Real-time Input**: Click on input fields, type values, and press Enter to apply changes, updating the simulation dynamically.
- **Cross-Platform Font Support**: Uses common system fonts (e.g., Arial, DejaVu Sans, Helvetica) for text rendering.
- **Customizable Parameters**: Initial particle positions and velocities are calculated to create stable orbits with slight randomization for variety.
- **Smooth Graphics**: Runs at 60 FPS with a resolution of 1920x1080.

## Prerequisites
To compile and run the simulator, you need:
- **C++ Compiler**: A C++17 compatible compiler (e.g., GCC, MSVC, Clang).
- **SFML Library**: Version 2.5 or later. Install SFML for your operating system:
  - **Windows**: Download from [SFML website](https://www.sfml-dev.org/download.php) or use a package manager like vcpkg.
  - **Linux**: Install via package manager (e.g., `sudo apt-get install libsfml-dev` on Ubuntu).
  - **macOS**: Install via Homebrew (`brew install sfml`) or download from the SFML website.
- **System Fonts**: The program attempts to load common system fonts (Arial, DejaVu Sans, Liberation Sans, Helvetica, or Tahoma). Ensure at least one is available on your system:
  - Windows: `C:/Windows/Fonts/arial.ttf` or `C:/Windows/Fonts/tahoma.ttf`
  - macOS: `/Library/Fonts/Arial.ttf` or `/System/Library/Fonts/Helvetica.ttc`
  - Linux: `/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf` or `/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf`

## Installation
1. **Install SFML**:
   - Follow the instructions for your platform on the [SFML website](https://www.sfml-dev.org/tutorials/2.5/#getting-started).
   - Ensure SFML libraries are linked correctly in your build system.
2. **Clone or Download the Code**:
   - Copy the provided project.
3. **Set Up Your Build System**:
   - **CMake Example**:
     ```cmake
     cmake_minimum_required(VERSION 3.10)
     project(GravitySimulator)
     set(CMAKE_CXX_STANDARD 17)
     find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
     add_executable(GravitySimulator main.cpp)
     target_link_libraries(GravitySimulator sfml-graphics sfml-window sfml-system)
     ```
   - Run `cmake .` and `make` to build the project.
   - **Manual Compilation** (example for GCC):
     ```bash
     g++ -c start.cpp -I/path/to/sfml/include
     g++ main.o -o GravitySimulator -L/path/to/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system
     ```
4. **Verify System Fonts**:
   - Ensure at least one of the fonts listed in the code is available on your system. If not, modify the font paths in `main.cpp` to match a font available on your system.

## Usage
1. **Run the Program**:
   - Execute the compiled binary (e.g., `./start` on Linux/macOS or `start.exe` on Windows).
   - The simulation starts with a default gravity strength of 80,000 and 20 particles orbiting a central red gravity source.
2. **Interact with the UI**:
   - A panel appears in the top-left corner with fields for "Gravity Strength" and "Num Particles".
   - **Click** on the gravity or particle input field to edit it (highlighted with a cyan outline).
   - **Type** a new value:
     - Gravity strength accepts decimal numbers (e.g., `80000.0`).
     - Number of particles accepts integers (e.g., `20`).
   - Press **Enter** to apply changes, which reinitializes the simulation with the new values.
3. **Exit the Program**:
   - Click the window's close button or press any key to exit.

## Code Structure
- **Gravity_Source**: Represents the central gravity source, rendered as a red circle.
- **Particle**: Represents orbiting particles, rendered as small white circles, updated based on gravitational acceleration.
- **createParticles**: Initializes particles in circular orbits with randomized radii and calculated velocities for stability.
- **Main Loop**:
  - Handles SFML events for window management and user input.
  - Updates particle positions based on gravitational forces.
  - Renders the gravity source, particles, and UI elements (panel, labels, input fields).

## Notes
- **Font Loading**: The program attempts to load common system fonts. If none are found, it exits with an error. You may need to adjust font paths in `main.cpp` to match your system's font locations.
- **Input Validation**: Invalid inputs (e.g., non-numeric values) are ignored when pressing Enter, and an error message is printed to the console.
- **Performance**: The simulation runs smoothly with up to hundreds of particles, but very large particle counts may impact performance.
- **Customization**: You can modify initial parameters (e.g., `gravity`, `numParticles`, `centerX`, `centerY`) in `main.cpp` to change the default simulation settings.

## Troubleshooting
- **Font Not Found**: If the program exits with "No system font found!", verify that one of the specified fonts exists on your system or update the font paths in `main.cpp`.
- **SFML Errors**: Ensure SFML is correctly installed and linked. Check the SFML documentation for platform-specific setup.
- **UI Issues**: Ensure your mouse clicks are within the input boxes (gray rectangles) to activate editing.

## License
This project is provided as-is for educational purposes. Feel free to modify and distribute it under your own terms.

## Acknowledgments
- Built with [SFML](https://www.sfml-dev.org/), a simple and fast multimedia library for C++.
- Inspired by gravitational orbit simulations and interactive graphics applications.
