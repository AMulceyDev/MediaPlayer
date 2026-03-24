# Companion Virus

> **Academic project** - No malicious payload. For educational purposes only.  
> Developed by **LINARES Julien** & **MULCEY Amaury** - **University of La Rochelle**

---

## Overview

This project was carried out as part of a practical security course at university. The goal was to design and implement a **companion virus** in C, embedded inside a functional **MediaPlayer** application.

A companion virus works by impersonating existing executables. It renames the original binary with a `.old` extension, copies itself under the original name, and, to avoid suspicion, launches the original program afterward. There is **no destructive payload**. The virus only propagates (1-to-1 replication starting from `media_player`).

The MediaPlayer itself is a GTK3 image viewer used as the initial infection vector.

---

## Project Structure

```
.
├── Billing.c              # Invoice generator (bonus utility)
├── blackjack.c            # Blackjack game (bonus utility)
├── change_calculator.c    # Coin change calculator (bonus utility)
├── compressFile.c         # File compression utility (bonus utility)
├── encryption.c           # Caesar cipher utility (bonus utility)
├── LREmailCounter.c       # GTK3 app – email counter for Univ. La Rochelle
├── media_player.c         # GTK3 MediaPlayer + companion virus
└── CMakeLists.txt         # Build configuration
```

The virus code lives inside `media_player.c` and was written by **Julien Linares**. The MediaPlayer UI was written by **Amaury Mulcey**.

---

## How the Companion Virus Works

1. On launch, `media_player` scans the current directory for executable files (no extension, no `.old` counterpart, not itself).
2. It renames the target binary to `<name>.old`.
3. It copies itself as `<name>` (the new "infected" version).
4. If the running binary is **not** `./media_player` (i.e., it was launched under another name after infection), it transparently executes `<name>.old` to hand control back to the original program.

The virus runs in a **background thread** to avoid blocking the media player UI.

---

## Requirements

- Ubuntu 22.04
- GCC
- CMake
- GTK3 development libraries

Install dependencies:

```bash
sudo apt update
sudo apt install cmake
sudo apt install libgtk-3-dev
```

---

## Build & Run

```bash
mkdir build && cd build
cmake ..
make
```

Executables are output to the `../cdRom` directory (as configured in `CMakeLists.txt`).

Run the media player:

```bash
cd ../cdRom
./media_player
```

---

## Authors

- **Amaury Mulcey** — MediaPlayer, utilities  
- **Julien Linares** — Virus code, utilisties

---

## Disclaimer

This project was developed strictly for **academic purposes** in a controlled university environment. It must not be used outside of this context. The authors take no responsibility for any misuse.
