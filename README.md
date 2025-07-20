## 🧖 Dino Rush – Endless Runner in C++ with Raylib

**Dino Rush** to dynamiczna gra typu **Endless Runner**, w której wcielasz się w dinozaura uciekającego przez losowo generowane, pełne przeszkód światy. Projekt został zrealizowany jako część kursu *Programowanie Komputerów* na Politechnice Śląskiej.

---

### 🎮 Gameplay

* Cztery różne światy: pustynia (dzień/noc), las (dzień/noc)
* Animowane przeszkody: kaktusy, pnie, nietoperze, pterodaktyle
* Prosta, intuicyjna rozgrywka
* Możliwość personalizacji postaci przez sklep
* System logowania i rejestracji użytkownika


<table>
  <tr>
    <td align="center">
      <strong>🌼 Desert – Day</strong><br>
      <img src="https://github.com/user-attachments/assets/47be073e-584f-4ca9-b85c-3cacbfd1cdf6" alt="🌼 Desert – Day" width="300">
    </td>
    <td align="center">
      <strong>🌙 Desert – Night</strong><br>
      <img src="https://github.com/user-attachments/assets/059314da-c3d4-47f6-95a1-0b88d7328f64" alt="🌙 Desert – Night" width="300">
    </td>
  </tr>
  <tr>
    <td align="center">
      <strong>🌲 Forest – Day</strong><br>
      <img src="https://github.com/user-attachments/assets/3a4bc5f0-e65c-49a3-be62-c7956adcaae0" alt="🌲 Forest – Day" width="300">
    </td>
    <td align="center">
      <strong>🌌 Forest – Night</strong><br>
      <img src="https://github.com/user-attachments/assets/4ae8e4f6-ab47-4380-b239-f1f81f88b536" alt="🌌 Forest – Night" width="300">
    </td>
  </tr>
</table>

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

## 🚀 Kompilacja i uruchamianie

Ten projekt nie zawiera gotowego pliku wykonywalnego. Aby uruchomić grę, wykonaj poniższe kroki:

1. Sklonuj repozytorium:

   ```bash
   git clone https://github.com/Pucdolf/EndlessRunner.git
   ```
2. Otwórz projekt w IDE obsługującym C++20 Modules, np. Visual Studio 2022 lub nowszym.
3. Upewnij się, że masz zainstalowaną i skonfigurowaną bibliotekę Raylib.
4. W IDE wybierz konfigurację `Debug` lub `Release` i skompiluj rozwiązanie (Build Solution).
5. Uruchom grę (np. klawiszem F5 lub opcją "Start Debugging").

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

