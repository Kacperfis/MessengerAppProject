#pragma once
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <algorithm>

class EncryptionManager
{
public:
    EncryptionManager(){};
    void encrypt(const std::string& login, const std::string& password);
    const std::string encryptString(const std::string& plaintext, const std::string& key, const std::string& iv);
    const std::string decryptString(const std::string& ciphertext, const std::string& key, const std::string& iv);
};
