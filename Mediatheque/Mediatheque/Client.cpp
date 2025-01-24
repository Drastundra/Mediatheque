#include "Client.h"
#include "Media.h"

Client::Client(const std::string& name, const std::string& firstname,
    int age, const std::string& address,
    const std::string& phoneNumber, const std::string& mail)
    : name(name), firstname(firstname), age(age),
    address(address), phoneNumber(phoneNumber), mail(mail) {}

std::string Client::getName() const { return name; }
std::string Client::getFirstname() const { return firstname; }
int Client::getAge() const { return age; }
std::string Client::getAddress() const { return address; }
std::string Client::getPhoneNumber() const { return phoneNumber; }
std::string Client::getMail() const { return mail; }

bool Client::canBorrow() const {
    return borrowedMedia.size() < 5;
}

void Client::borrowMedia(Media* media) {
    if (canBorrow()) {
        borrowedMedia.push_back(media);
    }
}

void Client::returnMedia(Media* media) {
    auto it = std::find(borrowedMedia.begin(), borrowedMedia.end(), media);
    if (it != borrowedMedia.end()) {
        borrowedMedia.erase(it);
    }
}

std::vector<Media*> Client::getBorrowedMedia() const {
    return borrowedMedia;
}