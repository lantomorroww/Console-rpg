#include "rooms/Room.h"
#include "entities/Monster.h"
#include <random>
#include <iostream>
#include <algorithm>

Room::Room() : chest(0), objects(0) {}

Room::Room(int chestCount, int objectsCount, std::vector<std::unique_ptr<Monster>> mon)
    : chest(chestCount), objects(objectsCount), monsters(std::move(mon)) {}

Room::~Room() = default;

void Room::showRoom() const {
    std::cout << "Room: chests=" << chest << ", objects=" << objects
              << ", monsters=" << monsters.size() << std::endl;
    for (auto& m : monsters) m->show();
}

void Room::draw(const Hero& hero) const {
    const int rows = 20, cols = 76;
    const int doorRow = rows, doorCol1 = 38, doorCol2 = 39;
    std::vector<std::vector<char>> map(rows + 1, std::vector<char>(cols + 1, ' '));

    // Стены и дверь
    for (int c = 1; c <= cols; ++c) {
        map[1][c] = '#';
        map[rows][c] = '#';
    }
    for (int r = 2; r < rows; ++r) {
        map[r][1] = '#';
        map[r][cols] = '#';
    }
    map[doorRow][doorCol1] = ' ';
    map[doorRow][doorCol2] = ' ';

    // Сундуки
    if (chest >= 1 && !chestOpened[0]) map[3][3] = 'C';
    if (chest >= 2 && !chestOpened[1]) map[3][cols-2] = 'C';
    // Ловушки
    if (objects >= 1 && !trapTriggered[0]) map[rows-1][doorCol1] = '^';
    if (objects >= 2 && !trapTriggered[1]) map[rows-2][doorCol2] = '^';
    // Монстры (живые)
    int idx = 0;
    for (auto& m : monsters) {
        if (m->getHp() > 0) {
            int mx = (idx == 0) ? cols/2 : cols/2;
            int my = (idx == 0) ? rows/2 : rows/2 + 2;
            map[my][mx] = 'M';
        }
        ++idx;
    }

    // Игрок (рисует себя без хитбокса)
    hero.draw(map);

    // Вывод
    for (int r = 1; r <= rows; ++r) {
        for (int c = 1; c <= cols; ++c)
            std::cout << map[r][c];
        std::cout << '\n';
    }
}

bool Room::isWalkable(int x, int y) const {
    if (x < 1 || x > 76 || y < 1 || y > 20) return false;
    if (y == 1 || y == 20 || x == 1 || x == 76) {
        if (y == 20 && (x == 38 || x == 39)) return true;
        return false;
    }
    return true;
}

bool Room::isOccupied(int x, int y) const {
    const int cols = 76, rows = 20;
    const int doorCol1 = 38, doorCol2 = 39;
    const int half = 2;
    auto inHitbox = [&](int ox, int oy) -> bool {
        for (int dy = -half; dy <= half-1; ++dy)
            for (int dx = -half; dx <= half-1; ++dx)
                if (ox + dx == x && oy + dy == y) return true;
        return false;
    };
    if (chest >= 1 && !chestOpened[0] && inHitbox(3, 3)) return true;
    if (chest >= 2 && !chestOpened[1] && inHitbox(3, cols-2)) return true;
    if (objects >= 1 && !trapTriggered[0] && inHitbox(doorCol1, rows-1)) return true;
    if (objects >= 2 && !trapTriggered[1] && inHitbox(doorCol2, rows-2)) return true;
    int idx = 0;
    for (auto& m : monsters) {
        if (m->getHp() > 0) {
            int mx = (idx == 0) ? cols/2 : cols/2;
            int my = (idx == 0) ? rows/2 : rows/2 + 2;
            if (inHitbox(mx, my)) return true;
        }
        ++idx;
    }
    return false;
}

void Room::movePlayer(Hero& hero, char direction) {
    int oldX = hero.getX(), oldY = hero.getY();
    hero.move(direction);
    if (!isWalkable(hero.getX(), hero.getY()) || isOccupied(hero.getX(), hero.getY())) {
        hero.setStartPosition(oldX, oldY);
    }
}

