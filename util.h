#ifndef PAZI2_UTIL_H
#define PAZI2_UTIL_H

#include <bitset>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <botan/hex.h>


#define bitstr std::vector<bool>
#define bytestr std::vector<uint8_t>

using namespace std;


// convert bitstring to bytestring
bytestr bitstr2bytestr(const bitstr &bitstring);

// convert bytestring to bitstring
bitstr bytestr2bitstr(const bytestr &bytestring);

// convert from decimal to binary
bitstr dec2bitstr(std::size_t num);

// convert from decimal to binary with bitstring length n
bitstr dec2bitstr(size_t n, std::size_t num);

// convert from hexadecimal to binary
bitstr hex2bitstr(const std::string &hex);

// convert from binary to hexadecimal
std::string bitstr2hex(const bitstr &bitstring);

// split bitstring into m almost equal parts
std::vector<bitstr> partition(const bitstr &bitstring, size_t m);

// perform bitwise XOR of two bitstrings
bitstr XOR(const bitstr &bitstring1, const bitstr &bitstring2);

// get the number of trailing zeros in bitstring
int ntz(const bitstr &bitstring);

// shift bitstring left by 1 bit
bitstr shl(const bitstr &bitstring);

// shift bitstring right by 1 bit
bitstr shr(const bitstr &bitstring);

// multiply bitstring by x
bitstr mul_by_x(const bitstr &bitstring);

// multiply bitstring by x^n
bitstr mul_by_xn(const bitstr &bitstring, int n);

// multiply bitstring by x^(-1)
bitstr div_by_x(const bitstr &bitstring);

// get length of bitstring (binary)
bitstr len(size_t n, const bitstr &bitstring);

// concatenate two bitstrings
bitstr concat(const bitstr &bitstring1, const bitstr &bitstring2);

// get first n bits in bitstring
bitstr first_n_bits(const bitstr &bitstring, size_t n);

// get last n bits in bitstring
bitstr last_n_bits(const bitstr &bitstring, size_t n);


#endif //PAZI2_UTIL_H
