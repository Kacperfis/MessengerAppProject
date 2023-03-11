#include <gtest/gtest.h>
#include <iostream>

#include <Encryption/EncryptionManager.hpp>

TEST(EncryptionManagerTests, shouldEncryptTheMessageSuccesfully)
{
    auto encryptionManagerPtr = std::make_shared<EncryptionManager>();
    std::string login = "onesadsadsadsadsad";
    std::string password = "twoasdsadsadasdsada\n";
    encryptionManagerPtr->encrypt(login, password);
}

// TEST(EncryptionManagerTests, shouldDecryptTheMessageSuccesfully)
// {
    
// }

// TEST(EncryptionManagerTests, shouldEncryptAndDecryptTheMessageSuccesfully)
// {
    
// }