#pragma once

#include <string>
#include <optional>

class Client; // Forward declaration

class Media {
protected:
    std::string title;
    std::string type;
    bool isAvailable;
    std::optional<std::string> borrower;

public:
    Media(const std::string& title, const std::string& type);
    virtual ~Media() = default;

    std::string getTitle() const;
    std::string getType() const;
    bool isMediaAvailable() const;
    std::optional<std::string> getBorrower() const;

    virtual void borrow(const std::string& clientName);
    virtual void returnMedia();
    virtual int getAgeRestriction() const;
    virtual std::string getDetails() const;
};

class Book : public Media {
private:
    std::string isbn;

public:
    Book(const std::string& title, const std::string& isbn);
    std::string getIsbn() const;
    std::string getDetails() const override;
};

class Film : public Media {
private:
    std::string support;
    int ageRestriction;

public:
    Film(const std::string& title, const std::string& support, int ageRestriction);
    int getAgeRestriction() const override;
    std::string getSupport() const;
    std::string getDetails() const override;
};

class Game : public Media {
private:
    std::string studio;
    int pegi;
    std::string genre;

public:
    Game(const std::string& title, const std::string& studio, int pegi, const std::string& genre);
    int getAgeRestriction() const override;
    std::string getDetails() const override;
};