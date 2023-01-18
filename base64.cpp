#include "base64.h"

#include <stdexcept>
#include <iostream>

const char keys[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
};

constexpr std::string generateKeyString() {
    std::string Ks;

    for (size_t i = 0; i < (sizeof(keys) - 1); i++) {
        Ks += keys[i];
        Ks += ", ";
    }

    Ks += keys[63];

    return std::move(Ks);
}

std::string generateError(char symbol) {
    std::string error = "Error: Invalid Symbol \"";
    error += symbol;
    error += ("\" encountered! Valid Symbols: \n" + generateKeyString());
    return error;
}

std::vector<uint8_t> base64::encode(const std::string& b64) {
    std::vector<uint8_t> encoded((size_t)ceil((b64.size() * 6) / 8));

    size_t bit = 0;
    for (size_t i = 0; i < b64.size(); i++) {
        bool cont = false;
        for (size_t j = 0; j < sizeof(keys); j++) {
            if (b64[i] == keys[j]) {
                cont = true;

                size_t index = (bit / 8);
                size_t b = (bit % 8);

                std::cout << "index: " << index << ", " << b << " : " << j << '\n';

                if (index != (encoded.size() - 1)) *(uint16_t*)(&encoded[index]) |= (((uint16_t)j) << b);
                else *(uint8_t*)(&encoded[index]) |= (j << b);

                bit += 6;

                break;
            }
        }
        if (cont) continue;
        std::string error = generateError(b64[i]);
        throw std::invalid_argument(error);
    }

    return std::move(encoded);
}