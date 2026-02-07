# Geant4 Simulation Project

This project simulates particle interactions using Geant4.

## Prerequisites

To build and run this simulation, you need the following software installed:

- **Geant4**: With UI and Visualization components enabled (`ui_all`, `vis_all`).
- **CMake**: Version 3.16 or higher.
- **ROOT**: For data analysis and merging output files (required for `runmt` workflow).
- **C++ Compiler**: Compatible with your Geant4 installation.
- **Fish Shell**: The environment setup scripts are written for `fish`.

## Building the Project

1. Clone the repository.
2. Create a build directory (if it doesn't exist, though the workflow assumes it does or you are in it):

    ```fish
    mkdir build
    ```

## Running the Simulation

The project includes a `env.fish` script helper to simplify building and running the simulation.

### 1. Setup Environment

Source the environment script to load aliases and functions:

```fish
source env.fish
cd build
```

### 2. Run with Visualization (Interactive Mode)

To build and run the simulation with the graphical user interface:

```fish
run
```

This command will:

1. Run CMake and compile the project (using `make -j4`).
2. Launch the executable (`./main`) with `QT_QPA_PLATFORM=xcb`.

### 3. Run in Batch Mode (Macro)

To build, run the simulation using `mac/run.mac`, and save the resulting ROOT output:

```fish
runmt FILENAME.root
```

*Replace `FILENAME.root` with your desired output filename.*

This command will run the `run.mac` macro without visual output and save the results to `root/FILENAME.root`. The workflow includes:

## Analyzing Output

To analyze the output ROOT files, you can use the following alias:

```fish
oroot
```

This will open the ROOT terminal, after which you can open the TBrowser to inspect the contents of the ROOT files:

```root
new TBrowser;
```

To exit the ROOT terminal, simply type:

```root
.q
```

## Project Structure

- `src/`: Source code (`.cc` and `.hh` files).
- `mac/`: Geant4 macro files (e.g., `run.mac`).
- `root/`: Destination for saved ROOT output files.
- `build/`: Build artifacts (not committed).
- `env.fish`: Helper script for workflow management.
