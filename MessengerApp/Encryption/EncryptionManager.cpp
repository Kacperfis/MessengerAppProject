#include "EncryptionManager.hpp"
#include <openssl/evp.h>

EncryptionManager::EncryptionManager(const std::string& path, const std::string& key, const std::string iv) : path_(path), key_(key), iv_(iv), logger_("EncryptionManager") {}

void EncryptionManager::encryptDataAndSaveToUsersDatabase(const std::string& login, const std::string& password)
{
    std::string plaintext = login + "|" + password + '\n';
    std::string ciphertext = encryptString(plaintext, key_, iv_);
    std::ofstream file(path_, std::ios::binary | std::ios::app);

    if (file.is_open())
    {
        size_t ciphertext_length = ciphertext.length();
        file.write(reinterpret_cast<const char*>(&ciphertext_length), sizeof(ciphertext_length));
        
        file.write(ciphertext.c_str(), ciphertext.length());
        if (file.fail() || file.bad()) logger_.log(Severity::error, "Error writing to file");
        file.close();
        logger_.log(Severity::info, "Encrypted data succesfully saved to users database");
    }
    else logger_.log(Severity::error, "Error opening file");
}

const std::vector<std::string> EncryptionManager::decryptDataFromUsersDatabase()
{
    std::vector<std::string> decryptedContent;
    std::ifstream infile(path_, std::ios::in | std::ios::binary);
    if (!infile.is_open())
    {
        logger_.log(Severity::error, "Failed to open file: " + path_);
        return {};
    }

    while (!infile.eof())
    {
        size_t ciphertext_length;
        infile.read(reinterpret_cast<char*>(&ciphertext_length), sizeof(ciphertext_length));
        if (infile.eof()) break;

        std::vector<unsigned char> buffer(ciphertext_length);
        infile.read(reinterpret_cast<char*>(buffer.data()), ciphertext_length);
        std::string decrypted = decryptString(std::string(buffer.begin(), buffer.end()), key_, iv_);
        decryptedContent.push_back(decrypted);
    }
    infile.close();
    logger_.log(Severity::info, "Succesfully decrypted data from users database");

    return decryptedContent;
}

// AES-256-CBC encryption
const std::string EncryptionManager::encryptString(const std::string& plaintext, const std::string& key, const std::string& iv)
{
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char*)key.c_str(), (unsigned char*)iv.c_str());

    int ciphertext_len = plaintext.length() + EVP_MAX_BLOCK_LENGTH;
    unsigned char* ciphertext = new unsigned char[ciphertext_len];
    int len;
    EVP_EncryptUpdate(ctx, ciphertext, &len, (unsigned char*)plaintext.c_str(), plaintext.length());
    auto ciphertext_len1 = len;

    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    auto ciphertext_len2 = len;
    EVP_CIPHER_CTX_free(ctx);

    std::string result((char*)ciphertext, ciphertext_len1 + ciphertext_len2);
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
    auto plaintext_len1 = len;

    EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
    auto plaintext_len2 = len;
    EVP_CIPHER_CTX_free(ctx);

    std::string result((char*)plaintext, plaintext_len1 + plaintext_len2);
    delete[] plaintext;
    return result;
}
