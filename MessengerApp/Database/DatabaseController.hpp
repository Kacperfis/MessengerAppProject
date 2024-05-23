#pragma once
#include <memory>
#include <string>
#include <map>
#include <Encryption/EncryptionManager.hpp>
#include <../MessengerInterfaces/IDatabaseController.hpp>

namespace database
{

class DatabaseController : public interface::IDatabaseController
{
public:
    explicit DatabaseController(const std::string& path);
    void LoadDatabase() override;
    void registerUser(const std::string& login, const std::string& password) override;
    const std::map<std::string, std::string> getRegisteredUsersData() const override;
private:
    const std::unique_ptr<encryption::EncryptionManager> encryptionManagerPtr_;
    std::map<std::string, std::string> registeredUsersData_;
    std::map<std::string, std::string> registeredAdminsData_;
    Logger logger_;
};

} // namespace database
