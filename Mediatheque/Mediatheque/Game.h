#ifndef GAME_H
#define GAME_H

#include "Media.h"

#include <string>

enum class GameGenre {
    ACTION,
    ADVENTURE,
    STRATEGY,
    RPG,
    SPORTS
};

class Game : public Media {
private:
    std::string studio;
    int pegi;
    GameGenre genre;

public:
    Game(const std::string& title, const std::string& studio, int pegi, GameGenre genre);

    std::string getStudio() const;
    int getPegi() const;
    GameGenre getGenre() const;
    void displayDetails() const override;
};

#endif // GAME_H