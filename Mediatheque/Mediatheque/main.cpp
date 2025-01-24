#include "Client.h"
#include "Media.h"
#include "Book.h"
#include "Film.h"
#include "Game.h"
#include "MediaService.h"
#include "InputValidator.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

class CommandLineInterface {
private:
    MediaService mediaService;
    std::vector<std::string> commandHistory;

    void displayMenu() {
        std::cout << "\n--- Médiathèque - Menu Principal ---\n";
        std::cout << "1. Ajouter un client\n";
        std::cout << "2. Supprimer un client\n";
        std::cout << "3. Lister les clients\n";
        std::cout << "4. Ajouter un média\n";
        std::cout << "5. Supprimer un média\n";
        std::cout << "6. Lister les médias\n";
        std::cout << "7. Vérifier l'état d'un média\n";
        std::cout << "8. Qui a emprunté un média\n";
        std::cout << "9. Emprunter un média\n";
        std::cout << "10. Retourner un média\n";
        std::cout << "11. Médias empruntés par un client\n";
        std::cout << "0. Quitter\n";
        std::cout << "Choisissez une option : ";
    }

    std::string getValidatedInput(const std::string& prompt,
        bool (*validator)(const std::string&) = nullptr) {
        std::string input;
        while (true) {
            std::cout << prompt;
            std::getline(std::cin, input);

            if (!validator || validator(input)) {
                return input;
            }
            std::cout << "Entrée invalide. Réessayez.\n";
        }
    }

    int getValidatedAge() {
        int age;
        while (true) {
            std::cout << "Âge : ";
            std::cin >> age;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (InputValidator::isValidAge(age)) {
                return age;
            }
            std::cout << "Âge invalide. Doit être entre 0 et 120.\n";
        }
    }

public:
    void run() {
        int choice;
        do {
            displayMenu();
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (choice) {
            case 1: addClient(); break;
            case 2: removeClient(); break;
            case 3: listClients(); break;
            case 4: addMedia(); break;
            case 5: removeMedia(); break;
            case 6: listMedia(); break;
            case 7: checkMediaState(); break;
            case 8: whoHasBorrowed(); break;
            case 9: rentMedia(); break;
            case 10: returnMedia(); break;
            case 11: showClientMedia(); break;
            case 0:
                std::cout << "Au revoir !\n";
                break;
            default:
                std::cout << "Option invalide.\n";
            }
        } while (choice != 0);
    }

private:
    void addClient() {
        std::string name = getValidatedInput("Nom : ", InputValidator::isValidName);
        std::string firstname = getValidatedInput("Prénom : ", InputValidator::isValidName);
        int age = getValidatedAge();
        std::string address = getValidatedInput("Adresse : ");
        std::string phoneNumber = getValidatedInput("Numéro de téléphone : ", InputValidator::isValidPhoneNumber);
        std::string mail = getValidatedInput("Email : ", InputValidator::isValidEmail);

        Client newClient(name, firstname, age, address, phoneNumber, mail);
        mediaService.addClient(newClient);
        std::cout << "Client ajouté avec succès.\n";
    }

    void removeClient() {
        std::string identifier = getValidatedInput("Entrez le nom, prénom ou email du client à supprimer : ");

        bool removed = mediaService.removeClient(identifier);
        if (removed) {
            std::cout << "Client supprimé avec succès.\n";
        }
        else {
            std::cout << "Client non trouvé.\n";
        }
    }

    void listClients() {
        auto clients = mediaService.listClients();
        if (clients.empty()) {
            std::cout << "Aucun client enregistré.\n";
            return;
        }

        for (const auto& client : clients) {
            std::cout << client.getName() << " " << client.getFirstname()
                << " (" << client.getAge() << " ans)\n";
        }
    }

