#include <iostream>
#include "ocb1.h"

using namespace std;

int main() {
    const string K = "000102030405060708090A0B0C0D0E0F";
    const string N = "BBAA99887766554433221100";
    const string M = "56BA4D86FC8BD656CEAD";

    cout << "Original string:\n " << M << '\n';

    string encrypted = encrypt(K, N, M);

    cout << "Encrypted string:\n " << encrypted << '\n';
    // output: ED10D40E8BED8312FD8FBBAA998877665544

    string decrypted = decrypt(K, N, encrypted);

    cout << "Decrypted string:\n " << decrypted << '\n';
    // output: 56BA4D86FC8BD656CEAD
}
