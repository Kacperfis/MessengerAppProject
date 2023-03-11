#include <gtest/gtest.h>
#include <iostream>

#include <Encryption/EncryptionManager.hpp>

void clearFile(const std::string& path)
{
    std::ofstream file(path);
    file << "";
}

TEST(EncryptionManagerTests, shouldEncryptAndDecryptTheMessageSuccesfully)
{
    std::shared_ptr<EncryptionManager> encryptionManagerPtr;
    const std::string login = "login";
    const std::string password = "password";

    const std::string key = "0123456789abcdef0123456789abcdef";
    const std::string iv = "0123456789abcdef";
    const std::string text = login + "|" + password;

    auto encryptedMessage = encryptionManagerPtr->encryptString(text, key, iv);
    auto decryptedMessage = encryptionManagerPtr->decryptString(encryptedMessage, key, iv);

    EXPECT_EQ(decryptedMessage, text);
}

TEST(EncryptionManagerTests, shouldEncryptTheDataSaveItToFileAndDecryptFromFileSuccesfully)
{
    const std::string key = "0123456789abcdef0123456789abcdef";
    const std::string iv = "0123456789abcdef";
    const std::string path = "/home/kacper/programming/MessengerAppProject/MessengerApp/Tests/testUserDatabase/testUserDatabase.txt";

    auto encryptionManagerPtr = std::make_shared<EncryptionManager>(path, key, iv);
    const std::string login = "UserLogin";
    const std::string password = "UserPassword";

    encryptionManagerPtr->encryptDataAndSaveToUsersDatabase(login, password);
    auto resultVec = encryptionManagerPtr->decryptDataFromUsersDatabase();
    EXPECT_EQ(resultVec.size(), 1);
    EXPECT_EQ(resultVec.front(), login + "|" + password);
    clearFile(path);
}
