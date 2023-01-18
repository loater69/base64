#ifndef BASE64_H
#define BASE64_H

#include <string>
#include <vector>

namespace base64 {
    /*
        @param b64 a string in base64 (expects the string to only include valid base64 characters)
    
        @throws std::invalid_argument if an invalid symbol is encountered
    */
    std::vector<uint8_t> encode(const std::string& b64);
    
    std::string decode(const std::vector<uint8_t>& b64);
}
#endif