    void addMedia() {
        int mediaType;
        std::cout << "Type de média :\n";
        std::cout << "1. Livre\n2. Film\n3. Jeu\n";
        std::cout << "Choisissez un type : ";
        std::cin >> mediaType;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::string title = getValidatedInput("Titre : ", InputValidator::isValidMediaTitle);

        switch (mediaType) {
        case 1: {
            std::string isbn = getValidatedInput("ISBN : ", InputValidator::isValidISBN);
            mediaService.addBook(title, isbn);
            break;
        }
        case 2: {
            int supportChoice;
            std::cout << "Support :\n1. Blu-ray\n2. DVD\n";
            std::cin >> supportChoice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            FilmSupport support = (supportChoice == 1) ?
                FilmSupport::BLURAY : FilmSupport::DVD;

            int ageLimit;
            std::cout << "Âge limite : ";
            std::cin >> ageLimit;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            mediaService.addFilm(title, support, ageLimit);
            break;
        }
        case 3: {
            std::string studio = getValidatedInput("Studio : ");

            int pegi;
            std::cout << "PEGI : ";
            std::cin >> pegi;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            int genreChoice;
            std::cout << "Genre :\n1. Action\n2. Aventure\n3. Stratégie\n4. RPG\n5. Sports\n";
            std::cin >> genreChoice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            GameGenre genre;
            switch (genreChoice) {
            case 1: genre = GameGenre::ACTION; break;
            case 2: genre = GameGenre::ADVENTURE; break;
            case 3: genre = GameGenre::STRATEGY; break;
            case 4: genre = GameGenre::RPG; break;
            case 5: genre = GameGenre::SPORTS; break;
            default: genre = GameGenre::ACTION;
            }

            mediaService.addGame(title, studio, pegi, genre);
            break;
        }
        default:
            std::cout << "Type de média invalide.\n";
        }
        std::cout << "Média ajouté avec succès.\n";
    }

    void removeMedia() {
        std::string title = getValidatedInput("Titre du média à supprimer : ", InputValidator::isValidMediaTitle);

        bool removed = mediaService.removeMedia(title);
        if (removed) {
            std::cout << "Média supprimé avec succès.\n";
        }
        else {
            std::cout << "Média non trouvé.\n";
        }
    }

    void listMedia() {
        auto medias = mediaService.listMedia();
        if (medias.empty()) {
            std::cout << "Aucun média enregistré.\n";
            return;
        }

        for (const auto& media : medias) {
            media->displayDetails();
            std::cout << "---\n";
        }
    }

    void checkMediaState() {
        std::string title = getValidatedInput("Titre du média : ", InputValidator::isValidMediaTitle);
        Media* media = mediaService.findMedia(title);

        if (media) {
            std::cout << "État : "
                << (media->isAvailable() ? "Disponible" : "Emprunté")
                << std::endl;
        }
        else {
            std::cout << "Média non trouvé.\n";
        }
    }

    void whoHasBorrowed() {
        std::string title = getValidatedInput("Titre du média : ", InputValidator::isValidMediaTitle);
        Client* client = mediaService.whoHasBorrowed(title);

        if (client) {
            std::cout << "Emprunté par : "
                << client->getName() << " " << client->getFirstname()
                << std::endl;
        }
        else {
            std::cout << "Média non emprunté ou non trouvé.\n";
        }
    }

    void rentMedia() {
        std::string clientName = getValidatedInput("Nom du client : ", InputValidator::isValidName);
        std::string mediaTitle = getValidatedInput("Titre du média : ", InputValidator::isValidMediaTitle);

        bool success = mediaService.rentMedia(clientName, mediaTitle);
        if (success) {
            std::cout << "Média emprunté avec succès.\n";
        }
        else {
            std::cout << "Emprunt impossible (âge, disponibilité ou limite d'emprunts).\n";
        }
    }

    void returnMedia() {
        std::string mediaTitle = getValidatedInput("Titre du média : ", InputValidator::isValidMediaTitle);

        bool success = mediaService.returnMedia(mediaTitle);
        if (success) {
            std::cout << "Média retourné avec succès.\n";
        }
        else {
            std::cout << "Retour impossible.\n";
        }
    }

    void showClientMedia() {
        std::string clientIdentifier = getValidatedInput("Nom, prénom ou email du client : ");

        auto medias = mediaService.showClientMedia(clientIdentifier);
        if (medias.empty()) {
            std::cout << "Aucun média emprunté.\n";
            return;
        }

        for (const auto& media : medias) {
            media->displayDetails();
            std::cout << "---\n";
        }
    }
};

int main() {
    CommandLineInterface cli;
    cli.run();
    return 0;
}