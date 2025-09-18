# XiOS

Welcome to **XiOS** — an ambitious new operating system project, built for innovation and learning!  
This repo contains all files, scripts, and configuration needed to build and run the XiOS kernel and related components.

---

## 🗂️ Repository Structure

- **.github/**  
  Community health files, workflows, and GitHub-specific configuration.
- **build.sh**  
  Main build script for compiling XiOS. Run this to build the OS.
- **build/**  
  Output directory for build artifacts.
- **limine**  
  Limine bootloader binary or reference file.
- **limine.cfg**  
  Configuration file for the Limine bootloader.
- **run_gui.sh**  
  Script to launch or test the graphical user interface.
- **src/**  
  Source code for the operating system.

---

## 🚀 Getting Started

### Prerequisites

- A UNIX-like environment (Linux/macOS recommended)
- GCC, make, and other development tools
- (If testing in a VM) QEMU or similar

### Build

```bash
./build.sh
```

### Run (GUI)

```bash
./run_gui.sh
```

---

## ⚙️ Bootloader

XiOS uses the **Limine** bootloader.  
Edit `limine.cfg` to change boot settings. Make sure the `limine` file is correctly referenced in your build output.

---

## 📁 Source Code

All kernel and OS source code is located in the `src/` directory.

---

## 🛠️ Contributing

1. Fork this repo and create your branch (`git checkout -b feature/your-feature`)
2. Commit your changes (`git commit -am 'Add a new feature'`)
3. Push to the branch (`git push origin feature/your-feature`)
4. Open a pull request!

---

## 📄 License

This project is licensed under the GNU GPL v3.0. See the [LICENSE](LICENSE) file for details.

---

## 💬 Support & Community

- Open an issue for bugs, questions, or feature requests
- PRs are welcome — let's build something awesome together!

---

> *XiOS is a project by [XIStudios](https://github.com/XIStudios).*