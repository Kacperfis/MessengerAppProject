#include <gtest/gtest.h>
#include <iostream>

#include <Encryption/EncryptionManager.hpp>



TEST(EncryptionManagerTests, shouldEncryptAndDecryptTheMessageSuccesfully)
{
    std::shared_ptr<EncryptionManager> encryptionManagerPtr;
    const std::string login = "login";
    const std::string password = "password";

    // Encryption key and IV
    const std::string key = "0123456789abcdef0123456789abcdef";
    const std::string iv = "0123456789abcdef";
    const std::string text = login + "|" + password;

    auto encryptedMessage = encryptionManagerPtr->encryptString(text, key, iv);
    auto decryptedMessage = encryptionManagerPtr->decryptString(encryptedMessage, key, iv);

    EXPECT_EQ(decryptedMessage, text);
}
