#include "EncryptionManager.hpp"
#include <openssl/evp.h>

void EncryptionManager::encrypt(const std::string& login, const std::string& password)
{
    // Plaintext to encrypt and decrypt
    std::string plaintext = login + "|" + password;

    // Encryption key and IV
    std::string key = "0123456789abcdef0123456789abcdef";
    std::string iv = "0123456789abcdef";

    // Encrypt the plaintext

    std::string ciphertext = encryptString(plaintext, key, iv);
    std::cout << "Ciphertext: " << ciphertext << std::endl;

    // Save the encrypted content to a file
    std::string path = "/home/kacper/programming/MessengerAppProject/MessengerApp/Database/registeredUsersData.txt";
    std::ofstream file(path, std::ios::out | std::ios::binary | std::ios::app);

    if (file.is_open())
    {
        std::cout << "File opened successfully\n";
        std::cout << "Ciphertext length: " << ciphertext.length() << std::endl;

        //file.write(reinterpret_cast<const char*>(ciphertext.c_str()), ciphertext.length());
        for (const char& c : ciphertext) 
        {
            if (c != '\n') {
                file << c;
            }
        }
        file << '\n';
        
        if (file.fail() || file.bad()) {
            std::cout << "Error writing to file\n";
        }
        file.flush();
        file.close();
    }
    else {
        std::cout << "Error opening file\n";
    }

/////

    // Read the encrypted content from the file and decrypt it
    std::vector<std::string> encrypted_content;
    std::ifstream read_file(path, std::ios::in | std::ios::binary);
    if (read_file.is_open()) {
        std::cout << "File opened successfully for reading\n";

        // Read the ciphertext from the file and store it in a string
        std::string file_content((std::istreambuf_iterator<char>(read_file)), std::istreambuf_iterator<char>());
        std::cout << "File content: " << file_content << std::endl;

        read_file.close();

        // Split the file content into individual encrypted strings
        size_t start_pos = 0;
        while (start_pos < file_content.length()) {
            size_t end_pos = file_content.find_first_of('\n', start_pos);
            if (end_pos == std::string::npos) {
                end_pos = file_content.length();
            }
            encrypted_content.push_back(file_content.substr(start_pos, end_pos - start_pos));
            start_pos = end_pos + 1;
        }

        // Decrypt the ciphertext
        std::vector<std::string> decrypted_content;
        for (const std::string& encrypted_str : encrypted_content) {

            std::string decrypted_str = decryptString(encrypted_str, key, iv);
            std::cout << "Decrypted plaintext: " << decrypted_str << std::endl;
            decrypted_content.push_back(decrypted_str);
        }

        // Use the decrypted content as needed
        // ...
    }
    else {
        std::cout << "Error opening file for reading\n";
    }
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
