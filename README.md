# 🎮 Console RPG — Terminal Game on C++17

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.14%2B-green.svg)](https://cmake.org/)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

> Turn-based console RPG written in modern C++17. Explore procedurally generated rooms, open chests, dodge traps, and fight patrolling monsters in tactical combat. Three hero classes, each with a unique playstyle.

---

## 🎬 Demo

![Gameplay demo](screenshots/demo.gif)

---

## 📖 About the project

A fully playable RPG in the terminal, built from scratch as a portfolio project. It demonstrates:

- **Object-oriented design** with a clear separation of concerns
- **Design patterns**: Command (combat actions), Factory (rooms & monsters), Strategy (hero abilities)
- **Modern C++17**: smart pointers, `override`, `auto`, move semantics
- **Memory safety**: `std::unique_ptr` for ownership, no raw `new`/`delete`
- **Testing**: 18 unit tests with Google Test
- **Build system**: CMake with `FetchContent` for dependencies

---

## ✨ Features

### Gameplay
- **Procedural rooms** — 4 types, generated randomly each run
- **Hitbox collision system** — invisible 4×4 zones around entities trigger events
- **Turn-based combat** — attack, defend, or use a special ability
- **Patrolling monsters** — enemies move after each player turn
- **Persistent state** — chests, traps, and defeated monsters are tracked

### Hero classes

| Class | HP | Mana | Base ATK | Unique ability |
|-------|----|------|----------|----------------|
| 🗡️ **Assassin** | 10 | 8 | 12 | *Escape* — 50% chance to flee; on failure takes +50% damage |
| 🛡️ **Warrior** | 15 | 5 | 10 | *Second Wind* — revive with 1 HP, but no healing for the rest of the fight |
| 🔥 **Mage** | 8 | 15 | 8 | *Fireball* — +10 bonus damage, costs 10% of max mana |

### Objects
- **Chest** `C` — grants +10 HP on open
- **Trap** `^` — deals 20 damage when triggered
- **Monster** `M` — initiates combat on contact

