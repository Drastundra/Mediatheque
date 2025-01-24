#ifndef MEDIA_H
#define MEDIA_H

#include <string>
#include <iostream>

enum class MediaState {
    AVAILABLE,
    BORROWED
};

enum class MediaType {
    BOOK,
    FILM,
    GAME
};

class Media {
protected:
    std::string title;
    MediaState state;
    MediaType type;
    class Client* borrowedBy;

public:
    Media(const std::string& title, MediaType type);

    virtual ~Media() = default;

    std::string getTitle() const;
    MediaState getState() const;
    MediaType getType() const;
    Client* getBorrowedBy() const;

    virtual void displayDetails() const = 0;

    void borrow(class Client* client);
    void returnMedia();
    bool isAvailable() const;

    // Pour permettre la comparaison des médias
    bool operator==(const Media& other) const;
};

#endif // MEDIA_H