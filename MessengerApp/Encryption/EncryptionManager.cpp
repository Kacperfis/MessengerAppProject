#include "EncryptionManager.hpp"
#include <openssl/evp.h>

EncryptionManager::EncryptionManager(const std::string& path, const std::string& key, const std::string iv) : path_(path), key_(key), iv_(iv) {};

void EncryptionManager::encryptDataAndSaveToUsersDatabase(const std::string& login, const std::string& password)
{
    std::string plaintext = login + "|" + password;
    std::string ciphertext = encryptString(plaintext, key_, iv_);
    std::ofstream file(path_, std::ios::out | std::ios::binary | std::ios::app);

    if (file.is_open())
    {
        std::cout << "File opened successfully\n";
        for (const char& c : ciphertext) if (c != '\n') file << c;
        file << '\n';
        if (file.fail() || file.bad()) std::cout << "Error writing to file\n";
        
        file.flush();
        file.close();
    }
    else std::cout << "Error opening file\n";
}

const std::vector<std::string> EncryptionManager::decryptDataFromUsersDatabase()
{
    std::vector<std::string> encryptedContent;
    std::ifstream readFile(path_, std::ios::in | std::ios::binary);
    if (readFile.is_open())
    {
        std::string fileContent((std::istreambuf_iterator<char>(readFile)), std::istreambuf_iterator<char>());
        readFile.close();

        size_t startPosition = 0;
        while (startPosition < fileContent.length())
        {
            size_t endPosition = fileContent.find_first_of('\n', startPosition);
            if (endPosition == std::string::npos)
            {
                endPosition = fileContent.length();
            }
            encryptedContent.push_back(fileContent.substr(startPosition, endPosition - startPosition));
            startPosition = endPosition + 1;
        }
        std::vector<std::string> decryptedContent;
        for (const std::string& encryptedString : encryptedContent)
        {
            std::string decryptedString = decryptString(encryptedString, key_, iv_);
            std::cout << "Decrypted plaintext: " << decryptedString << std::endl;
            decryptedContent.push_back(decryptedString);
        }
        return decryptedContent;
    }
    else std::cout << "Error opening file for reading\n";

    return {};
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
    EVP_DecryptUpdate(ctx, plaintext, &len, (unsigned char*)ciphertext.c_str(), ciphertext.length());
    auto plaintext_len1 = len;

    EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
    auto plaintext_len2 = len;
    EVP_CIPHER_CTX_free(ctx);

    std::string result((char*)plaintext, plaintext_len1 + plaintext_len2);
    delete[] plaintext;
    return result;
}
