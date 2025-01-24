#ifndef INPUT_VALIDATOR_H
#define INPUT_VALIDATOR_H

#include <string>
#include <regex>

class InputValidator {
public:
    // Validation de l'email
    static bool isValidEmail(const std::string& email);

    // Validation du num�ro de t�l�phone
    static bool isValidPhoneNumber(const std::string& phoneNumber);

    // Validation de l'�ge
    static bool isValidAge(int age);

    // Validation du nom et pr�nom (lettres uniquement)
    static bool isValidName(const std::string& name);

    // Validation du titre de m�dia
    static bool isValidMediaTitle(const std::string& title);

    // Validation de l'ISBN
    static bool isValidISBN(const std::string& isbn);
};

#endif // INPUT_VALIDATOR_H