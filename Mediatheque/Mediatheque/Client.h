#pragma once

#include <string>
#include <vector>
#include <stdexcept>

class Client {
private:
    std::string name;
    std::string firstname;
    int age;
    std::string address;
    std::string phoneNumber;
    std::string mail;
    std::vector<std::string> borrowedMedia;

public:
    Client(const std::string& name, const std::string& firstname, int age,
        const std::string& address, const std::string& phoneNumber, const std::string& mail);

    std::string getName() const;
    std::string getFirstname() const;
    int getAge() const;
    std::string getAddress() const;
    std::string getPhoneNumber() const;
    std::string getMail() const;
    const std::vector<std::string>& getBorrowedMedia() const;

    bool canBorrow() const;
    void borrowMedia(const std::string& mediaTitle);
    void returnMedia(const std::string& mediaTitle);
    std::string getFullIdentifier() const;
};