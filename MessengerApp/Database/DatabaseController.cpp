#include "DatabaseController.hpp"
#include <vector>
#include <ranges>

DatabaseController::DatabaseController(const std::string& path) : encryptionManagerPtr_(
    std::make_unique<EncryptionManager>(path, "0123456789abcdef0123456789abcdef", "0123456789abcdef")) {}

void DatabaseController::LoadDatabase()
{
    const auto usersData = encryptionManagerPtr_->decryptDataFromUsersDatabase();
    for(const auto& word : usersData)
    {
        for (uint32_t i = 0; i < word.length(); i++)
        {
            if (word[i] == '|')
            {
                registeredUsersData_.insert(std::make_pair<std::string, std::string>(word.substr(0, i), word.substr(i+1, word.length()-1)));
                break;
            }
        }
    }
}

void DatabaseController::registerUser(const std::string& login, const std::string& password)
{
    encryptionManagerPtr_->encryptDataAndSaveToUsersDatabase(login, password);
}

const std::map<std::string, std::string> DatabaseController::getRegisteredUsersData() const
{
    return registeredUsersData_;
}
