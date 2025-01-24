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
        std::cout << "\n--- M�diath�que - Menu Principal ---\n";
        std::cout << "1. Ajouter un client\n";
        std::cout << "2. Supprimer un client\n";
        std::cout << "3. Lister les clients\n";
        std::cout << "4. Ajouter un m�dia\n";
        std::cout << "5. Supprimer un m�dia\n";
        std::cout << "6. Lister les m�dias\n";
        std::cout << "7. V�rifier l'�tat d'un m�dia\n";
        std::cout << "8. Qui a emprunt� un m�dia\n";
        std::cout << "9. Emprunter un m�dia\n";
        std::cout << "10. Retourner un m�dia\n";
        std::cout << "11. M�dias emprunt�s par un client\n";
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
            std::cout << "Entr�e invalide. R�essayez.\n";
        }
    }

    int getValidatedAge() {
        int age;
        while (true) {
            std::cout << "�ge : ";
            std::cin >> age;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (InputValidator::isValidAge(age)) {
                return age;
            }
            std::cout << "�ge invalide. Doit �tre entre 0 et 120.\n";
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
        std::string firstname = getValidatedInput("Pr�nom : ", InputValidator::isValidName);
        int age = getValidatedAge();
        std::string address = getValidatedInput("Adresse : ");
        std::string phoneNumber = getValidatedInput("Num�ro de t�l�phone : ", InputValidator::isValidPhoneNumber);
        std::string mail = getValidatedInput("Email : ", InputValidator::isValidEmail);

        Client newClient(name, firstname, age, address, phoneNumber, mail);
        mediaService.addClient(newClient);
        std::cout << "Client ajout� avec succ�s.\n";
    }

    void removeClient() {
        std::string identifier = getValidatedInput("Entrez le nom, pr�nom ou email du client � supprimer : ");

        bool removed = mediaService.removeClient(identifier);
        if (removed) {
            std::cout << "Client supprim� avec succ�s.\n";
        }
        else {
            std::cout << "Client non trouv�.\n";
        }
    }

    void listClients() {
        auto clients = mediaService.listClients();
        if (clients.empty()) {
            std::cout << "Aucun client enregistr�.\n";
            return;
        }

        for (const auto& client : clients) {
            std::cout << client.getName() << " " << client.getFirstname()
                << " (" << client.getAge() << " ans)\n";
        }
    }

    void addMedia() {
        int mediaType;
        std::cout << "Type de m�dia :\n";
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
            std::cout << "�ge limite : ";
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
            std::cout << "Genre :\n1. Action\n2. Aventure\n3. Strat�gie\n4. RPG\n5. Sports\n";
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
            std::cout << "Type de m�dia invalide.\n";
        }
        std::cout << "M�dia ajout� avec succ�s.\n";
    }

    void removeMedia() {
        std::string title = getValidatedInput("Titre du m�dia � supprimer : ", InputValidator::isValidMediaTitle);

        bool removed = mediaService.removeMedia(title);
        if (removed) {
            std::cout << "M�dia supprim� avec succ�s.\n";
        }
        else {
            std::cout << "M�dia non trouv�.\n";
        }
    }

    void listMedia() {
        auto medias = mediaService.listMedia();
        if (medias.empty()) {
            std::cout << "Aucun m�dia enregistr�.\n";
            return;
        }

        for (const auto& media : medias) {
            media->displayDetails();
            std::cout << "---\n";
        }
    }

    void checkMediaState() {
        std::string title = getValidatedInput("Titre du m�dia : ", InputValidator::isValidMediaTitle);
        Media* media = mediaService.findMedia(title);

        if (media) {
            std::cout << "�tat : "
                << (media->isAvailable() ? "Disponible" : "Emprunt�")
                << std::endl;
        }
        else {
            std::cout << "M�dia non trouv�.\n";
        }
    }

    void whoHasBorrowed() {
        std::string title = getValidatedInput("Titre du m�dia : ", InputValidator::isValidMediaTitle);
        Client* client = mediaService.whoHasBorrowed(title);

        if (client) {
            std::cout << "Emprunt� par : "
                << client->getName() << " " << client->getFirstname()
                << std::endl;
        }
        else {
            std::cout << "M�dia non emprunt� ou non trouv�.\n";
        }
    }

    void rentMedia() {
        std::string clientName = getValidatedInput("Nom du client : ", InputValidator::isValidName);
        std::string mediaTitle = getValidatedInput("Titre du m�dia : ", InputValidator::isValidMediaTitle);

        bool success = mediaService.rentMedia(clientName, mediaTitle);
        if (success) {
            std::cout << "M�dia emprunt� avec succ�s.\n";
        }
        else {
            std::cout << "Emprunt impossible (�ge, disponibilit� ou limite d'emprunts).\n";
        }
    }

    void returnMedia() {
        std::string mediaTitle = getValidatedInput("Titre du m�dia : ", InputValidator::isValidMediaTitle);

        bool success = mediaService.returnMedia(mediaTitle);
        if (success) {
            std::cout << "M�dia retourn� avec succ�s.\n";
        }
        else {
            std::cout << "Retour impossible.\n";
        }
    }

    void showClientMedia() {
        std::string clientIdentifier = getValidatedInput("Nom, pr�nom ou email du client : ");

        auto medias = mediaService.showClientMedia(clientIdentifier);
        if (medias.empty()) {
            std::cout << "Aucun m�dia emprunt�.\n";
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