
#include <iostream>
#include <cassert>

#define ZERO 0x0
#define ONE 0x1
#define TWO 0x2

template<typename T>
struct Bitset
{
    
    Bitset()
    {
        this->bits = (T)ZERO;
    }

    Bitset(T bits)
    {
        this->bits = bits;
    }

    T getValue() const
    {
        return bits;
    }

    bool none() const
    {
        return !(bits | (T)ZERO);
    }

    bool any() const
    {
        return bits;
    }

    bool all() const
    {
        return !(bits ^ (T)~ZERO);
    }

    void flip()
    {
        bits = ~bits;
    }

    bool get(int index) const
    {
        T temp = bits >> index;
        return temp & ONE;
    }

    void set()
    {
        bits |= (T)~ZERO;
    }

    void set(int index)
    {
        T temp = (T)ONE << index;
        bits |= temp;
    }

    void clear()
    {
        bits &= (T)ZERO;
    }

    void clear(int index)
    {
        T temp = ~((T)ONE << index);
        bits &= temp;
    }

    void swap()
    {
        int half_size = width >> ONE;
        T f = (bits & ((T)~ZERO >> half_size)) << half_size;
        T s = (bits & ((T)~ZERO << half_size)) >> half_size;
        bits = f | s;
    }

    void swapHi()
    {
        int half_size = width >> ONE;
        int quart_size = width >> TWO;

        T first = (bits & ((T)~ZERO >> half_size));
        T second = (bits & ((T)~ZERO << half_size)) >> half_size;
        T high_first = (second & ((T)~ZERO >> (half_size + quart_size)));
        T high_second = (second ^ high_first) >> quart_size;

        high_first <<= quart_size;
        second = (high_first | high_second) << half_size;
        bits = second | first;
    }

    void swapLo()
    {
        int half_size = width >> ONE;
        int quart_size = width >> TWO;

        T first = (bits & ((T)~ZERO >> half_size));
        T second = (bits & ((T)~ZERO << half_size));
        T low_first = (first & ((T)~ZERO >> (half_size + quart_size)));
        T low_second = (first ^ low_first) >> quart_size;

        low_first <<= quart_size;
        first = (low_first | low_second);
        bits = second | first;
    }

    bool isPow2() const
    {
        return !(bits & (bits - 1));
    }

    void clearLast1()
    {
        bits &= (bits - 1);
    }

    int count() const
    {
        T temp = bits;
        int count = 0;
        for (int i = 0; i < width; ++i)
        {
            if (temp & ONE)
            {
                ++count;
            }
            temp >>= ONE;
        }

        return count;
    }

    // void printBinary() const
    // {
    //     std::string s;                          // Initializes the string
    //     T temp = bits;                          // Creates a temporary variable set to the stored bits
    //     while (s.size() < width)                // Iterates over the set
    //     {
    //         s = (char)(temp % TWO + '0') + s;   // If the bit is odd then the char added to the string will be 1, otherwise it will be 0
    //         temp >>= ONE;                       // Divide the temporary variable by 2
    //     }
    //     std::cout << "0b" << s;                 // Print the string
    // }

    // void print() const
    // {
    //     std::cout << "[" << std::dec << bits;   // Print the stored bits in decimal, hex, then octal
    //     std::cout << ", 0x" << std::hex << bits;
    //     std::cout << ", 0" << std::oct << bits;
    //     std::cout << ", ";
    //     printBinary();                          // Call to print the bits in binary
    //     std::cout << "]\n";                     // End the output and add a newline
    // }

    bool operator==(const Bitset& rs) const
    {
        return this->bits == rs.bits;
    }

    bool operator<(const Bitset& rs) const
    {
        return this->bits < rs.bits;
    }

    Bitset<T> operator&(const Bitset& rs) const
    {
        return this->bits & rs.bits;
    }

    Bitset<T> operator~() const
    {
        return ~this->bits;
    }

    Bitset<T> operator<<(const int shift) const
    {
        return this->bits << shift;
    }

    Bitset<T> operator^=(const Bitset& rs)
    {
        return this->bits ^= rs.bits;
    }

    Bitset<T> operator>>=(const int shift)
    {
        return this->bits >>= shift;
    }

    Bitset<T> operator+=(const T value)
    {
        return this->bits += value;
    }

    Bitset<T> operator++()
    {
        return ++this->bits;
    }

private:
    T bits;
    const int width = 8*sizeof(T);
};

template<typename T>
bool operator!=(const Bitset<T>& ls, const Bitset<T>& rs)
{
    return !(ls == rs);
}

template<typename T>
bool operator>=(const Bitset<T>& ls, const Bitset<T>& rs)
{
    return !(ls < rs);
}

