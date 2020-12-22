#include "ocb1.h"


bitstr E(const bytestr &key, const bitstr &open_text) {
    unique_ptr<Botan::BlockCipher> cipher(Botan::BlockCipher::create("AES-128"));
    bytestr block = bitstr2bytestr(open_text);
    cipher->set_key(key);
    cipher->encrypt(block);
    return bytestr2bitstr(block);
}

bitstr D(const bytestr &key, const bitstr &ciphertext) {
    unique_ptr<Botan::BlockCipher> cipher(Botan::BlockCipher::create("AES-128"));
    bytestr block = bitstr2bytestr(ciphertext);
    cipher->set_key(key);
    cipher->decrypt(block);
    return bytestr2bitstr(block);
}

string encrypt(const string &key, const string &nonce, const string &message) {
    bytestr K = Botan::hex_decode(key);
    bitstr N = hex2bitstr(nonce);
    bitstr M_whole = hex2bitstr(message);

    size_t n = N.size();
    size_t m = max(1UL, (size_t) ceil((double) M_whole.size() / n));
    vector<bitstr> M = partition(M_whole, m);

    bitstr L = E(K, bitstr(n));

    bitstr R = E(K, XOR(N, L));

    vector<bitstr> Z(m);
    Z[0] = XOR(L, R);
    for (size_t i = 1; i < m; ++i)
        Z[i] = XOR(Z[i - 1], mul_by_xn(L, ntz(dec2bitstr(i + 1))));

    vector<bitstr> C(m);
    for (size_t i = 0; i < m - 1; ++i)
        C[i] = XOR(E(K, XOR(M[i], Z[i])), Z[i]);

    bitstr Xm = XOR(XOR(len(n, M.back()), div_by_x(L)), Z.back());

    bitstr Ym = E(K, Xm);

    C.back() = XOR(Ym, M.back());

    bitstr C_whole = C[0];
    if (m > 1)
        for (size_t i = 1; i < m; ++i)
            C_whole = concat(C_whole, C[i]);

    bitstr checksum = M[0];
    if (m > 1)
        for (size_t i = 1; i < m - 1; ++i)
            checksum = XOR(checksum, M[i]);
    checksum = XOR(XOR(checksum, concat(C.back(), bitstr(n - C.back().size()))), Ym);

    bitstr T = first_n_bits(E(K, XOR(checksum, Z.back())), TAU);

    bitstr C_fancy = concat(C_whole, T);
    return bitstr2hex(C_fancy);
}

string decrypt(const string &key, const string &nonce, const string &ciphertext) {
    bytestr K = Botan::hex_decode(key);
    bitstr N = hex2bitstr(nonce);
    bitstr C_fancy = hex2bitstr(ciphertext);

    size_t n = N.size();
    size_t size = C_fancy.size();
    if (size < TAU) return "";
    bitstr C_whole = first_n_bits(C_fancy, size - TAU);
    bitstr T = last_n_bits(C_fancy, TAU);
    size_t m = max(1UL, (size_t) ceil((double) C_whole.size() / n));
    vector<bitstr> C = partition(C_whole, m);

    bitstr L = E(K, bitstr(n));

    bitstr R = E(K, XOR(N, L));

    vector<bitstr> Z(m);
    Z[0] = XOR(L, R);
    for (size_t i = 1; i < m; ++i)
        Z[i] = XOR(Z[i - 1], mul_by_xn(L, ntz(dec2bitstr(i + 1))));

    vector<bitstr> M(m);
    for (size_t i = 0; i < m - 1; ++i)
        M[i] = XOR(D(K, XOR(C[i], Z[i])), Z[i]);

    bitstr Xm = XOR(XOR(len(n, C.back()), div_by_x(L)), Z.back());

    bitstr Ym = E(K, Xm);

    M.back() = XOR(Ym, C.back());

    bitstr M_whole = M[0];
    if (m > 1)
        for (size_t i = 1; i < m; ++i)
            M_whole = concat(M_whole, M[i]);

    bitstr checksum = M[0];
    if (m > 1)
        for (size_t i = 1; i < m - 1; ++i)
            checksum = XOR(checksum, M[i]);
    checksum = XOR(XOR(checksum, concat(C.back(), bitstr(n - C.back().size()))), Ym);

    bitstr TT = first_n_bits(E(K, XOR(checksum, Z.back())), TAU);

    if (T == TT)
        return bitstr2hex(M_whole);
    else
        return "";
}
