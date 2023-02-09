
#include <iostream>

#define ZERO 0x0
#define ONE 0x1

#define MAX_SHORT 0xFFFF
#define MAX_BYTE 0xFF
#define MAX_NIBBLE 0xF

#define SHORT_SIZE 0x10
#define BYTE_SIZE 0x8
#define NIBBLE_SIZE 0x4

typedef struct Bitset
{
    Bitset() 
    {
        bits = ZERO;    // Sets the bits all to 0
    }

    Bitset(unsigned short the_bits)
    {
        bits = the_bits;    // Sets the bits to the input bits
    }

    bool none()
    {
        return !(bits | ZERO);  // Returns true if the bits are all 0
    }

    bool any()
    {
        return bits;    // Returns true if any of the bits are 1
    }

    bool all()
    {
        return !(bits ^ MAX_SHORT); // Returns true if all of the bits are 1
    }

    void flip()
    {
        bits = ~bits;   // Flips all of the bits from a 1 to a 0 and vice versa
    }

    bool get(int index)
    {
        unsigned short temp = bits >> index;    // Creates a temporary variable and bit shifts it so the bit at the index is the first bit
        return temp & ONE;                      // Returns true if the first bit is a 1
    }

    void set()
    {
        bits |= MAX_SHORT;  // Sets all of the bits to 1
    }

    void set(int index)
    {
        unsigned short temp = bits >> index;    // Creates a temporary variable and bit shifts it so the bit at the index is the first bit
        temp |= ONE;                            // Sets the first bit to a 1
        temp <<= index;                         // Bit shifts the variable back
        bits |= temp;                           // Sets the bit that was set to a 1 in the stored bits
    }

    void clear()
    {
        bits &= ZERO;   // Sets all the bits to 0
    }

    void clear(int index)
    {
        unsigned short temp = ONE << index; // Creates a temporary variable equal to one and bit shifts it so the bit lines up to the bit that needs to be cleared
        if (bits & temp)                    // Checks if the bit at the index is a 1
        {
            bits ^= temp;                   // If the bit that needs to be cleared is a 1 then it is fliped to a 0
        }
    }

    void swap()
    {
        unsigned short f = (bits & MAX_BYTE) << BYTE_SIZE;      // Gets the first byte and shifts it accordingly
        unsigned short s = (bits & (MAX_BYTE << BYTE_SIZE));    // Gets the second byte
        s >>= BYTE_SIZE;                                        // Shifts the second byte accordingly
        bits = f | s;                                           // Sets the stored bits to the first and second bytes swapped ex. 0xF76E --> 0x6EF7
    }

    void swapHi()
    {
        unsigned short f = (bits & (MAX_NIBBLE << (NIBBLE_SIZE * 2)));  // Gets the first nibble of the second byte
        unsigned short s = (bits & (MAX_NIBBLE << (NIBBLE_SIZE * 3)));  // Gets the second nibble of the second byte
        f <<= NIBBLE_SIZE;                                              // Shifts the first nibble accordingly
        s >>= NIBBLE_SIZE;                                              // Shifts the second nibble accordingly
        bits &= ~(MAX_BYTE << BYTE_SIZE);                               // Clears all the bits in the second byte
        bits |= (f | s);                                                // Sets all the bits in the second byte to the first nibble then the second nibble ex. 0XF76E --> 0x7F6E
    }

    void swapLo()
    {
        unsigned short f = (bits & (MAX_NIBBLE));                   // Gets the first nibble of the first byte
        unsigned short s = (bits & (MAX_NIBBLE << NIBBLE_SIZE));    // Gets the second nibble of the first byte
        f <<= NIBBLE_SIZE;                                          // Shifts the first nibble accordingly
        s >>= NIBBLE_SIZE;                                          // Shifts the second nibble accordingly
        bits &= ~MAX_BYTE;                                          // Clears all the bits in the second byte
        bits |= (f | s);                                            // Sets all the bits in the first byte to the first nibble then the second nibble ex. 0xF76E --> 0xF7E6
    }

    bool isPow2()
    {
        return !(bits & (bits - 1));    // Compares the current number with the number preceding, if the current number is a power of 2 the bitwise & will return 0, otherwise it will return non-zero
    }

    void clearLast1()
    {
        bits &= (bits - 1); // Compares the current number with the number preceding, and will clear the rightmost 1 in the set
    }

    int count()
    {
        unsigned short temp = bits;             // Creates a temprorary variable
        int count = 0;                          // Initializes the count
        for (int i = 0; i < SHORT_SIZE; ++i)    // Iterates over all the bits in the short
        {
            if (temp & ONE)                     // Checks if the first bit is a 1
            {
                ++count;                        // If the first bit is a 1 then increment the count
            }
            temp >>= ONE;                       // Bit shift the temporary variable
        }
        
        return count;                           // Returns the number of 1's within the set
    }

    void printBinary()
    {
        std::string s;                      // Initializes the string
        unsigned short temp = bits;         // Creates a temporary variable set to the stored bits
        while (s.size() < SHORT_SIZE)       // Iterates over the set
        {
            s = (char)(temp % 2 + '0') + s; // If the bit is odd then the char added to the string will be 1, otherwise it will be 0
            temp >>= ONE;                   // Divide the temporary variable by 2
        }
        printf("0b%s", s.c_str());          // Print the string
    }

    void print()
    {
        printf("[%d, 0x%x, 0%o, ", bits, bits, bits);   // Print the stored bits in decimal, hex, then octal
        printBinary();                                  // Call to print the bits in binary
        printf("]\n");                                  // End the output and add a newline
    }

private:
    unsigned short bits;    // Stored bits
} Bitset;

