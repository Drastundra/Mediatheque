#include "Game.h"

#include <iostream>

Game::Game(const std::string& title, const std::string& studio, int pegi, GameGenre genre)
    : Media(title, MediaType::GAME), studio(studio), pegi(pegi), genre(genre) {}

std::string Game::getStudio() const {
    return studio;
}

int Game::getPegi() const {
    return pegi;
}

GameGenre Game::getGenre() const {
    return genre;
}

void Game::displayDetails() const {
    std::cout << "--- Jeu Vidéo ---\n";
    Media::displayDetails();
    std::cout << "Studio : " << studio << std::endl;
    std::cout << "PEGI : " << pegi << std::endl;

    std::string genreStr;
    switch (genre) {
    case GameGenre::ACTION: genreStr = "Action"; break;
    case GameGenre::ADVENTURE: genreStr = "Aventure"; break;
    case GameGenre::STRATEGY: genreStr = "Stratégie"; break;
    case GameGenre::RPG: genreStr = "RPG"; break;
    case GameGenre::SPORTS: genreStr = "Sports"; break;
    }
    std::cout << "Genre : " << genreStr << std::endl;
}