# XiOS Copilot Coding Instructions

## Overview

XiOS is a lightweight operating system kernel project with a clear division between bootloader code, kernel internals, and hardware drivers. Key components include:

- **Boot & Platform**: The `/limine/` directory contains the bootloader and associated configuration files. Boot processes are initiated via scripts like `build.sh` and supplemented by files such as `limine.cfg`.
- **Kernel Core**: The `/src/` directory is organized into subdirectories:
  - `arch/`: Architecture-specific code (e.g., the i386 assembly in `src/arch/i386/idt_asm.asm` for interrupt handling).
  - `core/`: Core kernel functionality and system management.
  - `drivers/`: Hardware drivers and peripheral interfaces.
  - `include/`: Header files defining kernel interfaces and shared declarations.

## Developer Workflows

- **Building**: Run `build.sh` to compile the project. This integrates both assembly and C components to produce a bootable ISO stored in `build/xios.iso`.
- **Testing & Debugging**: Use `run_gui.sh` for GUI and system testing. For low-level debugging (e.g., interrupt handling in `src/arch/i386/idt_asm.asm`), refer to the assembly code and relevant build logs.
- **Version Control & Commit Conventions**: Changes affecting major components (bootloader in `/limine/` or kernel internals in `/src/`) should be reviewed in context. Maintain clear commit messages describing the impact on system startup, hardware interfacing, or architectural modifications.

## Code Conventions & Patterns

- **Assembly Code**: Files like `src/arch/i386/idt_asm.asm` follow strict conventions for register usage and interrupt management. Look for patterns in how interrupts are set up and handled.
- **C Code Integration**: Kernel C files are geared toward a freestanding environment with minimal reliance on standard libraries. Note the separation between high-level driver management and low-level system initialization.
- **Directory Boundaries**: The organization — with `/limine/` for bootloader, `/src/` for core functionality, and `/drivers/` for hardware interfaces — underscores clear modular boundaries. Changes in one module should be reviewed without unnecessary coupling to others.

## Integration & Dependencies

- **Bootloader and Kernel Interaction**: The bootloader in `/limine/` sets up the execution environment before handing control to the kernel in `/src/`. Ensure modifications in boot processes are aligned with kernel initialization routines.
- **Build System**: The GNUmakefile and custom scripts (e.g., `build.sh`) encapsulate project-specific build steps, linking both assembly and C components. Review these files for any non-obvious build dependencies and linking order.

## Examples & Key References

- Review `src/arch/i386/idt_asm.asm` for interrupt handling conventions.
- Refer to `build.sh` and the GNUmakefile in `/limine/` for insights on the build process.
- Examine `limine/config.h` for bootloader configurations that affect early system initialization.

---

AI Coding Agents should adhere to the above conventions, respecting the modular boundaries and specific integration points of the XiOS codebase. Always cross-reference build scripts and configuration files to understand context and dependency details. 

Please provide feedback on any unclear sections or suggest additional details to include.