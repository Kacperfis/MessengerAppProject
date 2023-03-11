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
    std::string encrypt_string(const std::string& plaintext, const std::string& key, const std::string& iv);
    std::string decrypt_string(const std::string& ciphertext, const std::string& key, const std::string& iv);
};
