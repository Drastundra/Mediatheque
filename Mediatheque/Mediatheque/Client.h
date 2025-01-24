#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>

class Client {
private:
    std::string name;
    std::string firstname;
    int age;
    std::string address;
    std::string phoneNumber;
    std::string mail;
    std::vector<class Media*> borrowedMedia;

public:
    // Constructeur
    Client(const std::string& name, const std::string& firstname,
        int age, const std::string& address,
        const std::string& phoneNumber, const std::string& mail);

    // Getters
    std::string getName() const;
    std::string getFirstname() const;
    int getAge() const;
    std::string getAddress() const;
    std::string getPhoneNumber() const;
    std::string getMail() const;

    // Méthodes de gestion des emprunts
    bool canBorrow() const;  // Vérifie si le client peut emprunter
    void borrowMedia(class Media* media);
    void returnMedia(class Media* media);
    std::vector<class Media*> getBorrowedMedia() const;
};

#endif // CLIENT_H