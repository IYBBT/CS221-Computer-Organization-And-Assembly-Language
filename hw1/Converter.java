
import java.util.HashMap;

public class Converter {

    private static HashMap<Character, Integer> RomanNums;

	static {
		RomanNums = buildRomanMap();
	}

	public static char getSymbol(long digit) {
		if (digit >= 0 && digit <= 9) {
			return (char)('0' + digit);
		}
		else {
			return (char)('A' + (digit - 10));
		}
	}

	public static long getValue(char symbol) {
		if (symbol >= '0' && symbol <= '9'){
			return symbol - '0';
		}
		else {
			return (symbol - 'A') + 10;
		}
	}

	public static long from10(long number, int base) {
		int power = 0;
		long num = 0;
		while (number > 0) {
			num += Math.pow(10, power) * (number % base);
			number /= base;
			++power;
		}
		return num;
	}

	public static String from10(long number) {
		String num = "";
		while (number > 0) {
			num = getSymbol(number % 16) + num;
			number /= 16;
		}
		return num;
	}

	public static long to10(long number, int base) {
		int power = 0;
		long num = 0;
		while (number > 0) {
			num += Math.pow(base, power) * (number % 10);
			number /= 10;
			++power;
		}
		return num;
	}

	public static long to10(String number) {
		int power = 0;
		long num = 0;
		for (int i = 1; i <= number.length(); ++i) {
			num += Math.pow(16, power) * getValue(number.charAt(number.length() - i));
			++power;
		}
		return num;
	}

	public static HashMap<Character, Integer> buildRomanMap() {
		HashMap<Character, Integer> RomanNums = new HashMap<>();
		RomanNums.put('I', 1);
		RomanNums.put('X', 10);
		RomanNums.put('C', 100);
		RomanNums.put('M', 1000);
		RomanNums.put('V', 5);
		RomanNums.put('L', 50);
		RomanNums.put('D', 500);
		return RomanNums;
	}

	public static int fromRoman(String number) {
		int num = 0;
		for (int i = 0; i < number.length(); ++i) {
			if (i < number.length() - 1 && 
				RomanNums.get(number.charAt(i)) < RomanNums.get(number.charAt(i + 1))) {
				num -= RomanNums.get(number.charAt(i));
			}
			else {
				num += RomanNums.get(number.charAt(i));
			}
		}
		return num;
	}
	
	public static void main(String[] args) {
		System.out.println("9 in base 2 is " + from10(9, 2));  // 1001
		System.out.println("9 in base 7 is " + from10(9, 7));  // 12
		System.out.println("9 in base 3 is " + from10(9, 3));  // 100
		System.out.println("9 in base 5 is " + from10(9, 5));  // 14
		System.out.println();
		
		System.out.println("9 in base 16 is " + from10(9));      // 9
		System.out.println("19 in base 16 is " + from10(19));    // 13
		System.out.println("99 in base 16 is " + from10(99));    // 63
		System.out.println("199 in base 16 is " + from10(199));  // C7
		System.out.println();
		
		System.out.println("11100101 from base 2 is " + to10(11100101, 2));    // 229
		System.out.println("332 from base 4 is " + to10(332, 4));			     // 62
		System.out.println("121 from base 5 is " + to10(121, 5));  			 // 36
		System.out.println("100 from base 7 is " + to10(100, 7));  			 // 49
		System.out.println();
		
		System.out.println("C0DE from base 16 is " + to10("C0DE"));  // 49374
		System.out.println("BEEF from base 16 is " + to10("BEEF"));  // 48879
		System.out.println("C0A1 from base 16 is " + to10("C0A1"));  // 49313
		System.out.println("BBB from base 16 is " + to10("BBB"));    // 3003
		System.out.println();
		
		System.out.println("XXXIX from Roman numerals is " + fromRoman("XXXIX"));  		   // 39
		System.out.println("CCXLVI from Roman numerals is " + fromRoman("CCXLVI"));  	   // 246
		System.out.println("DCCLXXXIX from Roman numerals is " + fromRoman("DCCLXXXIX"));  // 789
		System.out.println("MMCDXXI from Roman numerals is " + fromRoman("MMCDXXI"));  	   // 2421
		System.out.println("CLX from Roman numerals is " + fromRoman("CLX"));  			   // 160
		System.out.println("CCVII from Roman numerals is " + fromRoman("CCVII"));		   // 207
		System.out.println("MIX from Roman numerals is " + fromRoman("MIX"));  			   // 1009
		System.out.println("MLXVI from Roman numerals is " + fromRoman("MLXVI"));  		   // 1066
		System.out.println("MMMCMXCIX from Roman numerals is " + fromRoman("MMMCMXCIX"));  // 3999
		System.out.println("MDCCLXXVI from Roman numerals is " + fromRoman("MDCCLXXVI"));  // 1776
		System.out.println("MCMXVIII from Roman numerals is " + fromRoman("MCMXVIII"));    // 1918
		System.out.println("MCMXLIV from Roman numerals is " + fromRoman("MCMXLIV"));  	   // 1944
		System.out.println("MMXXIII from Roman numerals is " + fromRoman("MMXXIII"));  	   // 2023
	}
}