int main(int argc, char** argv) 
{
    Bitset s(0xC0DE);   // Set the bits to 16231, 0x3F67, 037547, 0b0011111101100111

    std::cout << "None: " << (s.none() ? "True" : "False") << std::endl;         // Prints 1 if all the bits are 0, and 0 if at least one bit is a 1 
    std::cout << "Any: " << (s.any() ? "True" : "False") << std::endl;           // Prints 1 if at least one of the bits is a 1, and 0 if all the bits are 0
    std::cout << "All: " << (s.all() ? "True" : "False") << std::endl;           // Prints 1 if all the bits are 1, and 0 if at least one bit is a 0
    std::cout << "Get index 2: " << (s.get(2) ? "True" : "False") << std::endl;  // Prints the state of the bit at the index

    std::cout << "\nBitset: ";
    s.print();  // Prints the bitset

    std::cout << "\nFlip: ";
    s.flip();   // Flips the bits
    s.print();  // Prints the flipped bitset
    std::cout << "Flip back: ";
    s.flip();   // Flips the bits back to the original state
    s.print();  // Prints the original bitset

    std::cout << "\nSet index 8: ";
    s.set(8);   // Sets the bit at 8
    s.print();  // Prints the new bitset
    std::cout << "Clear index 8: ";
    s.clear(8); // Clears the bit at 8
    s.print();  // Prints the original bitset

    std::cout << "\nSwap: ";
    s.swap();   // Swaps the bytes
    s.print();  // Prints the new bitset
    std::cout << "Swap back: ";
    s.swap();   // Swaps the bytes back
    s.print();  // Prints the new bitset
    
    std::cout << "\nSwapHi: ";
    s.swapHi(); // Swaps the high nibbles
    s.print();  // Prints the new bitset
    std::cout << "SwapHi back: ";
    s.swapHi(); // Swaps the high nibbles back
    s.print();  // Prints the original bitset

    std::cout << "\nSwapLo: ";
    s.swapLo(); // Swaps the low nibbles
    s.print();  // Prints the new bitset
    std::cout << "SwapLo back: ";
    s.swapLo(); // Swaps the low nibbles back
    s.print();  // Prints the new bitset

    std::cout << "\nCount: " << s.count() << std::endl; // Counts the number of bits that are 1
    std::cout << "Power of 2: " << s.isPow2() << std::endl; // Prints 1 if the bitset is a power of 2, and 0 otherwise

    std::cout << "\nClear last: ";
    s.clearLast1(); // Clears the rightmost bit
    s.print();  // Prints the new bitset

    return 0;
}
