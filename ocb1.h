#ifndef PAZI2_OCB1_H
#define PAZI2_OCB1_H

#include <botan/aes.h>
#include <botan/hex.h>

#include "util.h"


#define TAU 64

using namespace std;


// block cipher (AES128)
bitstr E(const bytestr &key, const bitstr &open_text);
bitstr D(const bytestr &key, const bitstr &ciphertext);

// encryption mode proper (OCB1)
std::string encrypt(const std::string &key, const std::string &nonce, const std::string &message);
std::string decrypt(const std::string &key, const std::string &nonce, const std::string &ciphertext);


#endif //PAZI2_OCB1_H
