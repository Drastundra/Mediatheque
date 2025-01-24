#include "MediaService.h"

#include <iostream>

// Gestion des clients
void MediaService::addClient(const Client& client) {
    clients.push_back(std::make_unique<Client>(client));
}

bool MediaService::removeClient(const std::string& identifier) {
    auto it = std::remove_if(clients.begin(), clients.end(),
        [&identifier](const auto& client) {
            return client->getName() == identifier ||
                client->getFirstname() == identifier ||
                client->getMail() == identifier;
        });

    if (it != clients.end()) {
        clients.erase(it, clients.end());
        return true;
    }
    return false;
}

std::vector<Client> MediaService::listClients() const {
    std::vector<Client> clientList;
    for (const auto& client : clients) {
        clientList.push_back(*client);
    }
    return clientList;
}

Client* MediaService::findClient(const std::string& identifier) {
    auto it = std::find_if(clients.begin(), clients.end(),
        [&identifier](const auto& client) {
            return client->getName() == identifier ||
                client->getFirstname() == identifier ||
                client->getMail() == identifier;
        });

    return it != clients.end() ? it->get() : nullptr;
}

// Ajout de médias
void MediaService::addBook(const std::string& title, const std::string& isbn) {
    medias.push_back(std::make_unique<Book>(title, isbn));
}

void MediaService::addFilm(const std::string& title, FilmSupport support, int ageLimit) {
    medias.push_back(std::make_unique<Film>(title, support, ageLimit));
}

void MediaService::addGame(const std::string& title, const std::string& studio, int pegi, GameGenre genre) {
    medias.push_back(std::make_unique<Game>(title, studio, pegi, genre));
}

bool MediaService::removeMedia(const std::string& title) {
    auto it = std::remove_if(medias.begin(), medias.end(),
        [&title](const auto& media) {
            return media->getTitle() == title;
        });

    if (it != medias.end()) {
        medias.erase(it, medias.end());
        return true;
    }
    return false;
}

std::vector<Media*> MediaService::listMedia() const {
    std::vector<Media*> mediaList;
    for (const auto& media : medias) {
        mediaList.push_back(media.get());
    }
    return mediaList;
}

std::vector<Media*> MediaService::listMediaByState(MediaState state) const {
    std::vector<Media*> mediaList;
    for (const auto& media : medias) {
        if (media->getState() == state) {
            mediaList.push_back(media.get());
        }
    }
    return mediaList;
}

Media* MediaService::findMedia(const std::string& title) {
    auto it = std::find_if(medias.begin(), medias.end(),
        [&title](const auto& media) {
            return media->getTitle() == title;
        });

    return it != medias.end() ? it->get() : nullptr;
}

Client* MediaService::whoHasBorrowed(const std::string& mediaTitle) {
    Media* media = findMedia(mediaTitle);
    return media ? media->getBorrowedBy() : nullptr;
}

bool MediaService::rentMedia(const std::string& clientName, const std::string& mediaTitle) {
    Client* client = findClient(clientName);
    Media* media = findMedia(mediaTitle);

    if (!client || !media || !media->isAvailable()) {
        return false;
    }

    // Vérification de l'âge pour les films
    if (media->getType() == MediaType::FILM) {
        Film* film = dynamic_cast<Film*>(media);
        if (client->getAge() < film->getAgeLimit()) {
            return false;
        }
    }

    // Limite d'emprunt à 5 médias
    if (!client->canBorrow()) {
        return false;
    }

    media->borrow(client);
    client->borrowMedia(media);
    return true;
}

bool MediaService::returnMedia(const std::string& mediaTitle) {
    Media* media = findMedia(mediaTitle);
    if (!media || media->isAvailable()) {
        return false;
    }

    Client* client = media->getBorrowedBy();
    if (client) {
        client->returnMedia(media);
        media->returnMedia();
        return true;
    }
    return false;
}

std::vector<Media*> MediaService::showClientMedia(const std::string& clientIdentifier) {
    Client* client = findClient(clientIdentifier);
    return client ? client->getBorrowedMedia() : std::vector<Media*>();
}