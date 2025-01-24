#include "Client.h"

#include <algorithm>

Client::Client(const std::string& name, const std::string& firstname, int age,
    const std::string& address, const std::string& phoneNumber, const std::string& mail)
    : name(name), firstname(firstname), age(age), address(address),
    phoneNumber(phoneNumber), mail(mail) {
    if (age < 0) throw std::invalid_argument("Age cannot be negative");
    if (name.empty() || firstname.empty()) throw std::invalid_argument("Name and firstname cannot be empty");
    if (mail.empty()) throw std::invalid_argument("Email cannot be empty");
}

std::string Client::getName() const { return name; }
std::string Client::getFirstname() const { return firstname; }
int Client::getAge() const { return age; }
std::string Client::getAddress() const { return address; }
std::string Client::getPhoneNumber() const { return phoneNumber; }
std::string Client::getMail() const { return mail; }
const std::vector<std::string>& Client::getBorrowedMedia() const { return borrowedMedia; }

bool Client::canBorrow() const { return borrowedMedia.size() < 5; }

void Client::borrowMedia(const std::string& mediaTitle) {
    if (!canBorrow()) {
        throw std::runtime_error("Reached maximum borrowed media");
    }
    borrowedMedia.push_back(mediaTitle);
}

void Client::returnMedia(const std::string& mediaTitle) {
    auto it = std::find(borrowedMedia.begin(), borrowedMedia.end(), mediaTitle);
    if (it != borrowedMedia.end()) {
        borrowedMedia.erase(it);
    }
    else {
        throw std::runtime_error("Media not found");
    }
}

std::string Client::getFullIdentifier() const {
    return name + "_" + firstname + "_" + mail;
}