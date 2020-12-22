#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-bool-literals"

#include "util.h"


bytestr bitstr2bytestr(const bitstr &bitstring) {
    bytestr bytestring;
    for (size_t i = 0; i < bitstring.size(); i += 8) {
        uint8_t byte = 0;
        for (int j = 0; j < 8; ++j)
            byte += (1 << j) * bitstring[i + j];
        bytestring.push_back(byte);
    }
    return bytestring;
}

bitstr bytestr2bitstr(const bytestr &bytestring) {
    bitstr bitstring;
    for (uint8_t byte : bytestring)
        for (int j = 0; j < 8; ++j)
            bitstring.push_back(bitset<8>(byte)[j]);
    return bitstring;
}

bitstr dec2bitstr(const size_t num) {
    bitstr bitstring;
    for (size_t i = num; i != 0; i /= 2)
        if (i % 2)
            bitstring.insert(bitstring.begin(), 1);
        else
            bitstring.insert(bitstring.begin(), 0);
    return bitstring;
}

bitstr dec2bitstr(const size_t n, const size_t num) {
    bitstr binary = dec2bitstr(num);
    bitstr bitstring(n - binary.size());
    bitstring.insert(bitstring.end(), binary.begin(), binary.end());
    return bitstring;
}

bitstr hex2bitstr(const string &hex) {
    return bytestr2bitstr(Botan::hex_decode(hex));
}

string bitstr2hex(const bitstr &bitstring) {
    return Botan::hex_encode(bitstr2bytestr(bitstring));
}

vector<bitstr> partition(const bitstr &bitstring, const size_t m) {
    size_t size = bitstring.size();
    size_t n = ceil(size / m); // size of one part
    vector<bitstr> result(m);
    for (size_t i = 0; i < m; ++i) {
        bitstr temp(n);
        for (size_t j = i; j < n; ++j)
            temp[j] = bitstring[i * n + j];
        result[i] = temp;
    }
    return result;
}

bitstr XOR(const bitstr &bitstring1, const bitstr &bitstring2) {
    size_t l = min(bitstring1.size(), bitstring2.size());
    bitstr result(l);
    for (size_t i = 0; i < l; ++i) {
        result[i] = bitstring1[i] ^ bitstring2[i];
    }
    return result;
}

int ntz(const bitstr &bitstring) {
    int count_zeros = 0;
    for (size_t i = bitstring.size() - 1; i >= 0; --i) {
        if (bitstring[i] == 0)
            count_zeros++;
        else
            break;
    }
    return count_zeros;
}

bitstr shl(const bitstr &bitstring) {
    bitstr result = bitstring;
    rotate(result.begin(), result.begin() + 1, result.end());
    return result;
}

bitstr shr(const bitstr &bitstring) {
    bitstr result = bitstring;
    rotate(result.rbegin(), result.rbegin() + 1, result.rend());
    return result;
}

bitstr mul_by_x(const bitstr &bitstring) {
    bitstr result = shl(bitstring);
    if (bitstring.front()) {
        bitstr xor_by = bitstr(128); // assuming bitstring is a 128-bit string
        xor_by[121] = xor_by[126] = xor_by[127] = xor_by[128] = 1;
        result = XOR(result, xor_by);
    }
    return result;
}

bitstr mul_by_xn(const bitstr &bitstring, const int n) {
    if (n == 0)
        return bitstring;
    else if (n == 1)
        return mul_by_x(bitstring);
    else
        return mul_by_xn(mul_by_x(bitstring), n - 1);
}

bitstr div_by_x(const bitstr &bitstring) {
    bitstr result = shr(bitstring);
    if (bitstring.front()) {
        bitstr xor_by = bitstr(128); // assuming bitstring is a 128-bit string
        xor_by[0] = xor_by[122] = xor_by[127] = xor_by[128] = 1;
        result = XOR(result, xor_by);
    }
    return result;
}

bitstr len(const size_t n, const bitstr &bitstring) {
    return dec2bitstr(n, bitstring.size());
}

bitstr concat(const bitstr &bitstring1, const bitstr &bitstring2) {
    bitstr result = bitstring1;
    if (!bitstring2.empty())
        result.insert(result.end(), bitstring2.begin(), bitstring2.end());
    return result;
}

bitstr first_n_bits(const bitstr &bitstring, const size_t n) {
    if (n > bitstring.size()) {
        cerr << "Message is too short!\n";
        exit(1);
    }
    bitstr result(bitstring.begin(), bitstring.begin() + n);
    return result;
}

bitstr last_n_bits(const bitstr &bitstring, const size_t n) {
    if (n > bitstring.size()) {
        cerr << "Message is too short!\n";
        exit(1);
    }
    bitstr result(bitstring.end() - n, bitstring.end());
    return result;
}


#pragma clang diagnostic pop
