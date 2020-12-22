#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-bool-literals"

#include "util.h"


bytestr bitstr2bytestr(const bitstr &bitstring) {
    bytestr bytestring;
    for (int i = 0; i < bitstring.size(); i += 8) {
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
            bitstring.push_back(std::bitset<8>(byte)[j]);
    return bitstring;
}

bitstr dec2bitstr(const unsigned long num) {
    bitstr bitstring;
    for (unsigned long i = num; i != 0; i /= 2)
        if (i % 2)
            bitstring.insert(bitstring.begin(), 1);
        else
            bitstring.insert(bitstring.begin(), 0);
    return bitstring;
}

bitstr dec2bitstr(const int n, const unsigned long num) {
    bitstr binary = dec2bitstr(num);
    bitstr bitstring(n - binary.size());
    bitstring.insert(bitstring.end(), binary.begin(), binary.end());
    return bitstring;
}

bitstr hex2bitstr(const std::string &hex) {
    return bytestr2bitstr(Botan::hex_decode(hex));
}

std::string bitstr2hex(const bitstr &bitstring) {
    return Botan::hex_encode(bitstr2bytestr(bitstring));
}

std::vector<bitstr> partition(bitstr bitstring, int m) {
    int size = bitstring.size();
    int n = std::ceil(size / m); // size of one part
    std::vector<bitstr> result(m);
    for (int i = 0; i < m; ++i) {
        bitstr temp(n);
        for (int j = i; j < n; ++j)
            temp[j] = bitstring[i * n + j];
        result[i] = temp;
    }
    return result;
}

bitstr XOR(const bitstr &bitstring1, const bitstr &bitstring2) {
    int l = std::min(bitstring1.size(), bitstring2.size());
    bitstr result(l);
    for (int i = 0; i < l; ++i) {
        result[i] = bitstring1[i] ^ bitstring2[i];
    }
    return result;
}

int ntz(const bitstr &bitstring) {
    int count_zeros = 0;
    for (unsigned long i = bitstring.size() - 1; i >= 0; --i) {
        if (bitstring[i] == 0)
            count_zeros++;
        else
            break;
    }
    return count_zeros;
}

bitstr shl(const bitstr &bitstring) {
    bitstr result = bitstring;
    std::rotate(result.begin(), result.begin() + 1, result.end());
    return result;
}

bitstr shr(const bitstr &bitstring) {
    bitstr result = bitstring;
    std::rotate(result.rbegin(), result.rbegin() + 1, result.rend());
    return result;
}

bitstr mul_by_x(const bitstr &bitstring) {
    bitstr result = shl(bitstring);
    if (bitstring.front() == 1) {
        bitstr xor_by = bitstr(120); // assuming bitstring is a 128-bit string
        xor_by.push_back(1);
        xor_by.push_back(0);
        xor_by.push_back(0);
        xor_by.push_back(0);
        xor_by.push_back(0);
        xor_by.push_back(1);
        xor_by.push_back(1);
        xor_by.push_back(1);
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
    if (bitstring.front() == 1) {
        bitstr xor_by = bitstr(120); // assuming bitstring is a 128-bit string
        xor_by.insert(xor_by.begin(), 1);
        xor_by.push_back(1);
        xor_by.push_back(0);
        xor_by.push_back(0);
        xor_by.push_back(0);
        xor_by.push_back(0);
        xor_by.push_back(1);
        xor_by.push_back(1);
        result = XOR(result, xor_by);
    }
    return result;
}

bitstr len(const int n, const bitstr &bitstring) {
    unsigned long tmp = bitstring.size();
    return dec2bitstr(n, tmp);
}

bitstr concat(const bitstr &bitstring1, const bitstr &bitstring2) {
    bitstr result = bitstring1;
    if (!bitstring2.empty())
        result.insert(result.end(), bitstring2.begin(), bitstring2.end());
    return result;
}

bitstr first_n_bits(const bitstr &bitstring, const int n) {
    if (n > bitstring.size()) {
        std::cerr << "Message is too short!\n";
        exit(1);
    }
    bitstr result(bitstring.begin(), bitstring.begin() + n);
    return result;
}

bitstr last_n_bits(const bitstr &bitstring, const int n) {
    if (n > bitstring.size()) {
        std::cerr << "Message is too short!\n";
        exit(1);
    }
    bitstr result(bitstring.end() - n, bitstring.end());
    return result;
}


#pragma clang diagnostic pop
