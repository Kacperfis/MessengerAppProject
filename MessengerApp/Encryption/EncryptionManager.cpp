#include "EncryptionManager.hpp"
#include <openssl/evp.h>

EncryptionManager::EncryptionManager(const std::string& path, const std::string& key, const std::string iv) : path_(path), key_(key), iv_(iv), logger_("EncryptionManager") {}

void EncryptionManager::encryptDataAndSaveToUsersDatabase(const std::string& login, const std::string& password)
{
    std::string plaintext = login + "|" + password;
    std::string ciphertext = encryptString(plaintext, key_, iv_);
    auto currentIndex = std::stoi(getCurrentFileIndex(path_)) + 1;
    std::ofstream file(path_ + "data" + std::to_string(currentIndex) + ".txt", std::ios::binary | std::ios::app);

    if (file.is_open())
    {
        file.write(ciphertext.data(), ciphertext.size());
        if (file.fail() || file.bad()) logger_.log(Severity::error, "Error writing to file");
        file.close();
        updateCurrentFileIndex(path_, currentIndex);
        logger_.log(Severity::info, "Encrypted data succesfully saved to users database");
    }
    else logger_.log(Severity::error, "Error opening file");
}

const std::vector<std::string> EncryptionManager::decryptDataFromUsersDatabase()
{
    std::vector<std::string> decryptedContent;
    auto currentNumberOfFiles = std::stoi(getCurrentFileIndex(path_));
    for (int counter = 1; counter <= currentNumberOfFiles; counter++)
    {
        std::ifstream infile(path_ + "data" + std::to_string(counter) + ".txt", std::ios::in | std::ios::binary);
        if (!infile.is_open()) {
            logger_.log(Severity::error, "Failed to open file: " + path_ + "data" + std::to_string(counter));
            return {};
        }

        infile.seekg(0, std::ios::end);
        std::streamsize size = infile.tellg();
        infile.seekg(0, std::ios::beg);

        std::vector<char> buffer(size);
        if (!infile.read(buffer.data(), size)) {
            logger_.log(Severity::error, "Error reading from the file");
            return {};
        }

        std::string ciphertext(buffer.begin(), buffer.end());
        std::string decrypted = decryptString(ciphertext, key_, iv_);
        decryptedContent.push_back(decrypted);

        infile.close();
    }

    logger_.log(Severity::info, "Successfully decrypted data from users database");
    return decryptedContent;
}

std::string EncryptionManager::getCurrentFileIndex(const std::string& path)
{
    std::string index = "";
    std::ifstream indexFile(path + "dataIndex.txt");

    if (indexFile.is_open())
    {
        if (getline(indexFile, index)) logger_.log(Severity::info, "successfully read current index: " + index);
        else logger_.log(Severity::error, "cannot read current index from file");
    }
    else logger_.log(Severity::error, "Error opening index file");
    indexFile.close();

    return index;
}

void EncryptionManager::updateCurrentFileIndex(const std::string& path, const int& currentIndex)
{
    std::ofstream indexFile(path + "dataIndex.txt", std::ios::trunc);

    if (indexFile.is_open())
    {
        indexFile << currentIndex;
        logger_.log(Severity::info, "Successfully updated current Index of file");
        indexFile.close();
    }
    else logger_.log(Severity::error, "Error opening index file to update");
}

const std::string EncryptionManager::encryptString(const std::string& plaintext, const std::string& key, const std::string& iv)
{
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char*)key.c_str(), (unsigned char*)iv.c_str());

    int ciphertext_len = plaintext.length() + EVP_MAX_BLOCK_LENGTH;
    unsigned char* ciphertext = new unsigned char[ciphertext_len];
    int len;
    EVP_EncryptUpdate(ctx, ciphertext, &len, (unsigned char*)plaintext.c_str(), plaintext.length());
    int final_len;
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &final_len);
    EVP_CIPHER_CTX_free(ctx);

    std::string result(reinterpret_cast<char*>(ciphertext), len + final_len); // construct the string using the full size
    delete[] ciphertext;
    return result;
}

const std::string EncryptionManager::decryptString(const std::string& ciphertext, const std::string& key, const std::string& iv)
{
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char*)key.c_str(), (unsigned char*)iv.c_str());

    int plaintext_len = ciphertext.length() + EVP_MAX_BLOCK_LENGTH;
    unsigned char* plaintext = new unsigned char[plaintext_len];
    int len;
    EVP_DecryptUpdate(ctx, plaintext, &len, (unsigned char*)ciphertext.data(), ciphertext.length());
    int final_len;
    EVP_DecryptFinal_ex(ctx, plaintext + len, &final_len);
    EVP_CIPHER_CTX_free(ctx);

    std::string result(reinterpret_cast<char*>(plaintext), len + final_len); // construct the string using the full size
    delete[] plaintext;
    return result;
}
