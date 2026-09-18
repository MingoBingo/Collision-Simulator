# 2D Collision Simulator

A lightweight 2D physics simulation written in **C** using **Raylib**. The project demonstrates rigid body interactions between circular particles, featuring real-time collision detection, impulse resolution, position correction, and wall boundary constraints.

---

## Features

* **Elastic Circle Collisions:** Momentum and energy conservation using impulse-based normal resolution.
* **Overlap Separation:** Positional correction to prevent circles from sticking or sinking into each other.
* **Boundary Confinement:** Rebound mechanics against window edges with energy damping.
* **Custom Physics Parameters:** Adjustable mass, radius, restitution (bounciness), and gravity.
* **Minimal Dependencies:** Built on pure C and standard Raylib windowing/math utilities.

---

## Prerequisites

Ensure you have the following installed:

* A C compiler (`gcc`, `clang`, or MSVC)
* **CMake** (v3.16 or newer)
* **Raylib** (system install or pulled via CMake FetchContent)

---

## Build & Run

To keep the repository clean, use an out-of-source build:

```bash
# Clone the repository
git clone [https://github.com/](https://github.com/)<your-username>/Collision-Simulator.git
cd Collision-Simulator

# Configure the build directory
cmake -B build

# Build the executable
cmake --build build

# Run the simulation
./build/collision_engine
```

---
*Note: This README was generated with AI assistance.*
