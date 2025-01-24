#include "Media.h"

#include <optional>
#include <stdexcept>

Media::Media(const std::string& title, const std::string& type)
    : title(title), type(type), isAvailable(true) {
    if (title.empty()) throw std::invalid_argument("Title cannot be empty");
}

std::string Media::getTitle() const { return title; }
std::string Media::getType() const { return type; }
bool Media::isMediaAvailable() const { return isAvailable; }
std::optional<std::string> Media::getBorrower() const { return borrower; }

void Media::borrow(const std::string& clientName) {
    if (!isAvailable) {
        throw std::runtime_error("Media already borrowed");
    }
    borrower = clientName;
    isAvailable = false;
}

void Media::returnMedia() {
    if (isAvailable) {
        throw std::runtime_error("Media already available");
    }
    borrower.reset();
    isAvailable = true;
}

int Media::getAgeRestriction() const { return 0; }

std::string Media::getDetails() const {
    return "Title: " + title + " | Type: " + type +
        " | Status: " + (isAvailable ? "Available" : "Borrowed");
}