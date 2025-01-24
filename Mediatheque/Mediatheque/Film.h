#ifndef FILM_H
#define FILM_H

#include <string>

#include "Media.h"

enum class FilmSupport {
    BLURAY,
    DVD
};

class Film : public Media {
private:
    FilmSupport support;
    int ageLimit;

public:
    Film(const std::string& title, FilmSupport support, int ageLimit);

    FilmSupport getSupport() const;
    int getAgeLimit() const;
    void displayDetails() const override;
};

#endif // FILM_H