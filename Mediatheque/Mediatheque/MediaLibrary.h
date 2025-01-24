#pragma once

#include <unordered_map>
#include <memory>
#include <vector>
#include "Media.h"
#include "Client.h"

class MediaLibrary {
private:
    std::unordered_map<std::string, std::unique_ptr<Client>> clients;
    std::unordered_map<std::string, std::unique_ptr<Media>> media;

    Client* findClient(const std::string& identifier);
    Media* findMedia(const std::string& mediaType, const std::string& title);

public:
    bool addClient(const std::string& name, const std::string& firstname, int age,
        const std::string& address, const std::string& phoneNumber,
        const std::string& mail);

    bool removeClient(const std::string& identifier);
    std::vector<const Client*> listClients() const;

    bool addMedia(const std::string& mediaType, const std::vector<std::string>& args);
    bool removeMedia(const std::string& mediaType, const std::string& title);
    std::vector<const Media*> listMedia(const std::string& state = "") const;

    const Media* getMediaState(const std::string& mediaType, const std::string& title) const;
    std::string getMediaBorrower(const std::string& mediaType, const std::string& title) const;

    bool rentMedia(const std::string& clientIdentifier, const std::string& mediaType, const std::string& title);
    bool returnMedia(const std::string& mediaType, const std::string& title);

    std::vector<const Media*> getClientMedia(const std::string& clientIdentifier) const;
};