template<typename T>
Bitset<T> operator|(const Bitset<T>& ls, const Bitset<T>& rs)
{
    return ls.getValue() | rs.getValue();
}

template<typename T>
Bitset<T> operator^(const Bitset<T>& ls, const Bitset<T>& rs)
{
    return ls.getValue() ^ rs.getValue();
}

// template<typename T>
// Bitset<T> operator~(const Bitset<T>& bs)
// {
//     return ~bs.getValue();
// }

template<typename T>
Bitset<T> operator>>(const Bitset<T>& ls, const int shift)
{
    return ls.getValue() >> shift;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Bitset<T>& bs)
{
    T bits = bs.getValue();
    os << "[" << std::dec << bits;     // Print the stored bits in decimal, hex, then octal
    os << ", 0x" << std::hex << bits;
    os << ", 0" << std::oct << bits;
    os << ", ";

    std::string s;                              // Initializes the string
    while (s.size() < sizeof(T)*8)              // Iterates over the set
    {
        s = (char)(bits % TWO + '0') + s;       // If the bit is odd then the char added to the string will be 1, otherwise it will be 0
        bits >>= ONE;                           // Divide the temporary variable by 2
    }
    os << "0b" << s;                            // Print the string

    os << "]";                                  // End the output and add a newline
    os << std::dec;
    return os;
}

int main()
{
    Bitset<uint16_t> set1(0xC0DE);
    Bitset<uint64_t> set2(0xC0DEBEEFC0A1BBBB);

    // std::cout << set1 << std::endl;
    // std::cout << set2 << std::endl;

    // Assignment 2 tests for set 1
    assert(!set1.none());
    assert(set1.any());
    assert(!set1.all());
    assert(set1.get(2));
    
    set1.flip();
    assert(set1 == 0x3F21);
    set1.flip();
    assert(set1 == 0xC0DE);

    set1.set(8);
    assert(set1 == 0xC1DE);
    set1.clear(8);
    assert(set1 == 0xC0DE);

    set1.swap();
    assert(set1 == 0xDEC0);
    set1.swap();
    assert(set1 == 0xC0DE);

    set1.swapHi();
    assert(set1 == 0x0CDE);
    set1.swapHi();
    assert(set1 == 0xC0DE);

    set1.swapLo();
    assert(set1 == 0xC0ED);
    set1.swapLo();
    assert(set1 == 0xC0DE);

    assert(!set1.isPow2());
    set1.clearLast1();
    assert(set1 == 0xC0DC);
    set1.set(1);

    // Assignment 2 tests for set 2
    assert(!set2.none());
    assert(set2.any());
    assert(!set2.all());
    assert(set2.get(0));

    set2.flip();
    assert(set2 == 0x3F2141103F5E4444);
    set2.flip();
    assert(set2 == 0xC0DEBEEFC0A1BBBB);

    set2.set(10);
    assert(set2 == 0xC0DEBEEFC0A1BFBB);
    set2.clear(10);
    assert(set2 == 0xC0DEBEEFC0A1BBBB);

    set2.swap();
    assert(set2 == 0xC0A1BBBBC0DEBEEF);
    set2.swap();
    assert(set2 == 0xC0DEBEEFC0A1BBBB);

    set2.swapHi();
    assert(set2 == 0xBEEFC0DEC0A1BBBB);
    set2.swapHi();
    assert(set2 == 0xC0DEBEEFC0A1BBBB);

    set2.swapLo();
    assert(set2 == 0xC0DEBEEFBBBBC0A1);
    set2.swapLo();
    assert(set2 == 0xC0DEBEEFC0A1BBBB);

    assert(!set2.isPow2());
    set2.clearLast1();
    assert(set2 == 0xC0DEBEEFC0A1BBBA);
    set2.set(0);

    // Assignment 3 tests
    Bitset<uint16_t> set3(0xC0A1);

    assert(set1.getValue() == 0xC0DE);
    assert(set3.getValue() == 0xC0A1);

    assert(!(set1 == set3));
    assert(set1 != set3);

    assert((set1 & set3) == 0xC080);
    assert((set1 | set3) == 0xC0FF);
    assert((set1 ^ set3) == 0x007F);
    assert(~set1 == 0x3F21);

    assert((set1 << 4) == 0x0DE0);
    assert((set1 >> 4) == 0x0C0D);

    assert(set3 < set1);
    assert(set1 >= set3);

    set1 ^= set3;
    assert(set1 == 0x007F);
    assert((set1 >>= 4) == 0x0007);
    assert((set1 += 4) == 0x000B);
    assert(++set1 == 0x000C);

    return 0;
}
