#ifndef MEDIA_SERVICE_H
#define MEDIA_SERVICE_H

#include "Client.h"
#include "Media.h"
#include "Book.h"
#include "Film.h"
#include "Game.h"

#include <vector>
#include <memory>
#include <algorithm>

class MediaService {
private:
    std::vector<std::unique_ptr<Client>> clients;
    std::vector<std::unique_ptr<Media>> medias;

public:
    // Gestion des clients
    void addClient(const Client& client);
    bool removeClient(const std::string& identifier);
    std::vector<Client> listClients() const;
    Client* findClient(const std::string& identifier);

    // Gestion des médias
    void addBook(const std::string& title, const std::string& isbn);
    void addFilm(const std::string& title, FilmSupport support, int ageLimit);
    void addGame(const std::string& title, const std::string& studio, int pegi, GameGenre genre);

    bool removeMedia(const std::string& title);
    std::vector<Media*> listMedia() const;
    std::vector<Media*> listMediaByState(MediaState state) const;

    Media* findMedia(const std::string& title);
    Client* whoHasBorrowed(const std::string& mediaTitle);

    // Opérations d'emprunt et retour
    bool rentMedia(const std::string& clientName, const std::string& mediaTitle);
    bool returnMedia(const std::string& mediaTitle);
    std::vector<Media*> showClientMedia(const std::string& clientIdentifier);
};

#endif // MEDIA_SERVICE_H