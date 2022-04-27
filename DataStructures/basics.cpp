#include<iostream>
#include<vector>
#include<string>

// std::cin;	characters from stdin;	reads from buffer
// std::cout;	characters to stdout	writes to buffer first, output to console when buffer full
// std::clog;	characters to stderr;	writes to buffer first, output to console when buffer full
// std::cerr;	characters to stderr; immediatly writes to console

int main()
{
	/****************************************************************************/
	// vector
	/****************************************************************************/

	/*
	{
		std::vector koka{ 1,2,3 };
		koka.resize(5, -1); // 1 2 3 -1 -1
	}
	//*/

	// Copies Are Always Deep!
	// deep copying : copying creates a new vector objectand copies all contained objects
	// deep assignment : all contained objects are copied from source to assignment target
	// deep comparison : comparing two vectors compares the values of the contained objects
	// deep ownership : destroying a vector destroys all contained objects

	//for (auto& i : koka) std::cout << i << " ";

	/****************************************************************************/
	// Scoped Enumearatioons C++11
	/****************************************************************************/
	/*
	{
		enum class day { mon, tue, wed, thu, fri, sat, sun };
		day d = day::mon;
		d = day::tue;
		//d = wed;  //  COMPILER ERROR: 'wed' only known in day's scope
	}
	//*/

	/****************************************************************************/
	// Enumerations
	/****************************************************************************/

	// Unscoped enumerations
	/*
	{
		enum day { mon, tue, wed, thu, fri, sat, sun };
		day d = day::mon;  // OK!
		//day d = mon;  // COMPILER ERROR!
		int i = wed;  // OK!, i = 2
		//enum stars { sun, … };  //  COMPILER ERROR: name collision
	}
	//*/

	//*/Conversions To / From Underlying Type
	/*
	{
		enum class month {
			jan = 1, feb = 2, mar = 3, apr = 4, may = 5, jun = 6,
			jul = 7, aug = 8, sep = 9, oct = 10, nov = 11, dec = 12
		};

		int i = static_cast<int>(month::mar);

		std::cin >> i;
		month m1 = static_cast<month>(i);
	}
	//*/

	/****************************************************************************/
	// Type System Basics
	/****************************************************************************/

	// Constant Expressions: constexpr C++11
	// must be computable at compile time
	// can be computed at runtime if not invoked in a constexpr context
	// all expressions inside a constexpr context must be constexpr themselves
	// constexpr functions may contain
		// C++11 nothing but one return statement
		// C++14 no statements
	///*
	{
		// two simple functions:
		// constexpr int cxf(int i) { return i * 2; }
		// int foo(int i) { return i * 2; }

		// constexpr int i = 2;       // OK '2' is a literal

		// constexpr int j = cxf(5);  // OK, cxf is constexpr 
		// constexpr int k = cxf(i);  // OK, cxf and i are constexpr

		// int x = 0;       // not constexpr
		// int l = cxf(x);  // OK, not a constexpr context

		// constexpr contexts:
		// constexpr int m = cxf(x);  // 
		// constexpr int n = foo(5);  //
	}
	//*/

	/****************************************************************************/
	// Functions (Basics)
	/****************************************************************************/

	// Attribute [[nodiscard]] C++17
	/*
	{
		[[nodiscard]] bool ret(int i) { // ovo mora da se nalazi van int-main
			return true;
		};
		// return value(s) used:
		bool const yes = prime(47); // OK!
		if (ret(47))  // OK!
			std::cout << "ova moze " << "\n";

		prime(47); // ERROR! return value discarded/ignored:
	}
	//*/

	// No-Throw Guarantee: noexcept C++11
	/*
	{
		auto foo = []() noexcept {}; // ne sme da baci izuzetak
	}
	//*/

	/****************************************************************************/
	// String (Basics)
	/****************************************************************************/

	// "C string Literal"
	/*
	{
		auto a = "seven of"; // type of a is char const[]
		auto b = a; // b refers to same object as a

		//a += " nine";            //  COMPILER ERROR: can't be modified
		//auto c = "al" + "cove";  //  COMPILER ERROR

		std::string s = a;    // a is copied into s
		s += " nine";         //  (s is std::string)
	}
	//*/

	// "std::string Literal"s C++14
	/*
	{
		using namespace std::string_literals;
		using namespace std;

		auto s1 = "seven of"s;  // type of s1 is std::string
		auto s2 = s1;           // s2 is a copy of s1

		s1 += " nine";          // OK
		cout << s1 << '\n';     // seven of nine
		cout << s2 << '\n';     // seven of

		auto s3 = "uni"s + "matrix"s;  // OK
		cout << s3 << '\n';     // unimatrix
	}
	//*/

	// Raw String Literals
	// Advantage: special characters can be used without escaping
	/*
	{
		// R"(raw "C"-string c:\users\joe)"	char const[] // C++11
		// R"(raw "std"-string c:\users\moe)"s	std::string // C++14s

		//Syntax: R"DELIMITER(characters...)DELIMITER"
		// where DELIMITER can be a sequence of 0 to 16 characters except spaces, (, ) and \
	}
	//*/

	//
	/*
	{
	}
	//*/

	return 0;
}

//
/*
{
}
//*/