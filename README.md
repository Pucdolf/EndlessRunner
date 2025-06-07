## 🧖 Dino Rush – Endless Runner in C++ with Raylib

**Dino Rush** to dynamiczna gra typu **Endless Runner**, w której wcielasz się w dinozaura uciekającego przez losowo generowane, pełne przeszkód światy. Projekt został zrealizowany jako część kursu *Programowanie Komputerów* na Politechnice Śląskiej.

---

### 🎮 Gameplay

* Cztery różne światy: pustynia (dzień/noc), las (dzień/noc)
* Animowane przeszkody: kaktusy, pnie, nietoperze, pterodaktyle
* Prosta, intuicyjna rozgrywka
* Możliwość personalizacji postaci przez sklep
* System logowania i rejestracji użytkownika

#### 🌼 Desert – Day

![Desert](https://github.com/user-attachments/assets/47be073e-584f-4ca9-b85c-3cacbfd1cdf6)


#### 🌙 Desert – Night

![DesertNight](https://github.com/user-attachments/assets/059314da-c3d4-47f6-95a1-0b88d7328f64)

#### 🌲 Forest – Day

![gameplay-forest-day](media/gameplay-forest-day.gif)

#### 🌌 Forest – Night

![gameplay-forest-night](media/gameplay-forest-night.gif)

---

### 🛍️ Shop System

Gracze mogą wybrać jednego z wielu dinozaurow, którymi będą grać.
![Shop](https://github.com/user-attachments/assets/0cb07ebe-0f76-4a9c-b8ee-741b7746e02e)

---

### 📂 Struktura projektu

Projekt został napisany w C++ z użyciem biblioteki **Raylib** i C++20 Modules. Główne moduły:

* `AnimatedSpriteModule` – obsługa animowanych sprite’ów
* `BoardModule` – główna logika gry
* `ObstacleFactoryModule` – dynamiczne generowanie przeszkód
* `AuthModule` – logowanie, rejestracja z plikiem `users.txt`
* `ShopModule` – wybór postaci
* `ControllerModule` – sterowanie stanem gry i tłem
* `ResourcesModule` – zarządzanie teksturami i zasobami

---

### 🛠️ Wymagania

* C++20 (moduły!)
* [Raylib](https://www.raylib.com/)
* System: Windows/Linux
* Kompilator obsługujący `std::module` (np. MSVC 2022+, GCC 13+, Clang 16+)

---

### 🧪 Uruchomienie

1. Skompiluj pliki C++ ręcznie lub przez skrypt.
2. Uruchom plik wykonywalny `DinoRush.exe` (Windows) lub `./DinoRush` (Linux).

---

### 📁 Pliki użytkownika

* `users.txt` – zapisane konta (login + hash hasła)
* `scores.txt` – historia wyników

---

### 🎓 Projekt studencki

Zrealizowano w ramach kursu *Programowanie Komputerów*
Politechnika Śląska, kierunek: Informatyka
Semestr 4, 2024/2025

---

