#include "Media.h"
#include "Client.h"

Media::Media(const std::string& title, MediaType type)
    : title(title), type(type), state(MediaState::AVAILABLE), borrowedBy(nullptr) {}

std::string Media::getTitle() const {
    return title;
}

MediaState Media::getState() const {
    return state;
}

MediaType Media::getType() const {
    return type;
}

Client* Media::getBorrowedBy() const {
    return borrowedBy;
}

void Media::borrow(Client* client) {
    if (state == MediaState::AVAILABLE) {
        state = MediaState::BORROWED;
        borrowedBy = client;
    }
}

void Media::returnMedia() {
    state = MediaState::AVAILABLE;
    borrowedBy = nullptr;
}

bool Media::isAvailable() const {
    return state == MediaState::AVAILABLE;
}

bool Media::operator==(const Media& other) const {
    return title == other.title && type == other.type;
}

void Media::displayDetails() const {
    std::cout << "Titre : " << title << std::endl;
    std::cout << "État : " << (state == MediaState::AVAILABLE ? "Disponible" : "Emprunté") << std::endl;
}