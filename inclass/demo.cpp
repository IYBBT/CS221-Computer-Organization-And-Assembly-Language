
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    for (int i = 0; i < argc; ++i)
        std::cout << argv[i] << std::endl;

    int a = 25;         // 25 in decimal
    int b = 0b11001;    // 25 in binary
    int c = 0x19;       // 25 in hexadecimal
    int d = 031;        // 25 in octal

    std::cout << std::dec << a << ", " << b << ", " << c << ", " << d << std::endl;
    std::cout << std::hex << a << ", " << b << ", " << c << ", " << d << std::endl;
    std::cout << std::oct << a << ", " << b << ", " << c << ", " << d << std::endl;

    char upper = 65;                    // 65 = 'A'
    std::cout << upper << std::endl;
    
    upper |= 32;                        // 32 conversion from upper to lower,   (65 | 35) = (01000001 | 00100000) = 01100001 = 'a'
    std::cout << upper << std::endl;

    upper ^= 32;                        // (97 ^ 32) = (01100001 ^ 00100000) = 01000001 = 'A'
    std::cout << upper << std::endl;

    return 0;
}
