#pragma once
#include <memory>
#include <string>
#include <map>
#include <Encryption/EncryptionManager.hpp>

class DatabaseController
{
public:
    DatabaseController(const std::string& path);
    void LoadDatabase();
    void registerUser(const std::string& login, const std::string& password);
    const std::map<std::string, std::string> getRegisteredUsersData() const;
private:
    const std::unique_ptr<EncryptionManager> encryptionManagerPtr_;
    std::map<std::string, std::string> registeredUsersData_;
    std::map<std::string, std::string> registeredAdminsData_;
};