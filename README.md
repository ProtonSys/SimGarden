# SimGarden

A C++ garden simulator that allows you to manage plants, water them, and watch them grow over time.

## Features

- **Plant Management**: Add plants with custom names and species
- **Watering System**: Water individual plants or all plants at once
- **Growth Simulation**: Simulate the passage of time and watch your plants grow
- **Health Monitoring**: Track plant health, water levels, and survival
- **Interactive CLI**: User-friendly command-line interface

## Building the Project

### Prerequisites

- CMake 3.10 or higher
- C++ compiler with C++11 support (g++, clang++, MSVC)

### Build Instructions

```bash
# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build the project
cmake --build .
```

## Running the Simulator

After building, run the executable:

```bash
./simgarden
```

## How to Play

1. **Create your garden**: Enter a name for your garden when prompted
2. **Add plants**: Choose option 1 and enter plant name and species
3. **Water plants**: Keep your plants hydrated (option 2 or 3)
4. **Simulate time**: Progress time to see your plants grow (option 4)
5. **Check status**: View all your plants' health and stats (option 5)

## Game Mechanics

- Plants start at 5 cm tall with 50% water level and 100% health
- Water evaporates by 5% each day
- Plants grow when water level is above 20%
- Health deteriorates if water level drops below 30%
- Plants die if health reaches 0%

## Project Structure

```
SimGarden/
├── CMakeLists.txt       # Build configuration
├── README.md            # This file
├── include/             # Header files
│   ├── Plant.h         # Plant class declaration
│   └── Garden.h        # Garden class declaration
└── src/                # Source files
    ├── main.cpp        # Main application
    ├── Plant.cpp       # Plant implementation
    └── Garden.cpp      # Garden implementation
```

## License

TP_POO
