
#include <iostream>
#include <string>
#include <map>

std::map<char, int> roman_nums;

char getSymbol(long digit)
{
    if (digit >= 0 && digit <= 9) {
        return (char)('0' + digit);
    }
    else {
        return (char)('A' + (digit - 10));
    }
}
    
long getValue(char symbol)
{
    if (symbol >= '0' && symbol <= '9') {
        return symbol - '0';
    }
    else {
        return (symbol - 'A') + 10;
    }
}

long from10(long number, int base)
{
    long power = 1;
    long result = 0;
    while (number > 0)
    {
        result += power * (number % base);
        number /= base;
        power *= 10;
    }
    return result;
}

std::string from10(long number)
{
    std::string result;
    while (number > 0)
    {
        result = getSymbol(number % 16) + result;
        number /= 16;
    }
    return result;
}

long to10(long number, int base)
{
    long power = 1;
    long result = 0;
    while (number > 0)
    {
        result += power * (number % 10);
        number /= 10;
        power *= base;
    }
    return result;
}

long to10(std::string number)
{
    long power = 1;
    long result = 0;
    for (int i = number.size() - 1; i >= 0; --i)
    {
        result += power * getValue(number[i]);
        power *= 16;
    }
    return result;
}

void init_roman() {
    roman_nums['I'] = 1;
    roman_nums['X'] = 10; 
    roman_nums['C'] = 100; 
    roman_nums['M'] = 1000; 
    roman_nums['V'] = 5; 
    roman_nums['L'] = 50; 
    roman_nums['D'] = 500;
}

int fromRoman(std::string number)
{
    init_roman();
    int result = 0;
    for (int i = 0; i < number.size() - 1; ++i)
    {
        if (roman_nums[number[i]] < roman_nums[number[i+1]]) 
        {
            result -= roman_nums[number[i]];
        }
        else 
        {
            result += roman_nums[number[i]];
        }
    }
    result += roman_nums[number[number.size() - 1]];
    return result;
}

// int main(int argc, char** argv)
// {
// 	std::cout << "9 in base 2 is " << from10(9, 2) << std::endl;  // 1001
// 	std::cout << "9 in base 7 is " << from10(9, 7) << std::endl;  // 12
// 	std::cout << "9 in base 3 is " << from10(9, 3) << std::endl;  // 100
// 	std::cout << "9 in base 5 is " << from10(9, 5) << std::endl;  // 14
// 	std::cout << std::endl;
	
// 	std::cout << "9 in base 16 is " << from10(9) << std::endl;      // 9
// 	std::cout << "19 in base 16 is " << from10(19) << std::endl;    // 13
// 	std::cout << "99 in base 16 is " << from10(99) << std::endl;    // 63
//     std::cout << "199 in base 16 is " << from10(199) << std::endl;  // C7
// 	std::cout << std::endl;
	
// 	std::cout << "11100101 from base 2 is " << to10(11100101, 2) << std::endl;  // 229
// 	std::cout << "332 from base 4 is " << to10(332, 4) << std::endl;			// 62
// 	std::cout << "121 from base 5 is " << to10(121, 5) << std::endl;  			// 36
// 	std::cout << "100 from base 7 is " << to10(100, 7) << std::endl;  			// 49
// 	std::cout << std::endl;
	
// 	std::cout << "C0DE from base 16 is " << to10("C0DE") << std::endl;  // 49374
// 	std::cout << "BEEF from base 16 is " << to10("BEEF") << std::endl;  // 48879
// 	std::cout << "C0A1 from base 16 is " << to10("C0A1") << std::endl;  // 49313
// 	std::cout << "BBB from base 16 is " << to10("BBB") << std::endl;    // 3003
// 	std::cout << std::endl;
		
// 	std::cout << "XXXIX from Roman numerals is " << fromRoman("XXXIX") << std::endl;  		   // 39
// 	std::cout << "CCXLVI from Roman numerals is " << fromRoman("CCXLVI") << std::endl;  	   // 246
// 	std::cout << "DCCLXXXIX from Roman numerals is " << fromRoman("DCCLXXXIX") << std::endl;   // 789
// 	std::cout << "MMCDXXI from Roman numerals is " << fromRoman("MMCDXXI") << std::endl;  	   // 2421
// 	std::cout << "CLX from Roman numerals is " << fromRoman("CLX") << std::endl;  			   // 160
// 	std::cout << "CCVII from Roman numerals is " << fromRoman("CCVII") << std::endl;		   // 207
// 	std::cout << "MIX from Roman numerals is " << fromRoman("MIX") << std::endl;  			   // 1009
// 	std::cout << "MLXVI from Roman numerals is " << fromRoman("MLXVI") << std::endl;  		   // 1066
// 	std::cout << "MMMCMXCIX from Roman numerals is " << fromRoman("MMMCMXCIX") << std::endl;   // 3999
// 	std::cout << "MDCCLXXVI from Roman numerals is " << fromRoman("MDCCLXXVI") << std::endl;   // 1776
// 	std::cout << "MCMXVIII from Roman numerals is " << fromRoman("MCMXVIII") << std::endl;     // 1918
// 	std::cout << "MCMXLIV from Roman numerals is " << fromRoman("MCMXLIV") << std::endl;  	   // 1944
// 	std::cout << "MMXXIII from Roman numerals is " << fromRoman("MMXXIII") << std::endl;  	   // 2023
// }