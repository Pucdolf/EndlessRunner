## 🧖 Dino Rush – Endless Runner in C++ with Raylib

![loading](media/loading.gif)

**Dino Rush** to dynamiczna gra typu **Endless Runner**, w której wcielasz się w dinozaura uciekającego przez losowo generowane, pełne przeszkód światy. Projekt został zrealizowany jako część kursu *Programowanie Komputerów* na Politechnice Śląskiej.

---

### 🎮 Gameplay

* Cztery różne światy: pustynia (dzień/noc), las (dzień/noc)
* Animowane przeszkody: kaktusy, pnie, nietoperze, pterodaktyle
* Prosta, intuicyjna rozgrywka
* Możliwość personalizacji postaci przez sklep
* System logowania i rejestracji użytkownika

#### 🌼 Desert – Day

![Desert](https://github.com/user-attachments/assets/96e953fd-faa8-45d6-b2c9-945894ffad9b)

#### 🌙 Desert – Night

![DesertNight](https://github.com/user-attachments/assets/e87d20f0-a3ab-4f31-aa54-0dcbc8ab6f97)

#### 🌲 Forest – Day

![gameplay-forest-day](media/gameplay-forest-day.gif)

#### 🌌 Forest – Night

![gameplay-forest-night](media/gameplay-forest-night.gif)

---

### 🛙 Shop System

Gracze mogą wybrać jednego z wielu dinozaurow, którymi będą grać.

![shop](media/shop.gif)

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

### 📸 Media

Dodaj gify do folderu `media/` w repozytorium i zaktualizuj ścieżki w README.
