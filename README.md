## 🧛 Dino Rush – Endless Runner in C++ with Raylib

**Dino Rush** is a dynamic **Endless Runner** game where you take on the role of a dinosaur running through randomly generated worlds filled with obstacles. The project was developed as part of the *Computer Programming* course at the Silesian University of Technology.

---

### 🎮 Download and Play (For Players)
If you just want to play, download the ready-to-use game installer. It contains all the necessary libraries and paid graphical assets that are not present in the code repository.
👉 **[Download Dino Rush v1.0.1](https://github.com/Pucdolf/EndlessRunner/releases/latest)**

*Instructions: Download the .exe file, run it, and follow the installer instructions.*

---

### 🕹️ Gameplay

<p align="center">
  <img src="https://github.com/user-attachments/assets/47be073e-584f-4ca9-b85c-3cacbfd1cdf6" width="400" alt="Desert Day">
  <img src="https://github.com/user-attachments/assets/059314da-c3d4-47f6-95a1-0b88d7328f64" width="400" alt="Desert Night">
</p>
<p align="center">
  <img src="https://github.com/user-attachments/assets/3a4bc5f0-e65c-49a3-be62-c7956adcaae0" width="400" alt="Forest Day">
  <img src="https://github.com/user-attachments/assets/4ae8e4f6-ab47-4380-b239-f1f81f88b536" width="400" alt="Forest Night">
</p>

---

### 🛍️ Shop System

Players can choose from several dinosaurs to play as.
<p align="center">
  <img src="https://github.com/user-attachments/assets/0cb07ebe-0f76-4a9c-b8ee-741b7746e02e" width="600" alt="Shop System">
</p>

---

### 📂 Project Structure

The project is written in C++ using the **Raylib** library and C++20 Modules. Main modules:

* `AnimatedSpriteModule` – handles animated sprites
* `BoardModule` – main game logic
* `ObstacleFactoryModule` – dynamic obstacle generation
* `AuthModule` – login, registration with the `users.txt` file
* `ShopModule` – character selection
* `ControllerModule` – game state and background control
* `ResourcesModule` – texture and resource management

---

### 🎨 Assets and License (Important!)
This repository contains **only the source code** of the game.
- **Graphics and sounds:** The project uses a professional asset pack [Dinosaur Rush Assets](https://alb-pixel-store.itch.io/dinosaur-rush-assets) by **Alb-Pixel Store**. Due to the license prohibiting the redistribution of source files, they are not part of the Git repository.
- **For developers:** To compile the project, you must provide your own assets in the `textures/` and `media/` folders or download the version from the installer.
- **For players:** The full version of the game with original graphics is available only through the [installer in the Releases section](https://github.com/Pucdolf/EndlessRunner/releases/latest).

---

### 🛠️ Requirements

* C++20 (modules)
* [Raylib](https://www.raylib.com/)
* OS: Windows/Linux
* Compiler supporting modules (e.g., Visual Studio 2022 v143+)

---

## 🚀 Compilation and Running (For Developers)

If you want to develop the project or analyze the code, follow these steps:

1. Clone the repository:
   ```bash
   git clone https://github.com/Pucdolf/EndlessRunner.git
   ```

2. **Raylib Installation (recommended via vcpkg):**
   - Download `vcpkg`: `git clone https://github.com/microsoft/vcpkg.git`
   - Install: `.\vcpkg\bootstrap-vcpkg.bat`
   - Integrate with VS: `.\vcpkg\vcpkg integrate install`
   - Download Raylib: `.\vcpkg\vcpkg install raylib:x64-windows`

3. Open the project in Visual Studio 2022.
4. **Note:** The game will not start without image files in the `textures/` folder. You must provide your own files with names matching those in `Resources.cpp`.
5. Select the `Release` configuration and compile (Build Solution).

---

### 💾 User Files

* `users.txt` – saved accounts (login + password hash)
* `scores.txt` – score history

---

### 🎓 Student Project

Developed as part of the *Computer Programming* course
Silesian University of Technology, major: Computer Science
Semester 4, 2024/2025

---
