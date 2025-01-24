#include "Film.h"

#include <iostream>

Film::Film(const std::string& title, FilmSupport support, int ageLimit)
    : Media(title, MediaType::FILM), support(support), ageLimit(ageLimit) {}

FilmSupport Film::getSupport() const {
    return support;
}

int Film::getAgeLimit() const {
    return ageLimit;
}

void Film::displayDetails() const {
    std::cout << "--- Film ---\n";
    Media::displayDetails();
    std::cout << "Support : " << (support == FilmSupport::BLURAY ? "Blu-ray" : "DVD") << std::endl;
    std::cout << "Âge limite : " << ageLimit << " ans\n";
}