void Room::checkTriggers(Hero& hero, bool& battleStarted, std::unique_ptr<Monster>*& targetMonster) {
    const int cols = 76, rows = 20;
    const int doorCol1 = 38, doorCol2 = 39;
    const int half = 2;
    auto hitboxesOverlap = [&](int x1, int y1, int x2, int y2) -> bool {
        return (std::abs(x1 - x2) < 4) && (std::abs(y1 - y2) < 4);
    };
    int hx = hero.getX(), hy = hero.getY();

    // Сундуки
    if (chest >= 1 && !chestOpened[0] && hitboxesOverlap(hx, hy, 3, 3)) {
        chestOpened[0] = true;
        hero.addHP(10);
        std::cout << "\n*** Вы открыли сундук! +10 HP ***\n";
    }
    if (chest >= 2 && !chestOpened[1] && hitboxesOverlap(hx, hy, 3, cols-2)) {
        chestOpened[1] = true;
        hero.addHP(10);
        std::cout << "\n*** Вы открыли сундук! +10 HP ***\n";
    }

    // Ловушки
    if (objects >= 1 && !trapTriggered[0] && hitboxesOverlap(hx, hy, doorCol1, rows-1)) {
        trapTriggered[0] = true;
        hero.addHP(-20);
        std::cout << "\n*** Ловушка! -20 HP ***\n";
    }
    if (objects >= 2 && !trapTriggered[1] && hitboxesOverlap(hx, hy, doorCol2, rows-2)) {
        trapTriggered[1] = true;
        hero.addHP(-20);
        std::cout << "\n*** Ловушка! -20 HP ***\n";
    }

    // Монстры
    if (!battleStarted) {
        int idx = 0;
        for (auto& m : monsters) {
            if (m->getHp() > 0) {
                int mx = (idx == 0) ? cols/2 : cols/2;
                int my = (idx == 0) ? rows/2 : rows/2 + 2;
                if (hitboxesOverlap(hx, hy, mx, my)) {
                    battleStarted = true;
                    targetMonster = &m;
                    return;
                }
            }
            ++idx;
        }
    }
}

void Room::updateMonsters() {
    for (auto& m : monsters) {
        if (m->getHp() <= 0) continue;
        int dx = rand() % 3 - 1;
        int dy = rand() % 3 - 1;
        int nx = m->getX() + dx;
        int ny = m->getY() + dy;
        if (isWalkable(nx, ny) && !isOccupied(nx, ny)) {
            m->setPosition(nx, ny);
        }
    }
}

void Room::removeDeadMonsters() {
    monsters.erase(std::remove_if(monsters.begin(), monsters.end(),
        [](const std::unique_ptr<Monster>& m) { return m->getHp() <= 0; }),
        monsters.end());
}

// Генерация случайной комнаты
Room generateRandomRoom() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> typeDist(0, 3);
    RoomType type = static_cast<RoomType>(typeDist(gen));
    int chests = 0, traps = 0;
    std::vector<std::unique_ptr<Monster>> monsters;

    auto makeMonster = [](int x, int y) -> std::unique_ptr<Monster> {
        return createRandomMonster(x, y);
    };

    const int cols = 76, rows = 20;
    switch (type) {
        case RoomType::EMPTY:
            break;
        case RoomType::MONSTER_CHEST:
            chests = 1;
            monsters.push_back(makeMonster(cols/2, rows/2));
            break;
        case RoomType::MONSTER_CHEST_TRAP:
            chests = 1;
            traps = 1;
            monsters.push_back(makeMonster(cols/2, rows/2));
            break;
        case RoomType::MAXIMAL:
            chests = 2;
            traps = 2;
            monsters.push_back(makeMonster(cols/2, rows/2));
            monsters.push_back(makeMonster(cols/2, rows/2 + 2));
            break;
    }
    return Room(chests, traps, std::move(monsters));
}