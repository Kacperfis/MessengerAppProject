#include <iostream>
#include <gtest/gtest.h>

#include <Encryption/EncryptionManager.hpp>
#include <Tests/common/commonFixture.hpp>
#include <Common/Config/pathConfig.hpp>

TEST(EncryptionManagerTests, shouldEncryptAndDecryptTheMessageSuccesfully)
{
    Logger::testName_ = "EncryptionManagerTests_shouldEncryptAndDecryptTheMessageSuccesfully";
    const std::string key = "0123456789abcdef0123456789abcdef";
    const std::string iv = "0123456789abcdef";
    const std::string path = config::path::pathPrefix + "MessengerApp/Tests/testDatabases/encryptionManagerDB/";
    auto encryptionManagerPtr = std::make_shared<encryption::EncryptionManager>(path, key, iv);

    const std::string login = "UserLogin";
    const std::string password = "UserPassword";
    const std::string text = login + "|" + password;

    auto encryptedMessage = encryptionManagerPtr->encryptString(text);
    auto decryptedMessage = encryptionManagerPtr->decryptString(encryptedMessage);

    EXPECT_EQ(decryptedMessage, text);
}

TEST(EncryptionManagerTests, shouldEncryptTheDataSaveItToFileAndDecryptFromFileSuccesfully)
{
    Logger::testName_ = "EncryptionManagerTests_shouldEncryptTheDataSaveItToFileAndDecryptFromFileSuccesfully";
    const std::string key = "0123456789abcdef0123456789abcdef";
    const std::string iv = "0123456789abcdef";
    std::cout << "PATH_PREFIX: " << config::path::pathPrefix << std::endl;
    const std::string path = config::path::pathPrefix + "MessengerApp/Tests/testDatabases/encryptionManagerDB/";

    auto encryptionManagerPtr = std::make_shared<encryption::EncryptionManager>(path, key, iv);
    const std::string login = "UserLoginsasdsadsankJklsdajfkljsaldkjasAJKSDJSALKDJSALKDJ1232132131";
    const std::string password = "UserPa12839021738921aslkjnKJLDHASJKHSJKADHKJSAHDKJHA1daskjhjsahAashdjsadhskaj1243KSRssword";

    const std::string login2 = "aaaaaaabbbbbbbcCCCCC";
    const std::string password2 = "123213AAAAAAAAAAdf123";

    encryptionManagerPtr->encryptDataAndSaveToDatabase(login, password);
    encryptionManagerPtr->encryptDataAndSaveToDatabase(login2, password2);
    auto resultVec = encryptionManagerPtr->decryptDataFromDatabase();
    EXPECT_EQ(resultVec.size(), 2);
    EXPECT_EQ(resultVec[0], login + "|" + password);
    EXPECT_EQ(resultVec[1], login2 + "|" + password2);

    clearAllFilesFromFolder(path);
    setDefaultValueForIndexFile(config::path::pathPrefix + "MessengerApp/Tests/testDatabases/encryptionManagerDB/", "0");
}
