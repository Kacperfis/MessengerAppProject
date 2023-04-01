#include <iostream>
#include <gtest/gtest.h>

#include <Encryption/EncryptionManager.hpp>
#include <Tests/common/commonFixture.hpp>

TEST(EncryptionManagerTests, shouldEncryptAndDecryptTheMessageSuccesfully)
{
    std::shared_ptr<EncryptionManager> encryptionManagerPtr;
    const std::string login = "UserLogin";
    const std::string password = "UserPassword";

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
    const std::string path = "/home/kacper/programming/MessengerAppProject/MessengerApp/Tests/testDatabases/testUserDatabase.txt";

    auto encryptionManagerPtr = std::make_shared<EncryptionManager>(path, key, iv);
    const std::string login = "UserLoginsasdsadsankJklsdajfkljsaldkjasAJKSDJSALKDJSALKDJ1232132131";
    const std::string password = "UserPa12839021738921aslkjnKJLDHASJKHSJKADHKJSAHDKJHA1daskjhjsahAashdjsadhskaj1243KSRssword";

    const std::string login2 = "aaaaaaabbbbbbbcCCCCC";
    const std::string password2 = "123213AAAAAAAAAAdf123";

    encryptionManagerPtr->encryptDataAndSaveToUsersDatabase(login, password);
    encryptionManagerPtr->encryptDataAndSaveToUsersDatabase(login2, password2);
    auto resultVec = encryptionManagerPtr->decryptDataFromUsersDatabase();
    EXPECT_EQ(resultVec.size(), 2);
    EXPECT_EQ(resultVec[0], login + "|" + password + '\n');
    EXPECT_EQ(resultVec[1], login2 + "|" + password2 + '\n');

    clearFile(path);
}
