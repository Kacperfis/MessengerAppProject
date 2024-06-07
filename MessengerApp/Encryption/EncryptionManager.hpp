#pragma once
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <algorithm>

#include <Common/Logger.hpp>

namespace encryption
{

class EncryptionManager
{
public:
    EncryptionManager(const std::string& path, const std::string& key, const std::string& iv);

    void encryptDataAndSaveToDatabase(const std::string& login, const std::string& password);
    const std::vector<std::string> decryptDataFromDatabase();

    const std::string encryptString(const std::string& plaintext);
    const std::string decryptString(const std::string& ciphertext);
private:
    std::string getCurrentFileIndex(const std::string& path);
    void updateCurrentFileIndex(const std::string& path, const int& currentIndex);

    const std::string path_;
    const std::string key_;
    const std::string iv_;
    Logger logger_;
};

} // namespace encryption
