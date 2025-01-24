#include "InputValidator.h"

bool InputValidator::isValidEmail(const std::string& email) {
    const std::regex emailPattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return std::regex_match(email, emailPattern);
}

bool InputValidator::isValidPhoneNumber(const std::string& phoneNumber) {
    const std::regex phonePattern(R"(^(\+33|0)[1-9](\d{2}){4}$)");
    return std::regex_match(phoneNumber, phonePattern);
}

bool InputValidator::isValidAge(int age) {
    return age >= 0 && age <= 120;
}

bool InputValidator::isValidName(const std::string& name) {
    const std::regex namePattern(R"(^[a-zA-ZÀ-ÿ\s-]+$)");
    return std::regex_match(name, namePattern) && !name.empty();
}

bool InputValidator::isValidMediaTitle(const std::string& title) {
    return !title.empty() && title.length() <= 100;
}

bool InputValidator::isValidISBN(const std::string& isbn) {
    const std::regex isbnPattern(R"(^(97(8|9))?\d{9}(\d|X)$)");
    return std::regex_match(isbn, isbnPattern);
}