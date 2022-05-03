
#include<array>
#include<cassert>
#include<cctype>
#include<compare>
#include<complex>
#include<cstddef>
#include<cstdint>
#include<cstdlib>
#include<functional>
#include<iomanip>
#include<iostream>
#include<iterator>
#include<memory>
#include<numeric>
#include<random>
#include<ranges>
#include<string>
#include<string_view>
#include<thread>
#include<type_traits>
#include<utility>
#include<vector>
using namespace std;

// fill vector with random values
vector<int> v{ 2, 4, 7, 8, 3, 6, 9, 8, 1, 0, 5 };

int main()
{
	/****************************************************************************/
	// Non-modifying sequence operations
	// header <algorithm>
	/****************************************************************************/

	// std::all_of, std::none_of, std::any_of // C++ 11
	// checks if a predicate is true for all, any or none of the elements in a range
	/*
	{
		// all_of
		cout << "all_of" << "\n";

		{
			if (all_of(v.cbegin(), v.cend(), [](int i) { return i % 2 == 0; }))
				cout << "All numbers are even." << "\n";
			else
				cout << "Not all numbers are even." << "\n";
		}

		// none_of
		cout << "none_of" << "\n";

		{
			if (std::none_of(v.cbegin(), v.cend(),
				std::bind(std::modulus<>(), std::placeholders::_1, 2)))
				std::cout << "None of them are odd." << "\n";
			else 	std::cout << "Some of them are odd." << "\n";
		}

		// any_of
		cout << "any_of" << "\n";

		{
			if (std::any_of(v.cbegin(), v.cend(),
				[](auto& i) {
					if (i % 2) return true;
				}
			))
				std::cout << "At least one number is divisible by 7." << "\n";
		}
	}
	//*/

	// std::ranges::all_of, std::ranges::any_of, std::ranges::none_of // c++20
	// treba skontati cemu sluzi ovaj poslednji argument, ne znam sta je ovo
	/*
	{
		std::cout << "Among the numbers: ";
		ranges::copy(v, std::ostream_iterator<int&>(std::cout, " "));
		std::cout << '\n';

		if (ranges::all_of(v.cbegin(), v.cend(), [](int i) { return i % 2 == 0; })) {
			std::cout << "All numbers are even." << "\n";
		}
		if (ranges::none_of(v, std::bind(std::modulus<int>(), std::placeholders::_1, 2))) {
			std::cout << "None of them are odd." << "\n";
		}

		auto DivisibleBy = [](int d)
		{
			return [d](int m) { return m % d == 0; };
		};

		if (ranges::any_of(v, DivisibleBy(7))) {
			std::cout << "At least one number is divisible by 7." << "\n";
		}
	}
	//*/

	// std::for_each, std::for_each_n C++17(_n)
	// applies a function to a range of elements or n elements
	/*
	{
		// std::for_each
		auto inc = [](int& n) { n++; };
		std::for_each(v.begin(), v.end(), inc);
		std::for_each(v.begin(), v.end(), [](auto& t) {cout << t << " "; });

		// std::for_each
		std::for_each_n(v.begin(), 5, inc);
		std::for_each(v.begin(), v.end(), [](auto& t) {cout << t << " "; });
	}
	//*/

	// std::ranges::for_each // C++20
	// applies a function to a range of elements
	/*
	{
		auto print = [](const auto& n) { std::cout << n << ' '; };
		std::ranges::for_each(v, print); // samo je ovo novo, osto se ponasa kao stari std::for_each
	}
	//*/

	//  std::ranges::for_each_n // C++20
	// applies a function object to the first n elements of a sequence
	/*
	{
		struct ex {
			int first;
			int second;
		};
		vector<ex> v{ { 1, 2 }, { 3, 4 }, { 5, 6 } };
		std::ranges::for_each_n(v.begin(), 3, [](auto& n) { n *= -1; }, &ex::first);
		for (auto& i : v)
			cout << i.first << " " << i.second << "\n";

	}
	//*/

	// std::count, std::count_if
	// returns the number of elements satisfying specific criteria
	/*
	{
		std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(std::cout, " "));
		cout << "\n";

		// std::count
		for (const int target : {3, 4, 5}) {
			const int num_items = std::count(v.cbegin(), v.cend(), target);
			std::cout << "number: " << target << ", count: " << num_items << '\n';
		}

		// std::count_if
		int count_div4 = std::count_if(v.begin(), v.end(), [](int i) {return i % 4 == 0; });
		std::cout << "numbers divisible by four: " << count_div4 << '\n';
	}
	//*/

	// std::ranges::count, std::ranges::count_if // C++20
	// returns the number of elements satisfying specific criteria
	/*
	{
		auto number_of_fives = std::ranges::count(v, 5);
		//auto number_of_fives = std::ranges::count(v.begin(), v.end(), 5); // old way
		int number_of_threes = std::ranges::count_if(v, [](int i) {return i % 3 == 0; });
		//int number_of_threes = std::ranges::count_if(v.begin(), v.end(), [](int i) {return i % 3 == 0; }); // old way
	}
	//*/

	// mismatch
	// finds the first position where two ranges differ
	/*
	{
		//string koka = "abcdfabc";
		//auto mis = mismatch(koka.begin(), koka.end(), "abc");
		//cout << "first mismatch: " << *mis.first << " " << *mis.second << "\n";

		vector<int>a = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		vector<int>b = { 1, 2, 3, 4, 5 };
		int myints[] = { 1, 2, 4, 6 };
		auto mis = mismatch(a.begin(), a.end(), myints);
		cout << "first mismatch: " << *mis.first << " " << *mis.second << "\n";

		// ovo nesto ne radi
		//auto koka = mismatch(a.begin(), a.end(), b.begin(), std::equal_to<int>());
		//cout << "first mismatch: " << *koka.first << " " << *koka.second << "\n";
	}
	//*/

	// std::ranges::mismatch  C++20
	// finds the first position where two ranges differ
	// ako ne postoji mismatch onda ispis puca, ne znam kako da proverim da li je res mismatch-a prazan
	/*
	{
		string_view in1{ "radarXxradar" };
		const auto res1 = std::ranges::mismatch(in1, in1 | std::views::reverse);
		cout << "first mismatch: " << *res1.in1 << " " << *res1.in2 << '\n';

		string_view in2{ "radarXYZxradar" };
		const auto res2 = std::ranges::mismatch(
			in2,
			in2 | std::views::reverse,
			[](char c1, char c2) { return std::toupper(c1) == std::toupper(c2); }
			// ovde ce da prvo uveca malo x pa ce da X == X da bude true
		);
		cout << "first mismatch: " << *res2.in1 << " " << *res2.in2 << '\n';

		vector<int> t1{ 1,2,3,4 };
		vector<int> t2{ 1,2,4,5 };

		auto in3 = std::ranges::mismatch(
			t1,
			t2,
			std::equal_to<int>()
		);
		cout << "first mismatch: " << *in3.in1 << " " << *in3.in2 << '\n';

	}
	//*/

	// std::find, std::find_if, std::find_if_not
	// finds the first element satisfying specific criteria
	/*
	{
		std::vector<int> v{ 1, 2, 3, 4 };
		int n1 = 3;
		int n2 = 5;
		auto is_even = [](int i) { return i % 2 == 0; };

		auto result1 = std::find(begin(v), end(v), n1);
		auto result2 = std::find(begin(v), end(v), n2);
		auto result3 = std::find_if(begin(v), end(v), is_even);

		(result1 != std::end(v))
			? std::cout << "v contains " << n1 << '\n'
			: std::cout << "v does not contain " << n1 << '\n';

		(result2 != std::end(v))
			? std::cout << "v contains " << n2 << '\n'
			: std::cout << "v does not contain " << n2 << '\n';

		(result3 != std::end(v))
			? std::cout << "v contains an even number: " << *result3 << '\n'
			: std::cout << "v does not contain even numbers\n";
	}
	//*/

	// std::ranges::find, std::ranges::find_if, std::ranges::find_if_not C++20
	// finds the first element satisfying specific criteria
	/*
	{
		namespace ranges = std::ranges;

		const int n1 = 3;
		const int n2 = 5;
		const auto v = { 4, 1, 3, 2 };

		if (ranges::find(v, n1) != v.end())
			std::cout << "v contains: " << n1 << '\n';
		else
			std::cout << "v does not contain: " << n1 << '\n';

		if (ranges::find(v.begin(), v.end(), n2) != v.end())
			std::cout << "v contains: " << n2 << '\n';
		else
			std::cout << "v does not contain: " << n2 << '\n';

		auto is_even = [](int x) { return x % 2 == 0; };

		if (auto result = ranges::find_if(v.begin(), v.end(), is_even); result != v.end())
			std::cout << "First even element in v: " << *result << '\n';
		else
			std::cout << "No even elements in v\n";

		if (auto result = ranges::find_if_not(v, is_even); result != v.end())
			std::cout << "First odd element in v: " << *result << '\n';
		else
			std::cout << "No odd elements in v\n";

		auto divides_13 = [](int x) { return x % 13 == 0; };

		if (auto result = ranges::find_if(v, divides_13); result != v.end())
			std::cout << "First element divisible by 13 in v: " << *result << '\n';
		else
			std::cout << "No elements in v are divisible by 13\n";

		if (auto result = ranges::find_if_not(v.begin(), v.end(), divides_13); result != v.end())
			std::cout << "First element indivisible by 13 in v: " << *result << '\n';
		else
			std::cout << "All elements in v are divisible by 13\n";
	}
	//*/

	// std::find_end
	// finds the last sequence of elements in a certain range
	// poslednje ponavaljanje subkolekcije u kolekciji
	/*
	{
		std::vector<int> v{ 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4 };
		std::vector<int>::iterator result;

		auto check = [&] {
			result == v.end()
				? std::cout << "sequence not found\n"
				: std::cout << "last occurrence is at: "
				<< std::distance(v.begin(), result) << "\n";
		};

		std::vector<int> t1{ 1, 2, 3 };
		result = std::find_end(v.begin(), v.end(), t1.begin(), t1.end());
		check();

		std::vector<int> t2{ 4, 5, 6 };
		result = std::find_end(v.begin(), v.end(), t2.begin(), t2.end());
		check();
	}
	//*/

	// std::ranges::find_end
	// finds the last sequence of elements in a certain range
	/*
	{
		auto print = [](const auto haystack, const auto needle)
		{
			const auto pos = std::distance(haystack.begin(), needle.begin());
			std::cout << "In \"";
			for (const auto c : haystack) { std::cout << c; }
			std::cout << "\" found \"";
			for (const auto c : needle) { std::cout << c; }
			std::cout << "\" at position [" << pos << ".." << pos + needle.size() << ")\n"
				<< std::string(4 + pos, ' ') << std::string(needle.size(), '^') << '\n';
		};

		using namespace std::literals;
		constexpr auto secret{ "password password word..."sv };
		constexpr auto wanted{ "password"sv };

		constexpr auto found1 = std::ranges::find_end(
			secret.cbegin(), secret.cend(), wanted.cbegin(), wanted.cend());
		print(secret, found1);

		constexpr auto found2 = std::ranges::find_end(secret, "word"sv);
		print(secret, found2);

		const auto found3 = std::ranges::find_end(secret, "ORD"sv,
			[](const char x, const char y) { // uses a binary predicate
				return std::tolower(x) == std::tolower(y);
			});
		print(secret, found3);

		const auto found4 = std::ranges::find_end(secret, "SWORD"sv, {}, {},
			[](char c) { return std::tolower(c); }); // projects the 2nd range
		print(secret, found4);

		static_assert(std::ranges::find_end(secret, "PASS"sv).empty()); // => not found

	}
	//*/

	// std::find_first_of
	// searches for any one of a set of elements
	/*
	{
		const std::vector<int> v{ 0, 3, 25, 5 };
		const auto t1 = { 19, 10, 5, 6, 3, 4 };

		auto res = std::find_first_of(
			v.begin(),
			v.end(),
			t1.begin(),
			t1.end()
			//,[](int x, int y) { return x % y == 0; }
		);
		// print res dsitance and refference
		std::cout << "first of: " << *res << '\n';
		std::cout << "distance: " << std::distance(v.begin(), res) << '\n';
	}
	//*/

	// std::ranges::find_first_of C++20
	// searches for any one of a set of elements
	// primer sa cppreference-a nesto nece da se prevede
	// poenta da se svi range-evi razlikuju sto mogu da uhvate celu kolekcinju; ne zattevaju begin end
	/*
	{
	}
	//*/

	// std::adjacent_find
	// finds the first two adjacent items that are equal (or satisfy a given predicate)
	/*
	{
		std::vector<int> v1{ 0, 1, 2, 3, 40, 40, 41, 41, 5 };
		auto i1 = std::adjacent_find(v1.begin(), v1.end()
			//, std::bind(std::modulus<>(), std::placeholders::_1, 2) // moze i ovo da se stavi
		);

		if (i1 == v1.end())
			std::cout << "No matching adjacent elements\n";
		else
			std::cout << "The first adjacent pair of equal elements is at "
			<< std::distance(v1.begin(), i1) << ", *i1 = "
			<< *i1 << '\n';

		auto i2 = std::adjacent_find(v1.begin(), v1.end(), std::greater<int>());
		if (i2 == v1.end())
			std::cout << "The entire vector is sorted in ascending order\n";
		else
			std::cout << "The last element in the non-decreasing subsequence is at "
			<< std::distance(v1.begin(), i2) << ", *i2 = " << *i2 << '\n';
	}
	//*/

	// std::ranges::adjacent_find
	// finds the first two adjacent items that are equal (or satisfy a given predicate)
	/*
	{
		std::vector<int> v1{ 0, 1, 2, 3, 40, 40, 41, 41, 5 };
		namespace ranges = std::ranges;

		auto i1 = ranges::adjacent_find(v1.begin(), v1.end());
		if (i1 == v1.end())
			std::cout << "No matching adjacent elements\n";
		else
			std::cout << "The first adjacent pair of equal elements is at ["
			<< ranges::distance(v1.begin(), i1) << "] == " << *i1 << '\n';

		auto i2 = ranges::adjacent_find(v1, ranges::greater());
		if (i2 == v1.end())
			std::cout << "The entire vector is sorted in ascending order\n";
		else
			std::cout << "The last element in the non-decreasing subsequence is at ["
			<< ranges::distance(v1.begin(), i2) << "] == " << *i2 << '\n';
	}
	//*/

	// std::search
	// searches for a range of elements
	// return iterataton gde ga je nasao
	/*
	{
		std::string cont{ "why waste time learning, when ignorance is instantaneous?" };
		string s{ "learning" };
		auto res1 = std::search(cont.begin(), cont.end(), s.begin(), s.end()) != cont.end();
		res1
			? cout << "nasao"
			: cout << "nije nasao"
			;
	}
	//*/

	// std::ranges::search C+20
	// searches for a range of elements
	// ovo je neki glup primer
	/*
	{
		constexpr auto haystack{ "abcd abcdf"sv };
		constexpr auto needle{ "bcd"sv };

		// the search uses iterator pairs begin()/end():
		constexpr auto found1 = std::ranges::search(
			haystack.begin(), haystack.end(),
			needle.begin(), needle.end());

		constexpr auto found2 = std::ranges::search(haystack, needle);

		cout << found2.data() << "\n";
	}
	//*/

	// std::search_n
	// searches a range for a number of consecutive copies of an element
	// trazi n rednih elemenata koji su jednak zadatoj vrednosti
	/*
	{
		const char sequence[] = "1001010100010101001010101";
		std::cout << std::boolalpha;

		int count = 4;
		auto res = std::search_n(std::begin(sequence), std::end(sequence), count, '0') != std::end(sequence);
		std::cout << "Has " << count << " consecutive zeros : " << res << "\n";

		count = 3;
		res = std::search_n(std::begin(sequence), std::end(sequence), count, '0') != std::end(sequence);
		std::cout << "Has " << count << " consecutive zeros : " << res << "\n";

	}
	//*/

	// std::ranges::search_n
	// searches a range for a number of consecutive copies of an element
	/*
	{
		auto nums = { 1, 2, 2, 3, 4, 1, 2, 2, 2, 1, 2, 2, 2, };
		constexpr int count{ 3 };
		constexpr int value{ 2 };

		auto
			res = std::ranges::search_n(
				nums,
				count,
				value
			);

		cout << res.size() << "\n";
		cout << std::distance(nums.begin(), res.begin()) << "\n";

		res = std::ranges::search_n(
			res.end(),
			nums.end(),
			count,
			value
		);

		cout << res.size() << "\n";
		cout << std::distance(nums.begin(), res.begin()) << "\n";

	}
	//*/

	// std::ranges::starts_with C++23
	// checks whether a range starts with another range
	// ovo je nesto komplikovano
	// u sustini je kako pocinje string, ali su primeru uzasno glupi i nelogicni
	/*
	{
		using namespace std::literals;
		constexpr auto ascii_upper = [](char8_t c)
		{
			return u8'a' <= c && c <= u8'z' ? static_cast<char8_t>(c + u8'A' - u8'a') : c;
		};

		constexpr auto cmp_ignore_case = [=](char8_t x, char8_t y)
		{
			return ascii_upper(x) == ascii_upper(y);
		};

		static_assert(std::ranges::starts_with("const_cast", "const"sv));
		static_assert(std::ranges::starts_with("constexpr", "const"sv));
		static_assert(!std::ranges::starts_with("volatile", "const"sv));

		std::cout
			<< std::boolalpha
			<< std::ranges::starts_with(u8"Constantinopolis", u8"constant"sv,
				{}, ascii_upper, ascii_upper) << ' '
			<< std::ranges::starts_with(u8"Istanbul", u8"constant"sv,
				{}, ascii_upper, ascii_upper) << ' '
			<< std::ranges::starts_with(u8"Metropolis", u8"metro"sv,
				cmp_ignore_case) << ' '
			<< std::ranges::starts_with(u8"Acropolis", u8"metro"sv,
				cmp_ignore_case) << '\n';

		constexpr static auto v = { 1, 3, 5, 7, 9 };
		constexpr auto odd = [](int x) { return x % 2; };

		auto res =
			std::ranges::starts_with(v,
				std::views::iota(1) | std::views::filter(odd) | std::views::take(3));

	}
	//*/

	// std::ranges::ends_with C++23
	// checks whether a range starts with another range
	// kako se zavrsava string
	/*
	{
		std::cout
			<< std::boolalpha
			<< std::ranges::ends_with("static_cast", "cast") << '\n' // true
			<< std::ranges::ends_with("const_cast", "cast") << '\n' // true
			<< std::ranges::ends_with("reinterpret_cast", "cast") << '\n' // true
			<< std::ranges::ends_with("dynamic_cast", "cast") << '\n' // true
			<< std::ranges::ends_with("move", "cast") << '\n' // false
			<< std::ranges::ends_with("move_if_noexcept", "cast") << '\n' // false
			<< std::ranges::ends_with("forward", "cast") << '\n'; // false
		static_assert(
			!std::ranges::ends_with("as_const", "cast") and
			!!std::ranges::ends_with("bit_cast", "cast") and
			!std::ranges::ends_with("to_underlying", "cast") and
			!!std::ranges::ends_with(std::array{ 1,2,3,4 }, std::array{ 3,4 }) and
			!std::ranges::ends_with(std::array{ 1,2,3,4 }, std::array{ 4,5 })
			);
	}
	//*/

	/****************************************************************************/
	// Modifying sequence operations
	// header <algorithm>
	/****************************************************************************/

	// std::copy, std::copy_if C++11
	// copies a range of elements to a new location
	/*
	{
		std::vector<int> from_vector(10);
		std::iota(from_vector.begin(), from_vector.end(), 0);

		std::vector<int> to_vector;
		std::copy(from_vector.begin(), from_vector.end(),
			std::back_inserter(to_vector));
		// or, alternatively,
		//  std::vector<int> to_vector(from_vector.size());
		//  std::copy(from_vector.begin(), from_vector.end(), to_vector.begin());
		// either way is equivalent to
		//  std::vector<int> to_vector = from_vector;

		std::cout << "to_vector contains: ";

		std::copy(to_vector.begin(), to_vector.end(),
			std::ostream_iterator<int>(std::cout, " "));
		std::cout << '\n';

		std::cout << "odd numbers in to_vector are: ";

		std::copy_if(to_vector.begin(), to_vector.end(),
			std::ostream_iterator<int>(std::cout, " "),
			[](int x) { return x % 2 != 0; });
		std::cout << '\n';

		std::cout << "to_vector contains these multiples of 3:\n";

		to_vector.clear();
		std::copy_if(from_vector.begin(), from_vector.end(),
			std::back_inserter(to_vector),
			[](int x) { return x % 3 == 0; });

		for (int x : to_vector)
			std::cout << x << ' ';
	}
	//*/

	// std::ranges::copy, std::ranges::copy_if, std::ranges::copy_result, std::ranges::copy_if_result C++20
	// copies a range of elements to a new location
	/*
	{
		std::vector<int> from_vector(10);
		std::iota(from_vector.begin(), from_vector.end(), 0);

		std::vector<int> to_vector;

		namespace ranges = std::ranges;
		ranges::copy(from_vector.begin(), from_vector.end(),
			std::back_inserter(to_vector));
		// or, alternatively,
		//  std::vector<int> to_vector(from_vector.size());
		//  ranges::copy(from_vector.begin(), from_vector.end(), to_vector.begin());
		// either way is equivalent to
		//  std::vector<int> to_vector = from_vector;

		std::cout << "to_vector contains: ";

		ranges::copy(to_vector, std::ostream_iterator<int>(std::cout, " "));
		std::cout << '\n';

		std::cout << "odd numbers in to_vector are: ";

		ranges::copy_if(to_vector, std::ostream_iterator<int>(std::cout, " "),
			[](int x) { return (x % 2) == 1; });
		std::cout << '\n';
	}
	//*/

	// std::copy_n C++11
	// copies a range of elements to a new location
	/*
	{
		std::string in = "1234567890";
		std::string out;

		std::copy_n(in.begin(), 4, std::back_inserter(out));
		std::cout << out << '\n';

		std::vector<int> v_in(128);
		std::iota(v_in.begin(), v_in.end(), 1);
		std::vector<int> v_out(v_in.size());

		std::copy_n(v_in.cbegin(), 100, v_out.begin());
		std::cout << std::accumulate(v_out.begin(), v_out.end(), 0) << '\n';
	}
	//*/

	// std::ranges::copy_n, std::ranges::copy_n_result
	// copies a range of elements to a new location
	/*
	{
		const std::string_view in{ "ABCDEFGH" };
		std::string out;

		std::ranges::copy_n(in.begin(), 4, std::back_inserter(out));
		std::cout << std::quoted(out) << '\n';

		out = "abcdefgh";
		const auto res = std::ranges::copy_n(in.begin(), 5, out.begin());
		std::cout
			<< "*(res.in): '" << *(res.in) << "', distance: "
			<< std::distance(std::begin(in), res.in) << '\n'
			<< "*(res.out): '" << *(res.out) << "', distance: "
			<< std::distance(std::begin(out), res.out) << '\n';
		}
	//*/

	// std::copy_backward
	// copies a range of elements in backwards order
	// ako se kopira nedovoljan broj elemenata onda se nalepi posledji elem na prazna mesta
	/*
	{
		std::vector<int> from_vector;
		for (int i = 0; i < 10; i++)
			from_vector.push_back(i);

		std::vector<int> to_vector(15);
		std::copy_backward(from_vector.begin(), from_vector.end(), to_vector.end());

		std::cout << "to_vector contains: ";
		for (auto i : to_vector)
			std::cout << i << " ";
	}
	//*/

	// std::ranges::copy_backward, std::ranges::copy_backward_result C++20
	// copies a range of elements in backwards order
	/*
	{
		auto print = [](std::string_view rem, std::ranges::forward_range auto const& r) {
			for (std::cout << rem << ": "; auto const& elem : r)
				std::cout << elem << ' ';
			std::cout << '\n';
		};

		const auto src = { 1, 2, 3, 4 };
		print("src", src);

		std::vector<int> dst(src.size() + 2);
		std::ranges::copy_backward(src, dst.end());
		print("dst", dst);

		std::ranges::fill(dst, 0);
		const auto [in, out] =
			std::ranges::copy_backward(src.begin(), src.end() - 2, dst.end());
		print("dst", dst);

		std::cout
			<< "(in - src.begin) == " << std::distance(src.begin(), in) << '\n'
			<< "(out - dst.begin) == " << std::distance(dst.begin(), out) << '\n';
	}
	//*/

	// std::move
	// moves a range of elements to a new location
	/*
	{
		auto f = [](int n)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(n));
			std::cout << "thread " << n << " ended" << std::endl;
		};

		std::vector<std::thread> v;
		v.emplace_back(f, 250);
		v.emplace_back(f, 500);
		v.emplace_back(f, 750);
		std::list<std::thread> l;

		// copy() would not compile, because std::thread is noncopyable
		std::move(v.begin(), v.end(), std::back_inserter(l));
		for (auto& t : l) t.join();
	}
	//*/

	// std::ranges::move, std::ranges::move_result C++20
	// moves a range of elements to a new location
	/*
	{
		using namespace std::literals::chrono_literals;

		auto f = [](std::chrono::milliseconds n)
		{
			std::this_thread::sleep_for(n);
			std::cout << "thread with n=" << n.count() << "ms ended" << std::endl;
		};

		std::vector<std::jthread> v;
		v.emplace_back(f, 400ms);
		v.emplace_back(f, 600ms);
		v.emplace_back(f, 800ms);

		std::list<std::jthread> l;

		// std::ranges::copy() would not compile, because std::jthread is non-copyable
		std::ranges::move(v, std::back_inserter(l));
	}
	//*/

	// std::move_backward C++11
	// moves a range of elements to a new location in backwards order
	/*
	{
		using container = std::vector<std::string>;

		auto print = [](std::string_view comment, const container& src, const container& dst = {})
		{
			auto prn = [](std::string_view name, const container& cont) {
				std::cout << name;
				for (const auto& s : cont) { std::cout << (s.empty() ? "*" : s.data()) << ' '; }
				std::cout << '\n';
			};
			std::cout << comment << '\n';
			prn("src: ", src);
			if (dst.empty()) return;
			prn("dst: ", dst);
		};

		container src{ "foo", "bar", "baz" };
		container dst{ "qux", "quux", "quuz", "corge" };
		print("Non-overlapping case; before move_backward:", src, dst);
		std::move_backward(src.begin(), src.end(), dst.end());
		print("After:", src, dst);

		src = { "snap", "crackle", "pop", "lock", "drop" };
		print("Overlapping case; before move_backward:", src);
		std::move_backward(src.begin(), std::next(src.begin(), 3), src.end());
		print("After:", src);
	}
	//*/

	// std::ranges::move_backward, std::ranges::move_backward_result C++20
	// moves a range of elements to a new location in backwards order
	// isto kao i ovo gore; stoga nista nije napisano nista	
	/*
	{
	}
	//*/

	// std::fill
	// copy-assigns the given value to every element in a range
	/*
	{
		std::vector<int> v{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		std::fill(v.begin(), v.end(), -1);
		for (auto& elem : v)
			std::cout << elem << " ";
		std::cout << "\n";
	}
	//*/

	// std::ranges::fill C++20
	// assigns a range of elements a certain value
	/*
	{
		std::vector<int> v{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		namespace ranges = std::ranges;
		ranges::fill(v.begin(), v.end(), -1);
		for (auto& elem : v)
			std::cout << elem << " ";
		std::cout << "\n";

		ranges::fill(v, 10);
		for (auto& elem : v)
			std::cout << elem << " ";
		std::cout << "\n";
	}
	//*/

	// std::fill_n	
	// copy-assigns the given value to N elements in a range
	/*
	{
		std::vector<int> v1{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		std::fill_n(v1.begin(), 5, -1);
		std::copy(begin(v1), end(v1), std::ostream_iterator<int>(std::cout, " "));
		std::cout << '\n';
	}
	//*/

	// std::ranges::fill_n C++20
	// assigns a value to a number of elements
	/*
	{
		constexpr auto n{ 8 };
		std::vector<std::string> v(n, "*");
		std::ranges::fill_n(v.begin(), n, "8");
	}
	//*/

	// std::transform
	// applies a function to a range of elements, storing results in a destination range
	/*
	{
		std::string s("hello");
		std::transform(s.begin(), s.end(), s.begin(),
			[](unsigned char c) -> unsigned char { return std::toupper(c); });

		std::vector<std::size_t> ordinals;
		std::transform(s.begin(), s.end(), std::back_inserter(ordinals),
			[](unsigned char c) -> std::size_t { return c; });

		std::cout << s << ':';
		for (auto ord : ordinals) {
			std::cout << ' ' << ord;
		}

		std::transform(ordinals.cbegin(), ordinals.cend(), ordinals.cbegin(),
			ordinals.begin(), std::plus<>{});

		std::cout << '\n';
		for (auto ord : ordinals) {
			std::cout << ord << ' ';
		}
		std::cout << '\n';
	}
	//*/

	// std::ranges::transform, std::ranges::unary_transform_result, std::ranges::binary_transform_result C++20
	// applies a function to a range of elements
	/*
	{
		std::string s("hello");
		namespace ranges = std::ranges;
		ranges::transform(s.begin(), s.end(), s.begin(),
			[](unsigned char c) -> unsigned char { return std::toupper(c); });

		std::vector<std::size_t> ordinals;
		ranges::transform(s, std::back_inserter(ordinals),
			[](unsigned char c) -> std::size_t { return c; });

		std::cout << s << ':';
		for (auto ord : ordinals)
			std::cout << ' ' << ord;

		ranges::transform(ordinals, ordinals, ordinals.begin(), std::plus{});
		// source, destination, niz koji koristi za operaciju, operacija

		std::cout << '\n';
		for (auto ord : ordinals)
			std::cout << ord << ' ';
		std::cout << '\n';

		struct Foo {
			char bar;
		};

		const std::vector<Foo> f = { {'h'},{'e'},{'l'},{'l'},{'o'} };
		std::string bar;
		ranges::transform(f, std::back_inserter(bar), &Foo::bar);
		std::cout << bar << '\n';
	}
	//*/

	// std::generate
	// assigns the results of successive function calls to every element in a range
	/*
	{
		auto f = []()
		{
			static int i;
			return ++i;
		};

		std::vector<int> v(5);
		auto print = [&] {
			for (std::cout << "v: "; auto iv: v)
				std::cout << iv << " ";
			std::cout << "\n";
		};

		std::generate(v.begin(), v.end(), f);
		print();

		// Initialize with default values 0,1,2,3,4 from a lambda function
		// Equivalent to std::iota(v.begin(), v.end(), 0);
		std::generate(v.begin(), v.end(), [n = 0]() mutable { return n++; });
		print();

	}
	//*/

	// std::ranges::generate C++20
	// saves the result of a function in a range
	/*
	{
		auto dice = []() {
			static std::uniform_int_distribution<int> distr{ 1, 6 };
			static std::random_device device;
			static std::mt19937 engine{ device() };
			return distr(engine);
		};

		vector<int> koka(10);
		std::ranges::generate(koka,
			[]() {static int i = 1; return i++; }
		);

		for (auto& i : koka)
			cout << i << " ";
		cout << "\n";

		std::ranges::generate(koka, dice);
		for (auto& i : koka)
			cout << i << " ";
		cout << "\n";
	}
	//*/

	// std::generate_n
	/*
	{
		std::mt19937 rng; // default constructed, seeded with fixed seed
		std::generate_n(
			std::ostream_iterator<std::mt19937::result_type>(std::cout, " "),
			5,
			std::ref(rng));
		std::cout << '\n';
	}
	//*/

	// std::ranges::generate_n C++20
	// assigns the results of successive function calls to N elements in a range
	/*
	{
		auto dice = []() {
			static std::uniform_int_distribution<int> distr{ 1, 6 };
			static std::random_device device;
			static std::mt19937 engine{ device() };
			return distr(engine);
		};

		std::array<int, 8> v;
		std::ranges::generate_n(v.begin(), v.size(), dice);
		for (auto& i : v)
			cout << i << " ";
		cout << "\n";

		std::ranges::generate_n(v.begin(), v.size(), [n{ 0 }]() mutable { return n++; });
		// same effect as std::iota(v.begin(), v.end(), 0);
		for (auto& i : v)
			cout << i << " ";
		cout << "\n";
	}
	//*/

	//std::remove, std::remove_if
	// removes elements satisfying specific criteria
	/*
	{
		std::string str1 = "Text with some   spaces";
		auto noSpaceEnd = std::remove(str1.begin(), str1.end(), ' ');

		// The spaces are removed from the string only logically.
		// Note, we use view, the original string is still not shrunk:
		std::cout << std::string_view(str1.begin(), noSpaceEnd)
			<< " size: " << str1.size() << '\n';

		str1.erase(noSpaceEnd, str1.end());

		// The spaces are removed from the string physically.
		std::cout << str1 << " size: " << str1.size() << '\n';

		std::string str2 = "Text\n with\tsome \t  whitespaces\n\n";
		str2.erase(std::remove_if(str2.begin(),
			str2.end(),
			[](unsigned char x) {return std::isspace(x); }),
			str2.end());
		std::cout << str2 << '\n';
	}
	//*/

	// std::ranges::remove, std::ranges::remove_if C++20
	// removes elements satisfying specific criteria
	/*
	{
		std::string v1{ "No - Diagnostic - Required" };
		std::cout << std::quoted(v1) << " (v1, size: " << v1.size() << ")\n";
		const auto ret = std::ranges::remove(v1, ' ');
		std::cout << std::quoted(v1) << " (v1 after `remove`, size: " << v1.size() << ")\n";
		//std::cout << ' ' << std::string(std::distance(v1.begin(), ret.begin()), '^') << '\n';
		std::cout << ' ' << std::string(std::distance(v1.begin(), ret.begin()), '^') << '\n';
		v1.erase(ret.begin(), ret.end());
		std::cout << std::quoted(v1) << " (v1 after `erase`, size: " << v1.size() << ")\n\n";

		// remove_if with custom unary predicate:
		auto rm = [](char c) { return !std::isupper(c); };
		std::string v2{ "Substitution Failure Is Not An Error" };
		std::cout << std::quoted(v2) << " (v2, size: " << v2.size() << ")\n";
		const auto [first, last] = std::ranges::remove_if(v2, rm);
		std::cout << std::quoted(v2) << " (v2 after `remove_if`, size: " << v2.size() << ")\n";
		std::cout << ' ' << std::string(std::distance(v2.begin(), first), '^') << '\n';
		v2.erase(first, last);
		std::cout << std::quoted(v2) << " (v2 after `erase`, size: " << v2.size() << ")\n\n";

		// creating a view into a container that is modified by `remove_if`:
		for (std::string s : {"Small Object Optimization", "Non-Type Template Parameter"}) {
			std::cout << quoted(s) << " => "
				<< std::string_view{ begin(s), std::ranges::remove_if(s, rm).begin() } << '\n';
		}
	}
	//*/

	// std::remove_copy, std::remove_copy_if
	// copies a range of elements omitting those that satisfy specific criteria
	/*
	{
		std::string str = "#Return #Value #Optimization";
		std::cout << "before: " << std::quoted(str) << "\n";

		std::cout << "after:  \"";
		std::remove_copy(
			str.begin(),
			str.end(),
			std::ostream_iterator<char>(std::cout), '#');

		std::cout << "\n";

		unique_ptr<char[]> buf(new char[str.size()]);
		auto t = std::remove_copy(
			str.begin(),
			str.end(),
			buf.get(),
			'#'
		);
		cout << buf << "\n";
	}
	//*/

	// std::ranges::remove_copy, std::ranges::remove_copy_if, std::ranges::remove_copy_result, std::ranges::remove_copy_if_result C++20
	// copies a range of elements omitting those that satisfy specific criteria
	/*
	{
		auto print = [](const auto rem, const auto& v) {
			std::cout << rem << ' ';
			for (const auto& e : v) { std::cout << e << ' '; };
			std::cout << '\n';
		};

		// Filter out the hash symbol from the given string.
		const std::string_view str{ "#Small #Buffer #Optimization" };
		std::cout << "before: " << std::quoted(str) << "\n";

		std::cout << "after:  \"";
		std::ranges::remove_copy(str.begin(), str.end(),
			std::ostream_iterator<char>(std::cout), '#');
		std::cout << "\"\n";


		// Copy only the complex numbers with positive imaginary part.
		using Ci = std::complex<int>;
		constexpr std::array<Ci, 5> source{
			Ci{1,0}, Ci{0,1}, Ci{2,-1}, Ci{3,2}, Ci{4,-3}
		};
		std::vector<std::complex<int>> target;

		std::ranges::remove_copy_if(source,
			std::back_inserter(target),
			[](int imag) { return imag <= 0; },
			[](Ci z) { return z.imag(); }
		);

		print("source:", source);
		print("target:", target);
	}
	//*/

	// std::replace, std::replace_if
	// replaces all values satisfying specific criteria with another value
	/*
	{
		std::array<int, 10> s{ 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 };
		std::replace(s.begin(), s.end(), 8, 88);

		for (int a : s)
			std::cout << a << " ";
		std::cout << '\n';

		std::replace_if(s.begin(), s.end(),
			std::bind(std::less<int>(), std::placeholders::_1, 5), 55);
		for (int a : s)
			std::cout << a << " ";
		std::cout << '\n';
	}
	//*/

	// std::ranges::replace, std::ranges::replace_if C++20
	// replaces all values satisfying specific criteria with another value
	/*
	{
		auto print = [](const auto& v) {
			for (const auto& e : v) { std::cout << e << ' '; }
			std::cout << '\n';
		};

		std::array p{ 1, 6, 1, 6, 1, 6 };
		print(p);
		std::ranges::replace(p, 6, 9);
		print(p);

		std::array q{ 1, 2, 3, 6, 7, 8, 4, 5 };
		print(q);
		std::ranges::replace_if(q, [](int x) { return 5 < x; }, 5);
		print(q);
	}
	//*/

	// std::replace_copy, std::replace_copy_if
	// copies a range, replacing elements satisfying specific criteria with another value
	/*
	{
		std::vector<int> v{ 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 };

		std::replace_copy_if(
			v.begin(),
			v.end(),
			std::ostream_iterator<int>(std::cout, " "),
			[](int n) {return n > 5; },
			99
		);
		std::cout << '\n';

		vector<int> dest(v.size());
		std::replace_copy_if(
			v.begin(),
			v.end(),
			dest.begin(),
			[](int n) {return n > 5; },
			99
		);

		// print dest
		for (int a : dest)
			std::cout << a << " ";

		std::cout << '\n';
	}
	//*/

	// std::ranges::replace_copy, std::ranges::replace_copy_if, std::ranges::replace_copy_result, std::ranges::replace_copy_if_result C++20
	// copies a range, replacing elements satisfying specific criteria with another value
	/*
	{
		auto print = [](const auto rem, const auto& v) {
			for (std::cout << rem << ": "; const auto & e : v)
				std::cout << e << ' ';
			std::cout << '\n';
		};

		std::vector<int> o;

		std::array p{ 1, 6, 1, 6, 1, 6 };
		o.resize(p.size());
		print("p", p);
		std::ranges::replace_copy(p, o.begin(), 6, 9);
		print("o", o);

		std::array q{ 1, 2, 3, 6, 7, 8, 4, 5 };
		o.resize(q.size());
		print("q", q);
		std::ranges::replace_copy_if(q, o.begin(), [](int x) { return 5 < x; }, 5);
		print("o", o);
	}
	//*/

	// std::swap
	// swaps the values of two objects
	/*
	{
		int min = 1;
		int max = 5;
		cout << "min: " << min << " max: " << max << '\n';
		std::swap(min, max);
		cout << "min: " << min << " max: " << max << '\n';

	}
	//*/

	// std::swap_ranges
	// swaps two ranges of elements
	/*
	{
		auto print = [](auto comment, auto const& seq) {
			std::cout << comment;
			for (const auto& e : seq) { std::cout << e << ' '; }
			std::cout << '\n';
		};

		std::vector<char> v = { 'a', 'b', 'c', 'd', 'e' };
		std::list<char> l = { '1', '2', '3', '4', '5' };

		print("Before swap_ranges:\n" "v: ", v);
		print("l: ", l);

		std::swap_ranges(v.begin(), v.begin() + 3, l.begin());

		print("After swap_ranges:\n" "v: ", v);
		print("l: ", l);

	}
	//*/

	// std::ranges::swap_ranges, std::ranges::swap_ranges_result C++20
	// swaps two ranges of elements
	/*
	{
		auto print = [](std::string_view name, auto const& seq, std::string_view term = "\n") {
			std::cout << name << " : ";
			for (const auto& elem : seq)
				std::cout << elem << ' ';
			std::cout << term;
		};

		std::vector<char>  p{ 'A', 'B', 'C', 'D', 'E' };
		std::list<char>    q{ '1', '2', '3', '4', '5', '6' };

		print("p", p);
		print("q", q, "\n\n");

		// swap p[0, 2) and q[1, 3):
		std::ranges::swap_ranges(p.begin(),
			p.begin() + 4,
			std::ranges::next(q.begin(), 1),
			std::ranges::next(q.begin(), 3));
		print("p", p);
		print("q", q, "\n\n");

		// swap p[0, 5) and q[0, 5):
		std::ranges::swap_ranges(p, q);

		print("p", p);
		print("q", q);
	}
	//*/

	// std::iter_swap
	// swaps the elements pointed to by two iterators
	// ovaj primer nesto ne radi
	/*
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(-9, +9);
		std::vector<int> v;
		std::generate_n(back_inserter(v), 20, bind(dist, gen));

		std::cout << "Before sort: " << std::showpos;
		for (auto e : v) std::cout << e << ' ';

		//for (auto i = v.begin(); i != v.end(); ++i)
		//	std::iter_swap(i, std::min_element(i, end));

		std::cout << "\nAfter sort : ";
		for (auto e : v) std::cout << e << ' ';
		std::cout << '\n';
	}
	//*/

	// std::reverse
	// reverses the order of elements in a range
	/*
	{
		std::cout << "vector" << '\n';
		std::vector<int> v{ 1, 2, 3 };
		for (auto e : v) std::cout << e;
		std::reverse(v.begin(), v.end());
		std::cout << '\n';
		for (auto e : v) std::cout << e;

		std::cout << '\n';
		std::cout << '\n';
		std::cout << "array int[]" << '\n';
		int a[] = { 4, 5, 6, 7 };
		for (auto e : a) std::cout << e;
		std::cout << '\n';
		std::reverse(std::begin(a), std::end(a));
		for (auto e : a) std::cout << e;
	}
	//*/

	// std::ranges::reverse C++20
	// reverses the order of elements in a range
	/*
	{
		std::string s{ "ABCDEF" };
		std::cout << s << " -> ";
		std::ranges::reverse(s.begin(), s.end());
		std::cout << s << " -> ";
		std::ranges::reverse(s);
		std::cout << s << " | ";

		std::array a{ 1, 2, 3, 4, 5 };
		for (auto e : a) { std::cout << e << ' '; }
		std::cout << "-> ";
		std::ranges::reverse(a);
		for (auto e : a) { std::cout << e << ' '; }
		std::cout << '\n';
	}
	//*/

	// std::reverse_copy
	// creates a copy of a range that is reversed
	/*
	{
		auto print = [](std::vector<int> const& v) {

			for (const auto& value : v)
				std::cout << value << ' ';
			std::cout << '\t';
		};

		std::vector<int> v({ 1,2,3 });
		print(v);

		std::vector<int> destination(3);
		std::reverse_copy(std::begin(v), std::end(v), std::begin(destination));
		print(destination);

		std::reverse_copy(std::rbegin(v), std::rend(v), std::begin(destination));
		print(destination);
	}
	//*/

	// std::ranges::reverse_copy, std::ranges::reverse_copy_result C++20
	// creates a copy of a range that is reversed
	/*
	{
		std::string x{ "12345" }, y(x.size(), ' ');
		std::cout << x << " -> ";
		std::ranges::reverse_copy(x.begin(), x.end(), y.begin());
		std::cout << y << " -> ";
		std::ranges::reverse_copy(y, x.begin());
		std::cout << x << '\n';
	}
	//*/

	// std::rotate
	// rotates the order of elements in a range
	// moze da se koristi za n pa i jednu ratociju levo / desno
	/*
	{
		auto print = [](auto const& remark, auto const& v) {
			std::cout << remark;
			for (int n : v)
				std::cout << n << ' ';
			std::cout << '\n';
		};
		std::vector<int> v{ 2, 4, 2, 0, 5, 10, 7, 3, 7, 1 };
		print("before sort:\t\t", v);

		// insertion sort
		for (auto i = v.begin(); i != v.end(); ++i)
			std::rotate(std::upper_bound(v.begin(), i, *i), i, i + 1);

		print("after sort:\t\t", v);
		// simple rotation to the left
		std::rotate(v.begin(), v.begin() + 1, v.end());
		print("simple rotate left:\t", v);
		// simple rotation to the right
		std::rotate(v.rbegin(), v.rbegin() + 1, v.rend());
		print("simple rotate right:\t", v);
	}
	//*/

	// std::ranges::rotate C++20
	// rotates the order of elements in a range
	/*
	{
		std::string s(16, ' ');

		std::iota(s.begin(), s.end(), 'A');
		std::cout << "Rotate left (" << 0 << "): " << s << '\n';
		for (int k{ 1 }; k != 5; ++k) {
			static int i = 1;
			std::ranges::rotate(s, s.begin() + i);
			std::cout << "Rotate left (" << k << "): " << s << '\n';
		}

		std::cout << '\n';

		for (int k{}; k != 5; ++k) {
			std::iota(s.begin(), s.end(), 'A');
			std::ranges::rotate(s, s.end() - k);
			std::cout << "Rotate right (" << k << "): " << s << '\n';
		}

		std::cout << "\n" "Insertion sort using `rotate`, step-by-step:\n";

		s = { '2', '4', '2', '0', '5', '9', '7', '3', '7', '1' };

		for (auto i = s.begin(); i != s.end(); ++i) {
			std::cout << "i = " << std::ranges::distance(s.begin(), i) << ": ";
			std::ranges::rotate(std::ranges::upper_bound(s.begin(), i, *i), i, i + 1);
			std::cout << s << '\n';
		}
		std::cout << (std::ranges::is_sorted(s) ? "Sorted!" : "Not sorted.") << '\n';


	}
	//*/

	// std::rotate_copy
	// copies and rotate a range of elements
	/*
	{
		std::vector<int> src = { 1, 2, 3, 4, 5 };
		std::vector<int> dest(src.size());
		auto pivot = std::find(src.begin(), src.end(), 3);

		std::rotate_copy(src.begin(), pivot, src.end(), dest.begin());
		for (int i : dest) {
			std::cout << i << ' ';
		}
		std::cout << '\n';

		// copy the rotation result directly to the std::cout
		pivot = std::find(dest.begin(), dest.end(), 1);
		std::rotate_copy(dest.begin(), pivot, dest.end(),
			std::ostream_iterator<int>(std::cout, " "));
		std::cout << '\n';
	}
	//*/

	// std::ranges::rotate_copy, std::ranges::rotate_copy_result C++20
	// copies and rotate a range of elements
	/*
	{
		std::vector<int> src{ 1, 2, 3, 4, 5 };
		std::vector<int> dest(src.size());
		auto pivot = std::ranges::find(src, 3);

		std::ranges::rotate_copy(src, pivot, dest.begin());
		for (int i : dest) { std::cout << i << ' '; }
		std::cout << '\n';

		// copy the rotation result directly to the std::cout
		pivot = std::ranges::find(dest, 1);
		std::ranges::rotate_copy(dest, pivot, std::ostream_iterator<int>(std::cout, " "));
		std::cout << '\n';
	}
	//*/

	// std::shift_left, std::shift_right C++20
	// shifts elements in a range
	// ovo se nesto cudno ponasa ako je vekotr stringova, brise karaktere koji ispadnu u siftu
	// za vektor intova radi kao kruzna lista
	/*
	{
		std::cout << std::left;

		std::vector<int>          b{ 1, 2, 3, 4, 5, 6, 7 };
		std::vector<std::string>  c{ "a", "b", "c", "d", "e", "f", "g" };

		std::cout << "vector<int> \tvector<string>\n";
		for (auto& i : b)
			cout << i << " ";
		cout << "\n\t\t";
		for (auto& i : c)
			cout << i << " ";
		cout << "\n";

		std::shift_left(begin(b), end(b), 3);
		std::shift_left(begin(c), end(c), 3);
		for (auto& i : b)
			cout << i << " ";
		cout << "\n\t\t";
		for (auto& i : c)
			cout << i << " ";
		cout << "\n";

		std::shift_right(begin(b), end(b), 2);
		std::shift_right(begin(c), end(c), 2);
		for (auto& i : b)
			cout << i << " ";
		cout << "\n\t\t";
		for (auto& i : c)
			cout << i << " ";
		cout << "\n";

		std::shift_left(begin(b), end(b), 8);  // ditto
		std::shift_left(begin(c), end(c), 8);  // ditto
		for (auto& i : b)
			cout << i << " ";
		cout << "\n\t\t";
		for (auto& i : c)
			cout << i << " ";
		cout << "\n";
	}
	//*/


	// std::ranges::shift_left, std::ranges::shift_right C++23
	// shifts elements in a range
	// isto kao prethnodno samo ranges moze bez begin i end da prihvati; stoga je bez primera
	/*
	{}
	//*/

	// std::random_shuffle, std::shuffle C++11 or C++17
	// randomly re-orders elements in a range
	/*
	{
		std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

		std::random_device rd;
		std::mt19937 g(rd());

		std::shuffle(v.begin(), v.end(), g);

		std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << "\n";
	}
	//*/

	// std::ranges::shuffle C++20
	// randomly re-orders elements in a range
	/*
	{
		auto print = [](const auto& a) {
			for (const auto e : a) { std::cout << e << ' '; }
			std::cout << "\n";
		};

		std::array a{ 'A', 'B', 'C', 'D', 'E', 'F' };
		print(a);

		std::random_device rd;
		std::mt19937 gen{ rd() };

		for (int i{}; i != 3; ++i) {
			std::ranges::shuffle(a, gen);
			print(a);
		}
	}
	//*/

	// std::sample C++17
	// selects n random elements from a sequence
	/*
	{
		std::string in = "hgfedcba", out;
		std::sample(in.begin(), in.end(), std::back_inserter(out),
			5, std::mt19937{ std::random_device{}() });
		std::cout << "five random letters out of " << in << " : " << out << '\n';
	}
	//*/

	// std::ranges::sample C++20
	// selects n random elements from a sequence
	/*
	{
		auto print = [](auto const& rem, auto const& v) {
			std::cout << rem << " = [" << std::size(v) << "] { ";
			for (auto const& e : v) {
				std::cout << e << ' ';
			}
			std::cout << "}\n";
		};

		const auto in = { 1, 2, 3, 4, 5, 6 };
		print("in", in);

		std::vector<int> out;
		const int max = in.size() + 2;
		auto gen = std::mt19937{ std::random_device{}() };

		for (int n{}; n != max; ++n) {
			out.clear();
			std::ranges::sample(in, std::back_inserter(out), n, gen);
			std::cout << "n = " << n;
			print(", out", out);
		}
	}
	//*/

	// std::unique
	// removes consecutive duplicate elements in a range
	/*
	{
		// a vector containing several duplicate elements
		std::vector<int> v{ 1,2,1,1,3,3,3,4,5,4 };
		auto print = [&](int id) {
			std::cout << "@" << id << ": ";
			for (int i : v)
				std::cout << i << ' ';
			std::cout << '\n';
		};
		print(1);

		// remove consecutive (adjacent) duplicates
		auto last = std::unique(v.begin(), v.end());
		// v now holds {1 2 1 3 4 5 4 x x x}, where 'x' is indeterminate
		v.erase(last, v.end());
		print(2);

		// sort followed by unique, to remove all duplicates
		std::sort(v.begin(), v.end()); // {1 1 2 3 4 4 5}
		print(3);

		last = std::unique(v.begin(), v.end());
		// v now holds {1 2 3 4 5 x x}, where 'x' is indeterminate
		v.erase(last, v.end());
		print(4);
	}
	//*/

	// std::ranges::unique C++20
	// removes consecutive duplicate elements in a range
	/*
	{
		struct id { int i; explicit id(int i) : i{ i } {} };

		auto print = [](id i, const auto& v) {
			std::cout << "@" << i.i << ": ";
			std::ranges::for_each(v, [](auto const& e) { std::cout << e << ' '; });
			std::cout << '\n';
		};

		// a vector containing several duplicate elements
		std::vector<int> v{ 1, 2, 1, 1, 3, 3, 3, 4, 5, 4 };

		print(id{ 1 }, v);

		// remove consecutive (adjacent) duplicates
		auto ret = std::ranges::unique(v);
		// v now holds {1 2 1 3 4 5 4 x x x}, where 'x' is indeterminate
		v.erase(ret.begin(), ret.end());
		print(id{ 2 }, v);

		// sort followed by unique, to remove all duplicates
		std::ranges::sort(v); // {1 1 2 3 4 4 5}
		print(id{ 3 }, v);

		auto [first, last] = std::ranges::unique(v.begin(), v.end());
		// v now holds {1 2 3 4 5 x x}, where 'x' is indeterminate
		v.erase(first, last);
		print(id{ 4 }, v);


		// unique with custom comparison and projection
		std::vector<std::complex<int>> vc{ {1, 1}, {-1, 2}, {-2, 3}, {2, 4}, {-3, 5} };
		print(id{ 5 }, vc);

		auto ret2 = std::ranges::unique(vc,
			[](int x, int y) { return std::abs(x) == std::abs(y); }, // comp
			[](std::complex<int> z) { return z.real(); }             // proj
		);
		vc.erase(ret2.begin(), ret2.end());
		print(id{ 6 }, vc);

	}
	//*/

	// std::unique_copy
	// creates a copy of some range of elements that contains no consecutive duplicates
	/*
	{
		std::string s1 = "The      string    with many       spaces!";
		std::cout << "before: " << s1 << '\n';

		std::string s2;
		std::unique_copy(s1.begin(), s1.end(), std::back_inserter(s2),
			[](char c1, char c2) { return c1 == ' ' && c2 == ' '; });

		std::cout << "after:  " << s2 << '\n';
	}
	//*/

	// std::ranges::unique_copy, std::ranges::unique_copy_result C++20
	// creates a copy of some range of elements that contains no consecutive duplicates
	/*
	{
		auto print = [](const auto& rem, const auto& v) {
			using V = std::remove_cvref_t<decltype(v)>;
			constexpr bool sep{ std::is_same_v<typename V::value_type, int> };
			std::cout << rem << std::showpos;
			for (const auto& e : v) std::cout << e << (sep ? " " : "");
			std::cout << '\n';
		};

		std::string s1{ "The      string    with many       spaces!" };
		print("s1: ", s1);

		std::string s2;
		std::ranges::unique_copy(
			s1.begin(), s1.end(), std::back_inserter(s2),
			[](char c1, char c2) { return c1 == ' ' && c2 == ' '; }
		);
		print("s2: ", s2);


		const auto v1 = { -1, +1, +2, -2, -3, +3, -3, };
		print("v1: ", v1);
		std::list<int> v2;
		std::ranges::unique_copy(
			v1, std::back_inserter(v2),
			{}, // default comparator std::ranges::equal_to
			[](int x) { return std::abs(x); } // projection
		);
		print("v2: ", v2);
	}
	//*/

	/****************************************************************************/
	// Partitioning operations
	// header <algorithm>
	/****************************************************************************/

	// std::is_partitioned C++11
	// determines if the range is partitioned by the given predicate
	// ne znam sta je ovo, nema mi smisla
	/*
	{
		std::array<int, 9> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		auto is_even = [](int i) { return i % 2 == 0; };
		std::cout.setf(std::ios_base::boolalpha);
		std::cout << std::is_partitioned(v.begin(), v.end(), is_even) << ' ';

		std::partition(v.begin(), v.end(), is_even);
		std::cout << std::is_partitioned(v.begin(), v.end(), is_even) << ' ';

		std::reverse(v.begin(), v.end());
		std::cout << std::is_partitioned(v.cbegin(), v.cend(), is_even) << ' ';
		std::cout << std::is_partitioned(v.crbegin(), v.crend(), is_even) << '\n';
	}
	//*/

	// std::ranges::is_partitioned C++20
	// determines if the range is partitioned by the given predicate
	/*
	{
		std::array<int, 9> v;

		auto is_even = [](int i) { return i % 2 == 0; };
		auto print = [&](bool o) {
			for (int x : v) std::cout << x << ' ';
			std::cout << (o ? "=> " : "=> not ") << "partitioned\n";
		};

		std::iota(v.begin(), v.end(), 1);
		print(std::ranges::is_partitioned(v, is_even));

		std::ranges::partition(v, is_even);
		print(std::ranges::is_partitioned(std::as_const(v), is_even));

		std::ranges::reverse(v);
		print(std::ranges::is_partitioned(v.cbegin(), v.cend(), is_even));
		print(std::ranges::is_partitioned(v.crbegin(), v.crend(), is_even));
	}
	//*/

	// std::partition
	// divides a range of elements into two groups
	/*
	{
		std::vector<int> v = { 0,1,2,3,4,5,6,7,8,9 };
		std::cout << "Original vector:\n    ";
		for (int elem : v) std::cout << elem << ' ';

		auto it = std::partition(v.begin(), v.end(), [](int i) {return i % 2 == 0; });

		std::cout << "\nPartitioned vector:\n    ";
		std::copy(std::begin(v), it, std::ostream_iterator<int>(std::cout, " "));
		std::cout << " * " " ";
		std::copy(it, std::end(v), std::ostream_iterator<int>(std::cout, " "));

	}
	//*/

	// std::ranges::partition
	// divides a range of elements into two groups
	/*
	{
		std::ostream_iterator<int> cout{ std::cout, " " };

		std::vector<int> v{ 0,1,2,3,4,5,6,7,8,9 };
		std::cout << "Original vector:  \t";
		ranges::copy(v, cout);

		auto tail = ranges::partition(v, [](int i) {return i % 2 == 0; });

		std::cout << "\nPartitioned vector: \t";
		ranges::copy(ranges::begin(v), ranges::begin(tail), cout);
		std::cout << "| ";
		ranges::copy(tail, cout);

	}
	//*/

	// std::partition_copy
	// copies a range dividing the elements into two groups C++11
	/*
	{
		int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
		int true_arr[5] = { 0 };
		int false_arr[5] = { 0 };

		std::partition_copy(std::begin(arr), std::end(arr), std::begin(true_arr), std::begin(false_arr),
			[](int i) {return i > 5; });

		std::cout << "true_arr: ";
		for (int x : true_arr) {
			std::cout << x << ' ';
		}
		std::cout << '\n';

		std::cout << "false_arr: ";
		for (int x : false_arr) {
			std::cout << x << ' ';
		}
		std::cout << '\n';

		return 0;
	}
	//*/

	// std::ranges::partition_copy, std::ranges::partition_copy_result C++20
	// copies a range dividing the elements into two groups
	/*
	{
		const auto in = { 'N', '3', 'U', 'M', '1', 'B', '4', 'E', '1', '5', 'R', '9' };

		std::vector<int> o1(size(in)), o2(size(in));

		auto pred = [](char c) { return std::isalpha(c); };

		auto ret = std::ranges::partition_copy(in, o1.begin(), o2.begin(), pred);

		std::ostream_iterator<char> cout{ std::cout, " " };
		std::cout << "in = ";
		std::ranges::copy(in, cout);
		std::cout << "\no1 = ";
		std::copy(o1.begin(), ret.out1, cout);
		std::cout << "\no2 = ";
		std::copy(o2.begin(), ret.out2, cout);
		std::cout << '\n';
	}
	//*/

	// std::stable_partition
	// divides elements into two groups while preserving their relative order
	/*
	{
		std::vector<int> v{ 0, 0, 3, -1, 2, 4, 5, 0, 7 };
		std::stable_partition(v.begin(), v.end(), [](int n) {return n > 0; });
		for (int n : v) {
			std::cout << n << ' ';
		}
		std::cout << '\n';
	}
	//*/

	// std::ranges::stable_partition C++20
	// copies a range dividing the elements into two groups
	/*
	{
		auto print = [](const auto rem, auto first, auto last, bool end = true) {
			std::cout << rem;
			for (; first != last; ++first) { std::cout << *first << ' '; }
			std::cout << (end ? "\n" : "");
		};
		namespace rng = std::ranges;

		const auto original = { 9, 6, 5, 2, 3, 1, 7, 8 };

		std::vector<int> vi;
		auto even = [](int x) { return 0 == (x % 2); };

		print("Original vector:\t", original.begin(), original.end(), "\n");

		vi = original;
		const auto ret1 = rng::stable_partition(vi, even);
		print("Stable partitioned:\t", vi.begin(), ret1.begin(), 0);
		print("| ", ret1.begin(), ret1.end());

		vi = original;
		const auto ret2 = rng::partition(vi, even);
		print("Partitioned:\t\t", vi.begin(), ret2.begin(), 0);
		print("| ", ret2.begin(), ret2.end());


		vi = { 16, 30, 44, 30, 15, 24, 10, 18, 12, 35 };
		print("Unsorted vector: ", vi.begin(), vi.end());

		stable_sort(rng::begin(vi), rng::end(vi));
		print("Sorted vector:   ", vi.begin(), vi.end());
	}
	//*/

	// std::partition_point C++11
	// locates the partition point of a partitioned range
	/*
	{
		auto print_seq = [](auto rem, auto first, auto last) {
			for (std::cout << rem; first != last; std::cout << *first++ << ' ') {}
			std::cout << '\n';
		};

		std::array v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		auto is_even = [](int i) { return i % 2 == 0; };

		std::partition(v.begin(), v.end(), is_even);
		print_seq("After partitioning, v: ", v.cbegin(), v.cend());

		const auto pp = std::partition_point(v.cbegin(), v.cend(), is_even);
		const auto i = std::distance(v.cbegin(), pp);
		std::cout << "Partition point is at " << i << "; v[" << i << "] = " << *pp << '\n';

		print_seq("First partition (all even elements): ", v.cbegin(), pp);
		print_seq("Second partition (all odd elements): ", pp, v.cend());
	}
	//*/

	// std::ranges::partition_point C++20
	// locates the partition point of a partitioned range
	/*
	{
		auto print_seq = [](auto rem, auto first, auto last) {
			for (std::cout << rem; first != last; std::cout << *first++ << ' ') {}
			std::cout << '\n';
		};

		std::array v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		auto is_even = [](int i) { return i % 2 == 0; };

		std::ranges::partition(v, is_even);
		print_seq("After partitioning, v: ", v.cbegin(), v.cend());

		const auto pp = std::ranges::partition_point(v, is_even);
		const auto i = std::ranges::distance(v.cbegin(), pp);
		std::cout << "Partition point is at " << i << "; v[" << i << "] = " << *pp << '\n';

		print_seq("First partition (all even elements): ", v.cbegin(), pp);
		print_seq("Second partition (all odd elements): ", pp, v.cend());
	}
	//*/

	/****************************************************************************/
	// Sorting operations
	// header <algorithm>
	/****************************************************************************/

	// std::is_sorted
	// std::ranges::is_sorted C++20
	// checks whether a range is sorted into ascending order
	/*
	{
		int digits[] = { 3, 1, 4, 1, 5 };

		for (auto i : digits) std::cout << i << ' ';
		std::cout << ": is_sorted: " << std::boolalpha
			<< std::is_sorted(std::begin(digits), std::end(digits)) << '\n';

		std::cout << ": is_sorted: " << std::boolalpha
			<< std::ranges::is_sorted(digits) << '\n';



		std::sort(std::begin(digits), std::end(digits));

		for (auto i : digits) std::cout << i << ' ';
		std::cout << ": is_sorted: "
			<< std::is_sorted(std::begin(digits), std::end(digits)) << '\n';
	}
	//*/

	// std::is_sorted_until
	// finds the largest sorted subrange
	/*
	{
		std::random_device rd;
		std::mt19937 g(rd());
		const int N = 6;
		int nums[N] = { 3, 1, 4, 1, 5, 9 };

		const int min_sorted_size = 4;
		int sorted_size = 0;
		do {
			std::shuffle(nums, nums + N, g);
			int* sorted_end = std::is_sorted_until(nums, nums + N);
			sorted_size = std::distance(nums, sorted_end);

			for (auto i : nums) std::cout << i << ' ';
			std::cout << " : " << sorted_size << " initial sorted elements\n";
		} while (sorted_size < min_sorted_size);
	}


	//
	/*
	{
	}
	//*/

	//std::ranges::is_sorted_until
	// finds the largest sorted subrange
	/*
	{
		std::random_device rd;
		std::mt19937 g{ rd() };
		std::array nums{ 3, 1, 4, 1, 5, 9 };

		constexpr int min_sorted_size = 4;
		int sorted_size = 0;
		do {
			std::ranges::shuffle(nums, g);
			const auto sorted_end = std::ranges::is_sorted_until(nums);
			sorted_size = std::ranges::distance(nums.begin(), sorted_end);

			std::ranges::copy(nums, std::ostream_iterator<int>(std::cout, " "));
			std::cout << " : " << sorted_size << " leading sorted element(s)\n";
		} while (sorted_size < min_sorted_size);
	}
	//*/

	// std::sort
	// sorts a range into ascending order
	/*
	{
		std::array<int, 10> s = { 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 };

		auto print = [&s](std::string_view const rem) {
			for (auto a : s) {
				std::cout << a << ' ';
			}
			std::cout << ": " << rem << '\n';
		};

		std::sort(s.begin(), s.end());
		print("sorted with the default operator<");

		std::sort(s.begin(), s.end(), std::greater<int>());
		print("sorted with the standard library compare function object");

		struct {
			bool operator()(int a, int b) const { return a < b; }
		} customLess;
		std::sort(s.begin(), s.end(), customLess);
		print("sorted with a custom function object");

		std::sort(s.begin(), s.end(), [](int a, int b) {
			return a > b;
			});
		print("sorted with a lambda expression");
	}
	//*/

	// std::ranges::sort C++20
	// sorts a range into ascending order
	/*
	{
		void print(auto comment, auto const& seq, char term = ' ') {
			for (std::cout << comment << '\n'; auto const& elem : seq)
				std::cout << elem << term;
			std::cout << '\n';
		};

		struct Particle {
			std::string name; double mass; // MeV
			template<class Os> friend
				Os& operator<< (Os& os, Particle const& p) {
				return os << std::left << std::setw(8) << p.name << " : " << p.mass << ' ';
			}
		};

		std::array s{ 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 };
		namespace ranges = std::ranges;

		ranges::sort(s);
		print("Sort using the default operator<", s);

		ranges::sort(s, ranges::greater());
		print("Sort using a standard library compare function object", s);

		struct {
			bool operator()(int a, int b) const { return a < b; }
		} customLess;
		ranges::sort(s.begin(), s.end(), customLess);
		print("Sort using a custom function object", s);

		ranges::sort(s, [](int a, int b) { return a > b; });
		print("Sort using a lambda expression", s);

		Particle particles[]{
			{"Electron", 0.511}, {"Muon", 105.66}, {"Tau", 1776.86},
			{"Positron", 0.511}, {"Proton", 938.27}, {"Neutron", 939.57},
		};
		ranges::sort(particles, {}, & Particle::name);
		print("\nSort by name using a projection", particles, '\n');
		ranges::sort(particles, {}, & Particle::mass);
		print("Sort by mass using a projection", particles, '\n');

		}
	//*/

	// std::partial_sort
	// sorts the first N elements of a range
	/*
	{
		auto print = [](auto const& s, int middle) {
			for (int a : s) { std::cout << a << ' '; }
			std::cout << '\n';
			if (middle > 0) {
				while (middle-- > 0) { std::cout << "--"; }
				std::cout << '^';
			}
			else if (middle < 0) {
				for (auto i = s.size() + middle; --i; std::cout << "  ");
				for (std::cout << '^'; middle++ < 0; std::cout << "--");
			}
			std::cout << '\n';
		};
		std::array<int, 10> s{ 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 };

		print(s, 0);
		std::partial_sort(s.begin(), s.begin() + 3, s.end());
		print(s, 3);
		std::partial_sort(s.rbegin(), s.rbegin() + 4, s.rend());
		print(s, -4);
		std::partial_sort(s.rbegin(), s.rbegin() + 5, s.rend(), std::greater{});
		print(s, -5);
	}
	//*/

	// std::ranges::partial_sort C++20
	// sorts the first N elements of a range
	/*
	{
		auto print = [](const auto& v) {
			for (const char e : v) { std::cout << e << ' '; }
			std::cout << '\n';
		};

		auto underscore = [](int n) {
			while (n-- > 0) { std::cout << "^ "; }
			std::cout << '\n';
		};
		static_assert('A' < 'a');
		std::vector<char> v{ 'x', 'P', 'y', 'C', 'z', 'w', 'P', 'o' };
		print(v);
		std::ranges::partial_sort(v, v.begin() + 3);
		print(v); underscore(3);

		static_assert('1' < 'a');
		std::string s{ "3a1b41c5" };
		print(s);
		std::ranges::partial_sort(s.begin(), s.begin() + 3, s.end(), std::greater{});
		print(s); underscore(3);
	}
	//*/

	// std::partial_sort_copy
	// copies and partially sorts a range of elements
	/*
	{
		const auto v0 = { 4, 2, 5, 1, 3 };
		std::vector<int> v1{ 10, 11, 12 };
		std::vector<int> v2{ 10, 11, 12, 13, 14, 15, 16 };
		std::vector<int>::iterator it;

		it = std::partial_sort_copy(v0.begin(), v0.end(), v1.begin(), v1.end());

		std::cout << "Writing to the smaller vector in ascending order gives: ";
		for (int a : v1) {
			std::cout << a << " ";
		}
		std::cout << '\n';
		if (it == v1.end())
			std::cout << "The return value is the end iterator\n";

		it = std::partial_sort_copy(v0.begin(), v0.end(), v2.begin(), v2.end(),
			std::greater<int>());

		std::cout << "Writing to the larger vector in descending order gives: ";
		for (int a : v2) {
			std::cout << a << " ";
		}
		std::cout << '\n' << "The return value is the iterator to " << *it << '\n';
	}
	//*/

	// std::ranges::partial_sort_copy, std::ranges::partial_sort_copy_result C++20
	// copies and partially sorts a range of elements
	/*
	{
		auto print = [](std::string_view rem, std::ranges::input_range auto const& v)
		{
			for (std::cout << rem; const auto & e : v)
				std::cout << e << ' ';
			std::cout << '\n';
		};

		const std::forward_list source{ 4, 2, 5, 1, 3 };

		print("Write to the smaller vector in ascending order: ", "");

		std::vector dest1{ 10, 11, 12 };
		print("const source list: ", source);
		print("destination range: ", dest1);
		std::ranges::partial_sort_copy(source, dest1);
		print("partial_sort_copy: ", dest1);

		print("Write to the larger vector in descending order:", "");

		std::vector dest2{ 10, 11, 12, 13, 14, 15, 16 };
		print("const source list: ", source);
		print("destination range: ", dest2);
		std::ranges::partial_sort_copy(source, dest2, std::greater{});
		print("partial_sort_copy: ", dest2);
	}
	//*/

	// std::stable_sort
	// sorts a range of elements while preserving order between equal elements
	/*
	{
		struct Employee
		{
			int age;
			std::string name;  // Does not participate in comparisons
		};

		std::vector<Employee> v =
		{
			{108, "Zaphod"},
			{32, "Arthur"},
			{108, "Ford"},
		};

		std::stable_sort(v.begin(), v.end(),
			[](const Employee& lhs, const Employee& rhs)
			{
				return lhs.age < rhs.age;
			}
		);

		for (const Employee& e : v)
			std::cout << e.age << ", " << e.name << '\n';

	}
	//*/

	// std::ranges::stable_sort C++20
	// sorts a range of elements while preserving order between equal elements
	/*
	{
		struct Particle {
			std::string name; double mass; // MeV
		};

		auto print = [](const array<int, 10>& seq) {
			for (auto const& elem : seq)
				std::cout << elem << ' ';
			std::cout << '\n';
		};


		std::array s{ 5, 7, 4, 2, 8, 6, 1, 9, 0, 3 };

		// sort using the default operator<
		std::ranges::stable_sort(s);
		print(s);

		// sort using a standard library compare function object
		std::ranges::stable_sort(s, std::ranges::greater());
		print(s);

		// sort using a custom function object
		struct {
			bool operator()(int a, int b) const {
				return a < b;
			}
		} customLess;
		std::ranges::stable_sort(s.begin(), s.end(), customLess);
		print(s);

		// sort using a lambda expression
		std::ranges::stable_sort(s, [](int a, int b) {
			return a > b;
			});
		print(s);

		// sort with projection
		Particle particles[]{
			{"Electron", 0.511}, {"Muon", 105.66}, {"Tau", 1776.86},
			{"Positron", 0.511}, {"Proton", 938.27}, {"Neutron", 939.57},
		};
		for (auto const& elem : particles)
			std::cout << elem.name << ' ' << elem.mass << '\n';
		std::cout << '\n';

		std::ranges::stable_sort(particles, {}, & Particle::name); //< sort by name
		for (auto const& elem : particles)
			std::cout << elem.name << ' ' << elem.mass << '\n';
		std::cout << '\n';

		std::ranges::stable_sort(particles, {}, & Particle::mass); //< sort by mass
		for (auto const& elem : particles)
			std::cout << elem.name << ' ' << elem.mass << '\n';
		std::cout << '\n';
	}
	//*/

	// std::nth_element
	// partially sorts the given range making sure that it is partitioned by the given element
	/*
	{
		auto printVec = [](const std::vector<int>& vec) {
			std::cout << "v= {";
			for (int i : vec)
				std::cout << i << ", ";
			std::cout << "}\n";
		};

		std::vector<int> v{ 5, 10, 6, 4, 3, 2, 6, 7, 9, 3 };
		printVec(v);

		auto m = v.begin() + v.size() / 2;
		std::nth_element(v.begin(), m, v.end());
		std::cout << "\nThe median is " << v[v.size() / 2] << '\n';
		// The consequence of the inequality of elements before/after the Nth one:
		//assert(std::accumulate(v.begin(), m, 0) < std::accumulate(m, v.end(), 0));
		printVec(v);

		// Note: comp function changed
		std::nth_element(v.begin(), v.begin() + 1, v.end(), std::greater{});
		std::cout << "\nThe second largest element is " << v[1] << '\n';
		std::cout << "The largest element is " << v[0] << '\n';
		printVec(v);
	}
	//*/

	// std::ranges::nth_element C++20
	// partially sorts the given range making sure that it is partitioned by the given element
	/*
	{
		auto print = [](std::string_view rem, std::ranges::input_range auto const& a)
		{
			for (std::cout << rem; const auto e : a)
				std::cout << e << ' ';
			std::cout << "\n";
		};

		std::array v{ 5, 6, 4, 3, 2, 6, 7, 9, 3 };
		print("Before nth_element: ", v);

		std::ranges::nth_element(v, v.begin() + v.size() / 2);
		print("After nth_element:  ", v);
		std::cout << "The median is: " << v[v.size() / 2] << '\n';

		std::ranges::nth_element(v, v.begin() + 1, std::greater<int>());
		print("After nth_element:  ", v);
		std::cout << "The second largest element is: " << v[1] << '\n';
		std::cout << "The largest element is: " << v[0] << "\n\n";


		using namespace std::literals;
		std::array names{
			"Diva"sv, "Cornelius"sv, "Munro"sv, "Rhod"sv,
			"Zorg"sv, "Korben"sv, "Bender"sv, "Leeloo"sv,
		};
		print("Before nth_element: ", names);
		auto fifth_element{ std::ranges::next(names.begin(), 4) };
		std::ranges::nth_element(names, fifth_element);
		print("After nth_element:  ", names);
		std::cout << "The 5th element is: " << *fifth_element << '\n';

	}
	//*/

	/****************************************************************************/
	// Sorting operations
	/****************************************************************************/

	// std::lower_bound
	// std::ranges::lower_bound C++20
	// returns an iterator to the first element not less than the given value
	/*
	{
		struct PriceInfo { double price; };

		const std::vector<int> data = { 1, 2, 4, 5, 5, 6 };
		for (int i = 0; i < 8; ++i) {
			// Search for first element x such that i <= x
			auto lower = std::lower_bound(data.begin(), data.end(), i);

			std::cout << i << " <= ";
			lower != data.end()
				? std::cout << *lower << " at index " << std::distance(data.begin(), lower)
				: std::cout << "not found";
			std::cout << '\n';
		}

		std::vector<PriceInfo> prices = { {100.0}, {101.5}, {102.5}, {102.5}, {107.3} };
		for (double to_find : {102.5, 110.2}) {
			auto prc_info = std::lower_bound(prices.begin(), prices.end(), to_find,
				[](const PriceInfo& info, double value) {
					return info.price < value;
				});

			prc_info != prices.end()
				? std::cout << prc_info->price << " at index " << prc_info - prices.begin()
				: std::cout << to_find << " not found";
			std::cout << '\n';
		}
	}
	//*/

	// std::upper_bound
	// std::ranges::upper_bound C++20
	// returns an iterator to the first element greater than a certain value
	/*
	{
		struct PriceInfo { double price; };

		const std::vector<int> data = { 1, 2, 4, 5, 5, 6 };
		for (int i = 0; i < 7; ++i) {
			// Search first element that is greater than i
			auto upper = std::upper_bound(data.begin(), data.end(), i);

			std::cout << i << " < ";
			upper != data.end()
				? std::cout << *upper << " at index " << std::distance(data.begin(), upper)
				: std::cout << "not found";
			std::cout << '\n';
		}

		std::vector<PriceInfo> prices = { {100.0}, {101.5}, {102.5}, {102.5}, {107.3} };
		for (double to_find : {102.5, 110.2}) {
			auto prc_info = std::upper_bound(prices.begin(), prices.end(), to_find,
				[](double value, const PriceInfo& info) {
					return value < info.price;
				});

			prc_info != prices.end()
				? std::cout << prc_info->price << " at index " << prc_info - prices.begin()
				: std::cout << to_find << " not found";
			std::cout << '\n';
		}
	}
	//*/

	// std::ranges::upper_bound C++20
	// returns an iterator to the first element greater than a certain value
	/*
	{
		namespace ranges = std::ranges;
		std::vector<int> data = { 1, 1, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6 };

		{
			auto lower = ranges::lower_bound(data.begin(), data.end(), 4);
			auto upper = ranges::upper_bound(data.begin(), data.end(), 4);

			ranges::copy(lower, upper, std::ostream_iterator<int>(std::cout, " "));
			std::cout << '\n';
		}
		{
			auto lower = ranges::lower_bound(data, 3);
			auto upper = ranges::upper_bound(data, 3);

			ranges::copy(lower, upper, std::ostream_iterator<int>(std::cout, " "));
			std::cout << '\n';
		}
	}
	//*/

	// std::binary_search
	// determines if an element exists in a certain range
	/*
	{
		std::vector<int> haystack{ 1, 3, 4, 5, 9 };
		std::vector<int> needles{ 1, 2, 3 };

		for (auto needle : needles) {
			std::cout << "Searching for " << needle << '\n';
			if (std::binary_search(haystack.begin(), haystack.end(), needle)) {
				std::cout << "Found " << needle << '\n';
			}
			else {
				std::cout << "no dice!\n";
			}
		}
	}
	//*/

	// std::ranges::binary_search C++20
	// determines if an element exists in a certain range
	/*
	{
		auto haystack = { 1, 3, 4, 5, 9 };
		auto needles = { 1, 2, 3 };

		for (const int needle : needles) {
			std::cout << "Searching for " << needle << ": ";
			std::ranges::binary_search(haystack, needle)
				? std::cout << "found " << needle << '\n'
				: std::cout << "no dice!\n";
		}
	}
	//*/

	// std::equal_range
	// std::ranges::equal_range C++20
	// returns range of elements matching a specific key
	/*
	{
		struct S
		{
			int number;
			char name;
			// note: name is ignored by this comparison operator
			bool operator< (const S& s) const { return number < s.number; }
		};

		// note: not ordered, only partitioned w.r.t. S defined below
		const std::vector<S> vec = { {1,'A'}, {2,'B'}, {2,'C'}, {2,'D'}, {4,'G'}, {3,'F'} };

		const S value = { 2, '?' };

		std::cout << "Compare using S::operator<(): ";
		const auto p = std::equal_range(vec.begin(), vec.end(), value);

		for (auto i = p.first; i != p.second; ++i)
			std::cout << i->name << ' ';


		std::cout << "\n" "Using heterogeneous comparison: ";
		struct Comp
		{
			bool operator() (const S& s, int i) const { return s.number < i; }
			bool operator() (int i, const S& s) const { return i < s.number; }
		};

		const auto p2 = std::equal_range(vec.begin(), vec.end(), 2, Comp{});

		for (auto i = p2.first; i != p2.second; ++i)
			std::cout << i->name << ' ';
	}
	//*/

	/****************************************************************************/
	// Other operations on sorted ranges
	// Sorting operations
	/****************************************************************************/

	// std::merge
	// merges two sorted ranges
	/*
	{
		auto print = [](auto const rem, auto const& v)
		{
			std::cout << rem;
			std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
			std::cout << '\n';
		};

		// fill the vectors with random numbers
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<> dis(0, 9);

		std::vector<int> v1(10), v2(10);
		std::generate(v1.begin(), v1.end(), std::bind(dis, std::ref(mt)));
		std::generate(v2.begin(), v2.end(), std::bind(dis, std::ref(mt)));

		print("Originally:\nv1: ", v1);
		print("v2: ", v2);

		std::sort(v1.begin(), v1.end());
		std::sort(v2.begin(), v2.end());

		print("After sorting:\nv1: ", v1);
		print("v2: ", v2);

		// merge
		std::vector<int> dst;
		std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(dst));

		print("After merging:\ndst: ", dst);
	}
	//*/

	// std::ranges::merge, std::ranges::merge_result C++20
	// merges two sorted ranges
	/*
	{
		auto print = [](const auto& in1, const auto& in2, auto first, auto last) {
			std::cout << "{ ";
			for (const auto& e : in1) { std::cout << e << ' '; }
			std::cout << "} +\n{ ";
			for (const auto& e : in2) { std::cout << e << ' '; }
			std::cout << "} =\n{ ";
			while (!(first == last)) { std::cout << *first++ << ' '; }
			std::cout << "}\n\n";
		};

		std::vector<int> in1, in2, out;

		in1 = { 1, 2, 3, 4, 5 };
		in2 = { 3, 4, 5, 6, 7 };
		out.resize(in1.size() + in2.size());
		const auto ret = std::ranges::merge(in1, in2, out.begin());
		print(in1, in2, out.begin(), ret.out);

		in1 = { 1, 2, 3, 4, 5, 5, 5 };
		in2 = { 3, 4, 5, 6, 7 };
		out.clear();
		out.reserve(in1.size() + in2.size());
		std::ranges::merge(in1, in2, std::back_inserter(out));
		print(in1, in2, out.cbegin(), out.cend());
	}
	//*/

	// std::inplace_merge
	// merges two ordered ranges in-place
	/*
	{
		template<class Iter>
		void merge_sort(Iter first, Iter last)
		{
			if (last - first > 1) {
				Iter middle = first + (last - first) / 2;
				merge_sort(first, middle);
				merge_sort(middle, last);
				std::inplace_merge(first, middle, last);
			}
		};

		std::vector<int> v{ 8, 2, -2, 0, 11, 11, 1, 7, 3 };
		//merge_sort(v.begin(), v.end());
		merge_sort(v.begin(), v.end());
		for (auto n : v) {
			std::cout << n << ' ';
		}
		std::cout << '\n';
	}
	//*/

	// std::ranges::inplace_merge C++20
	// merges two ordered ranges in-place
	/*
	{
		auto print = [](auto const& v, auto const& rem, int middle = -1)
		{
			for (int i{}; auto n : v)
				std::cout << (i++ == middle ? "| " : "") << n << ' ';
			std::cout << rem << '\n';
		};

		template <std::random_access_iterator I, std::sentinel_for<I> S>
			requires std::sortable<I>
		void merge_sort(I first, S last)
		{
			if (last - first > 1) {
				I middle{ first + (last - first) / 2 };
				merge_sort(first, middle);
				merge_sort(middle, last);
				std::ranges::inplace_merge(first, middle, last);
			}
		}

		// custom merge-sort demo
		std::vector v{ 8, 2, 0, 4, 9, 8, 1, 7, 3 };
		print(v, ": before sort");
		merge_sort(v.begin(), v.end());
		print(v, ": after sort\n");

		// merging with comparison function object and projection
		using CI = std::complex<int>;
		std::vector<CI> r{ {0,1}, {0,2}, {0,3}, {1,1}, {1,2} };
		const auto middle{ std::ranges::next(r.begin(), 3) };
		auto comp{ std::ranges::less{} };
		auto proj{ [](CI z) { return z.imag(); } };

		print(r, ": before merge", middle - r.begin());
		std::ranges::inplace_merge(r, middle, comp, proj);
		print(r, ": after merge");
	}
	//*/

	/****************************************************************************/
	// Set operations (on sorted ranges)
	// Sorting operations
	/****************************************************************************/

	// std::includes
	// std::ranges::includes C++20
	// returns true if one sequence is a subsequence of another
	/*
	{
		const auto
			v1 = { 'a', 'b', 'c', 'f', 'h', 'x' },
			v2 = { 'a', 'b', 'c' },
			v3 = { 'a', 'c' },
			v4 = { 'a', 'a', 'b' },
			v5 = { 'g' },
			v6 = { 'a', 'c', 'g' },
			v7 = { 'A', 'B', 'C' };

		auto no_case = [](char a, char b) { return std::tolower(a) < std::tolower(b); };

		std::cout << "\nincludes:\n" << std::boolalpha;
		std::cout << std::includes(v1.begin(), v1.end(), v2.begin(), v2.end()) << '\n';
		std::cout << std::includes(v1.begin(), v1.end(), v3.begin(), v3.end()) << '\n';
		std::cout << std::includes(v1.begin(), v1.end(), v4.begin(), v4.end()) << '\n';
		std::cout << std::includes(v1.begin(), v1.end(), v5.begin(), v5.end()) << '\n';
		std::cout << std::includes(v1.begin(), v1.end(), v6.begin(), v6.end()) << '\n';
		std::cout << std::includes(v1.begin(), v1.end(), v7.begin(), v7.end(), no_case)
			<< " (case-insensitive)\n";

	}
	//*/

	// std::set_difference
	// computes the difference between two sets
	/*
	{
		auto print = [](const auto& v, std::string_view end = "") {
			std::cout << "{ ";
			for (auto i : v) std::cout << i << ' ';
			std::cout << "} " << end;
		};

		struct Order // a struct with some interesting data
		{
			int order_id;

			friend std::ostream& operator<<(std::ostream& os, const Order& ord) {
				return os << ord.order_id << ',';
			}
		};

		const std::vector<int> v1{ 1, 2, 5, 5, 5, 9 };
		const std::vector<int> v2{ 2, 5, 7 };
		std::vector<int> diff;

		std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(),
			std::inserter(diff, diff.begin()));
		print(v1, "\ ");
		print(v2, "= ");
		print(diff, "\n");

		// we want to know which orders "cut" between old and new states:
		std::vector<Order> old_orders{ {1}, {2}, {5}, {9} };
		std::vector<Order> new_orders{ {2}, {5}, {7} };
		std::vector<Order> cut_orders;

		std::set_difference(old_orders.begin(), old_orders.end(),
			new_orders.begin(), new_orders.end(),
			std::back_inserter(cut_orders),
			[](auto& a, auto& b) { return a.order_id < b.order_id; });

		std::cout << "old orders = "; print(old_orders, "\n");
		std::cout << "new orders = "; print(new_orders, "\n");
		std::cout << "cut orders = "; print(cut_orders, "\n");
	}
	//*/

	// std::ranges::set_difference, std::ranges::set_difference_result C++20
	// computes the difference between two sets
	/*
	{
		auto print = [](const auto& v, std::string_view end = "") {
			for (std::cout << "{ "; auto i : v) std::cout << i << ' ';
			std::cout << "} " << end;
		};

		struct Order // a struct with some very interesting data
		{
			int order_id;

			friend std::ostream& operator<<(std::ostream& os, const Order& ord) {
				return os << "{" << ord.order_id << "},";
			}
		};

		const auto v1 = { 1, 2, 5, 5, 5, 9 };
		const auto v2 = { 2, 5, 7 };
		std::vector<int> diff;

		std::ranges::set_difference(v1, v2, std::back_inserter(diff));
		print(v1, "\\ ");
		print(v2, "= ");
		print(diff, "\n");

		// we want to know which orders "cut" between old and new states:
		const std::vector<Order> old_orders{ {1}, {2}, {5}, {9}, };
		const std::vector<Order> new_orders{ {2}, {5}, {7}, };
		std::vector<Order> cut_orders(old_orders.size() + new_orders.size());

		auto [old_orders_end, cut_orders_last] =
			std::ranges::set_difference(old_orders, new_orders,
				cut_orders.begin(), {},
				&Order::order_id, &Order::order_id);
		//assert(old_orders_end == old_orders.end());

		std::cout << "old orders = "; print(old_orders, "\n");
		std::cout << "new orders = "; print(new_orders, "\n");
		std::cout << "cut orders = "; print(cut_orders, "\n");
		cut_orders.erase(cut_orders_last, end(cut_orders));
		std::cout << "cut orders = "; print(cut_orders, "\n");
	}
	//*/

	// std::set_intersection
	// computes the intersection of two sets
	/*
	{
		std::vector<int> v1{ 1,2,3,4,5,6,7,8 };
		std::vector<int> v2{ 5,  7,  9,10 };
		std::sort(v1.begin(), v1.end());
		std::sort(v2.begin(), v2.end());

		std::vector<int> v_intersection;

		std::set_intersection(v1.begin(), v1.end(),
			v2.begin(), v2.end(),
			std::back_inserter(v_intersection));
		for (int n : v_intersection)
			std::cout << n << ' ';
	}
	//*/

	// std::ranges::set_intersection, std::ranges::set_intersection_result C++20
	// computes the intersection of two sets
	/*
	{
		auto print = [](const auto& v, const auto& rem) {
			std::cout << "{ ";
			for (const auto& e : v)
				std::cout << e << ' ';
			std::cout << "}" << rem;
		};

		const auto in1 = { 1, 2, 2, 3, 4, 5, 6 };
		const auto in2 = { 2, 2, 3, 3, 5, 7 };
		std::vector<int> out;

		std::ranges::set_intersection(in1, in2, std::back_inserter(out));

		print(in1, " n "), print(in2, " = "), print(out, "\n");
	}
	//*/

	// set_symmetric_difference
	// computes the symmetric difference between two sets	
	// a i b niz/skup - ovi; ono sto postoji u oba se izbaci, ostalo se uradi unija
	/*
	{
		std::vector<int> v1{ 1,2,3,4,5,6,7,8 };
		std::vector<int> v2{ 5,  7,  9,10 };
		std::sort(v1.begin(), v1.end());
		std::sort(v2.begin(), v2.end());

		std::vector<int> v_symDifference;

		std::set_symmetric_difference(
			v1.begin(), v1.end(),
			v2.begin(), v2.end(),
			std::back_inserter(v_symDifference));

		for (int n : v_symDifference)
			std::cout << n << ' ';
	}
	//*/

	// std::ranges::set_symmetric_difference, std::ranges::set_symmetric_difference_result C++20
	// computes the symmetric difference between two sets
	/*
	{
		auto visualize_this = [](const auto& v, int min = 1, int max = 9) {
			for (auto i{ min }; i <= max; ++i) {
				std::ranges::binary_search(v, i) ? std::cout << i : std::cout << '.';
				std::cout << ' ';
			}
			std::cout << '\n';
		};

		const auto in1 = { 1, 3, 4,    6, 7, 9 };
		const auto in2 = { 1,    4, 5, 6,    9 };

		std::vector<int> out;

		std::ranges::set_symmetric_difference(in1, in2, std::back_inserter(out));

		visualize_this(in1);
		visualize_this(in2);
		visualize_this(out);
	}
	//*/

	// set_union
	// computes the union of two sets
	/*
	{
		{
			std::vector<int> v1 = { 1, 2, 3, 4, 5 };
			std::vector<int> v2 = { 3, 4, 5, 6, 7 };
			std::vector<int> dest1;

			std::set_union(v1.begin(), v1.end(),
				v2.begin(), v2.end(),
				std::back_inserter(dest1));

			for (const auto& i : dest1) {
				std::cout << i << ' ';
			}
			std::cout << '\n';
		}
		{
			std::vector<int> v1 = { 1, 2, 3, 4, 5, 5, 5 };
			std::vector<int> v2 = { 3, 4, 5, 6, 7 };
			std::vector<int> dest1;

			std::set_union(v1.begin(), v1.end(),
				v2.begin(), v2.end(),
				std::back_inserter(dest1));

			for (const auto& i : dest1) {
				std::cout << i << ' ';
			}
			std::cout << '\n';
		}
	}
	//*/

	// std::ranges::set_union, std::ranges::set_union_result C++20
	// computes the union of two sets
	/*
	{
		auto print = [](const auto& in1, const auto& in2, auto first, auto last) {
			std::cout << "{ ";
			for (const auto& e : in1) { std::cout << e << ' '; }
			std::cout << "} U { ";
			for (const auto& e : in2) { std::cout << e << ' '; }
			std::cout << "} =\n{ ";
			while (!(first == last)) { std::cout << *first++ << ' '; }
			std::cout << "}\n\n";
		};

		std::vector<int> in1, in2, out;

		in1 = { 1, 2, 3, 4, 5 };
		in2 = { 3, 4, 5, 6, 7 };
		out.resize(in1.size() + in2.size());
		const auto ret = std::ranges::set_union(in1, in2, out.begin());
		print(in1, in2, out.begin(), ret.out);

		in1 = { 1, 2, 3, 4, 5, 5, 5 };
		in2 = { 3, 4, 5, 6, 7 };
		out.clear();
		out.reserve(in1.size() + in2.size());
		std::ranges::set_union(in1, in2, std::back_inserter(out));
		print(in1, in2, out.cbegin(), out.cend());

	}
	//*/

	/****************************************************************************/
	// Heap operations
	// Sorting operations
	/****************************************************************************/

	// std::is_heap
	// checks if the given range is a max heap
	/*
	{
		std::vector<int> v{ 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9 };

		std::cout << "initially, v:\n";
		for (auto i : v) std::cout << i << ' ';
		std::cout << '\n';

		if (!std::is_heap(v.begin(), v.end())) {
			std::cout << "making heap...\n";
			std::make_heap(v.begin(), v.end());
		}

		std::cout << "after make_heap, v:\n";
		for (auto t{ 1U }; auto i : v)
			std::cout << i << (std::has_single_bit(++t) ? " | " : " ");
		std::cout << '\n';
	}
	//*/

	// std::ranges::is_heap C++20
	// checks if the given range is a max heap
	// ovde ima i print za heap, moze biri korisna
	/*
	{
		void out(const auto& what, int n = 1) { while (n-- > 0) std::cout << what; };
		std::vector<int> v{ 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8 };

		auto draw_heap = [](auto const& v)
		{
			auto bails = [](int n, int w) {
				auto b = [](int w) { out("┌"), out("─", w), out("┴"), out("─", w), out("┐"); };
				n /= 2;
				if (!n) return;
				for (out(' ', w); n-- > 0; ) b(w), out(' ', w + w + 1);
				out('\n');
			};
			auto data = [](int n, int w, auto& first, auto last) {
				for (out(' ', w); n-- > 0 && first != last; ++first)
					out(*first), out(' ', w + w + 1);
				out('\n');
			};
			auto tier = [&](int t, int m, auto& first, auto last) {
				const int n{ 1 << t };
				const int w{ (1 << (m - t - 1)) - 1 };
				bails(n, w), data(n, w, first, last);
			};
			const int m{ static_cast<int>(std::ceil(std::log2(1 + v.size()))) };
			auto first{ v.cbegin() };
			for (int i{}; i != m; ++i) { tier(i, m, first, v.cend()); }
		};

		out("initially, v:\n");
		for (auto i : v) std::cout << i << ' ';
		out('\n');

		if (!std::ranges::is_heap(v)) {
			out("making heap...\n");
			std::ranges::make_heap(v);
		}

		out("after make_heap, v:\n");
		for (auto t{ 1U }; auto i : v) {
			std::cout << i << (std::has_single_bit(++t) ? " │ " : " ");
		}

		out("\n" "corresponding binary tree is:\n");
		draw_heap(v);


	}
	//*/

	// std::is_heap_until
	// finds the largest subrange that is a max heap
	/*
	{
		std::vector<int> v{ 3, 1, 4, 1, 5, 9 };
		std::make_heap(v.begin(), v.end());

		// probably mess up the heap
		v.push_back(2);
		v.push_back(6);

		auto heap_end = std::is_heap_until(v.begin(), v.end());

		std::cout << "all of v: ";
		for (auto i : v) std::cout << i << ' ';
		std::cout << '\n';

		std::cout << "only heap: ";
		for (auto i = v.begin(); i != heap_end; ++i) std::cout << *i << ' ';
		std::cout << '\n';
	}
	//*/

	// std::ranges::is_heap_until C++20
	// finds the largest subrange that is a max heap
	/*
	{
		void out(const auto& what, int n = 1) { while (n-- > 0) std::cout << what; }

		void draw_bin_tree(auto first, auto last);

		std::vector<int> v{ 3, 1, 4, 1, 5, 9, };
		std::ranges::make_heap(v);

		void draw_bin_tree(auto first, auto last)
		{
			auto bails = [](int n, int w) {
				auto b = [](int w) { out("┌"), out("─", w), out("┴"), out("─", w), out("┐"); };
				n /= 2;
				if (!n) return;
				for (out(' ', w); n-- > 0; ) b(w), out(' ', w + w + 1);
				out('\n');
			};
			auto data = [](int n, int w, auto& first, auto last) {
				for (out(' ', w); n-- > 0 && first != last; ++first)
					out(*first), out(' ', w + w + 1);
				out('\n');
			};
			auto tier = [&](int t, int m, auto& first, auto last) {
				const int n{ 1 << t };
				const int w{ (1 << (m - t - 1)) - 1 };
				bails(n, w), data(n, w, first, last);
			};
			const auto size{ std::ranges::distance(first, last) };
			const int m{ static_cast<int>(std::ceil(std::log2(1 + size))) };
			for (int i{}; i != m; ++i) { tier(i, m, first, last); }
			for (int i{}; i != m; ++i) { tier(i, m, first, last); }
		};
		// probably mess up the heap
		v.push_back(2);
		v.push_back(6);

		out("v after make_heap and push_back: \n");
		draw_bin_tree(v.begin(), v.end());

		out("the max-heap prefix of v: \n");
		const auto heap_end = std::ranges::is_heap_until(v);
		draw_bin_tree(v.begin(), heap_end);

	}
	//*/

	// std::make_heap
	// creates a max heap out of a range of elements
	/*
	{
		auto print = [](std::string_view text, std::vector<int> const& v = {}) {
			std::cout << text << ": ";
			for (const auto& e : v) std::cout << e << ' ';
			std::cout << '\n';
		};

		print("Max heap");

		std::vector<int> v{ 3, 2, 4, 1, 5, 9 };
		print("initially, v", v);

		std::make_heap(v.begin(), v.end());
		print("after make_heap, v", v);

		std::pop_heap(v.begin(), v.end());
		print("after pop_heap, v", v);

		auto top = v.back();
		v.pop_back();
		print("former top element", { top });
		print("after removing the former top element, v", v);

		print("\nMin heap");

		std::vector<int> v1{ 3, 2, 4, 1, 5, 9 };
		print("initially, v1", v1);

		std::make_heap(v1.begin(), v1.end(), std::greater<>{});
		print("after make_heap, v1", v1);

		std::pop_heap(v1.begin(), v1.end(), std::greater<>{});
		print("after pop_heap, v1", v1);

		auto top1 = v1.back();
		v1.pop_back();
		print("former top element", { top1 });
		print("after removing the former top element, v1", v1);
	}
	//*/

	// std::ranges::make_heap C++20
	// creates a max heap out of a range of elements
	/*
	{
		void draw_heap(auto const& v);
		void out(const auto& what, int n = 1) { while (n-- > 0) std::cout << what; }
		void print(auto rem, auto const& v) {
			out(rem);
			for (auto e : v) { out(e), out(' '); }
			out('\n');
		}

		int main()
		{
			std::vector h{ 1, 6, 1, 8, 0, 3, 3, 9, 8, 8, 7, 4, 9, 8, 9 };
			print("source: ", h);

			std::ranges::make_heap(h);
			print("\n" "max-heap: ", h);
			draw_heap(h);

			std::ranges::make_heap(h, std::greater{});
			print("\n" "min-heap: ", h);
			draw_heap(h);
		}

		void draw_heap(auto const& v)
		{
			auto bails = [](int n, int w) {
				auto b = [](int w) { out("┌"), out("─", w), out("┴"), out("─", w), out("┐"); };
				if (!(n /= 2)) return;
				for (out(' ', w); n-- > 0; ) b(w), out(' ', w + w + 1);
				out('\n');
			};
			auto data = [](int n, int w, auto& first, auto last) {
				for (out(' ', w); n-- > 0 && first != last; ++first)
					out(*first), out(' ', w + w + 1);
				out('\n');
			};
			auto tier = [&](int t, int m, auto& first, auto last) {
				const int n{ 1 << t };
				const int w{ (1 << (m - t - 1)) - 1 };
				bails(n, w), data(n, w, first, last);
			};
			const int m{ static_cast<int>(std::ceil(std::log2(1 + v.size()))) };
			auto first{ v.cbegin() };
			for (int i{}; i != m; ++i) { tier(i, m, first, v.cend()); }
		}
	}

	//*/

	// std::push_heap
	// adds an element to a max heap
	/*
	{
		std::vector<int> v{ 3, 1, 4, 1, 5, 9 };

		std::make_heap(v.begin(), v.end());

		std::cout << "v: ";
		for (auto i : v) std::cout << i << ' ';
		std::cout << '\n';

		v.push_back(6);

		std::cout << "before push_heap: ";
		for (auto i : v) std::cout << i << ' ';
		std::cout << '\n';

		std::push_heap(v.begin(), v.end());

		std::cout << "after push_heap:  ";
		for (auto i : v) std::cout << i << ' ';
		std::cout << '\n'
	}
	//*/

	// std::ranges::push_heap C++20
	// adds an element to a max heap
	/*
	{
		void out(const auto& what, int n = 1) {
			while (n-- > 0)
				std::cout << what;
		}

		void print(auto rem, auto const& v) {
			out(rem);
			for (auto e : v) { out(e), out(' '); }
			out('\n');
		}

		void draw_heap(auto const& v);

		int main()
		{
			std::vector<int> v{ 1, 6, 1, 8, 0, 3, };
			print("source vector v: ", v);

			std::ranges::make_heap(v);
			print("after make_heap: ", v);
			draw_heap(v);

			v.push_back(9);

			print("before push_heap: ", v);
			draw_heap(v);

			std::ranges::push_heap(v);
			print("after push_heap: ", v);
			draw_heap(v);
		}

		void draw_heap(auto const& v)
		{
			auto bails = [](int n, int w) {
				auto b = [](int w) { out("┌"), out("─", w), out("┴"), out("─", w), out("┐"); };
				if (!(n /= 2)) return;
				for (out(' ', w); n-- > 0; ) b(w), out(' ', w + w + 1);
				out('\n');
			};
			auto data = [](int n, int w, auto& first, auto last) {
				for (out(' ', w); n-- > 0 && first != last; ++first)
					out(*first), out(' ', w + w + 1);
				out('\n');
			};
			auto tier = [&](int t, int m, auto& first, auto last) {
				const int n{ 1 << t };
				const int w{ (1 << (m - t - 1)) - 1 };
				bails(n, w), data(n, w, first, last);
			};
			const int m{ static_cast<int>(std::ceil(std::log2(1 + v.size()))) };
			auto first{ v.cbegin() };
			for (int i{}; i != m; ++i) { tier(i, m, first, v.cend()); }
		}
	}
	//*/

	// std::pop_heap
	// removes the largest element from a max heap
	/*
	{
		std::vector<int> v{ 3, 1, 4, 1, 5, 9 };

		std::make_heap(v.begin(), v.end());

		std::cout << "v: ";
		for (auto i : v) std::cout << i << ' ';
		std::cout << '\n';

		std::pop_heap(v.begin(), v.end()); // moves the largest to the end

		std::cout << "after pop_heap: ";
		for (auto i : v) std::cout << i << ' ';
		std::cout << '\n';

		int largest = v.back();
		v.pop_back();  // actually removes the largest element
		std::cout << "largest element: " << largest << '\n';

		std::cout << "heap without largest: ";
		for (auto i : v) std::cout << i << ' ';
		std::cout << '\n';
	}
	//*/

	// std::ranges::pop_heap C++20
	// removes the largest element from a max heap
	/*
	{
		template <class I = int*>
		void print(std::string_view rem, I first = {}, I last = {},
			std::string_view term = "\n")
		{
			for (std::cout << rem; first != last; ++first) {
				std::cout << *first << ' ';
			}
			std::cout << term;
		}

		int main()
		{
			std::array v{ 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };
			print("initially, v: ", v.cbegin(), v.cend());

			std::ranges::make_heap(v);
			print("make_heap, v: ", v.cbegin(), v.cend());

			print("convert heap into sorted array:");
			for (auto n{ std::ssize(v) }; n >= 0; --n) {
				std::ranges::pop_heap(v.begin(), v.begin() + n);
				print("[ ", v.cbegin(), v.cbegin() + n, "]  ");
				print("[ ", v.cbegin() + n, v.cend(), "]\n");
			}
		}
	}
	//*/

	// std::sort_heap
	// turns a max heap into a range of elements sorted in ascending order
	/*
	{
		std::vector<int> v = { 3, 1, 4, 1, 5, 9 };

		std::make_heap(v.begin(), v.end());

		std::cout << "heap:\t";
		for (const auto& i : v) {
			std::cout << i << ' ';
		}

		std::sort_heap(v.begin(), v.end());

		std::cout << "\nsorted:\t";
		for (const auto& i : v) {
			std::cout << i << ' ';
		}
		std::cout << '\n';
	}
	//*/

	// std::ranges::sort_heap C++20
	// turns a max heap into a range of elements sorted in ascending order
	/*
	{
		void print(auto const& rem, auto const& v)
		{
			std::cout << rem;
			for (const auto i : v)
				std::cout << i << ' ';
			std::cout << '\n';
		}

		int main()
		{
			std::array v{ 3, 1, 4, 1, 5, 9 };
			print("original array:  ", v);

			std::ranges::make_heap(v);
			print("after make_heap: ", v);

			std::ranges::sort_heap(v);
			print("after sort_heap: ", v);
		}
	}
	//*/

	/****************************************************************************/
	// Minimum/maximum operations
	// Sorting operations
	/****************************************************************************/

	// std::max
	// std::ranges::max C++20
	// returns the greater of the given values
	/*
	{
		std::cout << "larger of 1 and 9999 is " << std::max(1, 9999) << '\n'
			<< "larger of 'a', and 'b' is '" << std::max('a', 'b') << "'\n"
			<< "largest of 1, 10, 50, and 200 is " << std::max({ 1, 10, 50, 200 }) << '\n'
			<< "longest of \"foo\", \"bar\", and \"hello\" is \""
			<< std::max({ "foo", "bar", "hello" },
				[](const std::string_view s1, const std::string_view s2) {
					return s1.size() < s2.size();
				}) << "\"\n";
	}
	//*/

	// std::max_element
	// std::ranges::max_element C++20
	// returns the largest element in a range
	/*
	{
		auto abs_compare = [](int a, int b)
		{
			return (std::abs(a) < std::abs(b));
		};

		std::vector<int> v{ 3, 1, -14, 1, 5, 9 };
		std::vector<int>::iterator result;

		result = std::max_element(v.begin(), v.end());
		std::cout << "max element at: " << std::distance(v.begin(), result) << '\n';

		result = std::max_element(v.begin(), v.end(), abs_compare);
		std::cout << "max element (absolute) at: " << std::distance(v.begin(), result) << '\n';
	}
	//*/

	// std::min
	// std::ranges::min C++20
	// returns the smaller of the given values
	/*
	{
		std::cout << "smaller of 1 and 9999 is " << std::min(1, 9999) << '\n'
			<< "smaller of 'a', and 'b' is '" << std::min('a', 'b') << "'\n"
			<< "shortest of \"foo\", \"bar\", and \"hello\" is \""
			<< std::min({ "foo", "bar", "hello" },
				[](const std::string_view s1, const std::string_view s2) {
					return s1.size() < s2.size();
				}) << "\"\n";
	}
	//*/

	// std::min_element
	// std::ranges::min_element C++20
	// returns the smallest element in a range
	/*
	{
		std::vector<int> v{ 3, 1, 4, 1, 5, 9 };
		auto result = ranges::min_element(v); // C++20
		std::vector<int>::iterator result = std::min_element(v.begin(), v.end());
		std::cout << "min element at: " << std::distance(v.begin(), result);
	}
	//*/

	// std::minmax C++11
	// returns the smaller and larger of two elements
	/*
	{
		std::vector<int> v{ 3, 1, 4, 1, 5, 9, 2, 6 };
		std::srand(std::time(0));
		std::pair<int, int> bounds = std::minmax(std::rand() % v.size(),
			std::rand() % v.size());

		std::cout << "v[" << bounds.first << "," << bounds.second << "]: ";
		for (int i = bounds.first; i < bounds.second; ++i) {
			std::cout << v[i] << ' ';
		}
		std::cout << '\n';
	}
	//*/

	// std::ranges::minmax, std::ranges::minmax_result C++20
	// returns the smaller and larger of two elements
	/*
	{
		namespace ranges = std::ranges;

		constexpr std::array v{ 3, 1, 4, 1, 5, 9, 2, 6, 5 };

		std::random_device rd;
		std::mt19937_64 generator(rd());
		std::uniform_int_distribution<> distribution(0, ranges::distance(v)); // [0..9]

		// auto bounds = ranges::minmax(distribution(generator), distribution(generator));
		// UB: dangling references: bounds.min and bounds.max have the type `const int&`.

		const int x1 = distribution(generator);
		const int x2 = distribution(generator);
		auto bounds = ranges::minmax(x1, x2); // OK: got references to lvalues x1 and x2

		std::cout << "v[" << bounds.min << ":" << bounds.max << "]: ";
		for (int i = bounds.min; i < bounds.max; ++i) {
			std::cout << v[i] << ' ';
		}
		std::cout << '\n';

		auto [min, max] = ranges::minmax(v);
		std::cout << "smallest: " << min << ", " << "largest: " << max << '\n';
	}
	//*/

	// std::minmax_element C++11
	// returns the smallest and the largest elements in a range
	/*
	{
		const auto v = { 3, 9, 1, 4, 2, 5, 9 };
		const auto [min, max] = std::minmax_element(begin(v), end(v));

		std::cout << "min = " << *min << ", max = " << *max << '\n';
	}
	//*/

	// std::ranges::minmax_element, std::ranges::minmax_element_result C++20
	// returns the smallest and the largest elements in a range
	/*
	{
		namespace rng = std::ranges;

		const auto v = { 3, 9, 1, 4, 1, 2, 5, 9 };
		const auto [min, max] = rng::minmax_element(v);
		std::cout
			<< "min = " << *min << ", at [" << rng::distance(v.begin(), min) << "]\n"
			<< "max = " << *max << ", at [" << rng::distance(v.begin(), max) << "]\n";
	}
	//*/

	// std::ranges::clamp C++17
	// clamps a value between a pair of boundary values
	// ovo nesto nece da se prevede 
	/*
	{
		using namespace std::literals;

		std::cout << " raw   clamped to int8_t   clamped to uint8_t\n";
		for (int const v : {-129, -128, -1, 0, 42, 127, 128, 255, 256}) {
			std::cout << std::setw(04) << v
				<< std::setw(20) << std::ranges::clamp(v, INT8_MIN, INT8_MAX)
				<< std::setw(21) << std::ranges::clamp(v, 0, UINT8_MAX) << '\n';
		}
		std::cout << '\n';

		// Projection function
		const auto stoi = [](std::string s) { return std::stoi(s); };

		// Same as above, but with strings
		for (std::string const v : {"-129", "-128", "-1", "0", "42", "127", "128", "255", "256"}) {
			std::cout << std::setw(04) << v
				<< std::setw(20) << std::ranges::clamp(v, "-128"s, "127"s, {}, stoi)
				<< std::setw(21) << std::ranges::clamp(v, "0"s, "255"s, {}, stoi) << '\n';
		}
	}
	//*/

	// std::ranges::clamp C++20
	// clamps a value between a pair of boundary values
	// ovo nesto nece da se prevede 
	/*
	{
		using namespace std::literals;

		std::cout << " raw   clamped to int8_t   clamped to uint8_t\n";
		for (int const v : {-129, -128, -1, 0, 42, 127, 128, 255, 256}) {
			std::cout << std::setw(04) << v
				<< std::setw(20) << std::ranges::clamp(v, INT8_MIN, INT8_MAX)
				<< std::setw(21) << std::ranges::clamp(v, 0, UINT8_MAX) << '\n';
		}
		std::cout << '\n';

		// Projection function
		const auto stoi = [](std::string s) { return std::stoi(s); };

		// Same as above, but with strings
		for (std::string const v : {"-129", "-128", "-1", "0", "42", "127", "128", "255", "256"}) {
			std::cout << std::setw(04) << v
				<< std::setw(20) << std::ranges::clamp(v, "-128"s, "127"s, {}, stoi)
				<< std::setw(21) << std::ranges::clamp(v, "0"s, "255"s, {}, stoi) << '\n';
		}
	}
	//*/

	/****************************************************************************/
	// Comparison operations
	// Sorting operations
	/****************************************************************************/

	// std::equal
	// determines if two sets of elements are the same
	/*
	{
		auto is_palindrome = [](const std::string_view& s)
		{
			return std::equal(s.begin(), s.begin() + s.size() / 2, s.rbegin());
		};

		cout << is_palindrome("radar") << "\n";
		cout << is_palindrome("hello") << "\n";
	}
	//*/

	// std::ranges::equal C++20
	// determines if two sets of elements are the same
	/*
	{
		auto is_palindrome = [](const std::string_view& s)
		{
			namespace views = std::views;
			auto forward = s | views::take(s.size() / 2);
			auto backward = s | views::reverse | views::take(s.size() / 2);
			return std::ranges::equal(forward, backward);
		};

		cout << is_palindrome("radar") << "\n";
		cout << is_palindrome("hello") << "\n";
	}
	//*/

	// std::lexicographical_compare
	// returns true if one range is lexicographically less than another
	/*
	{
		std::vector<char> v1{ 'a', 'b', 'c', 'd' };
		std::vector<char> v2{ 'a', 'b', 'c', 'd' };

		std::mt19937 g{ std::random_device{}() };
		while (!std::lexicographical_compare(v1.begin(), v1.end(),
			v2.begin(), v2.end())) {
			for (auto c : v1) std::cout << c << ' ';
			std::cout << ">= ";
			for (auto c : v2) std::cout << c << ' ';
			std::cout << '\n';

			std::shuffle(v1.begin(), v1.end(), g);
			std::shuffle(v2.begin(), v2.end(), g);
		}

		for (auto c : v1) std::cout << c << ' ';
		std::cout << "< ";
		for (auto c : v2) std::cout << c << ' ';
		std::cout << '\n';
	}
	//*/

	// std::ranges::lexicographical_compare C++20
	// returns true if one range is lexicographically less than another
	/*
	{
		std::vector<char> v1{ 'a', 'b', 'c', 'd' };
		std::vector<char> v2{ 'a', 'b', 'c', 'd' };

		namespace ranges = std::ranges;
		auto os = std::ostream_iterator<char>(std::cout, " ");

		std::mt19937 g{ std::random_device{}() };
		while (!ranges::lexicographical_compare(v1, v2)) {
			ranges::copy(v1, os);
			std::cout << ">= ";
			ranges::copy(v2, os);
			std::cout << '\n';

			ranges::shuffle(v1, g);
			ranges::shuffle(v2, g);
		}

		ranges::copy(v1, os);
		std::cout << "<  ";
		ranges::copy(v2, os);
		std::cout << '\n';
	}
	//*/

	// std::lexicographical_compare_three_way
	// compares two ranges using three-way comparison C++20
	// primer nece da se prevede, nisam siguran sta radi
	/*
	{
		auto show_result = [](std::string_view s1, std::string_view s2, std::strong_ordering o)
		{
			std::cout << quoted(s1) << " is ";
			(o < 0) ? std::cout << "less than " :
				(o > 0) ? std::cout << "greater than " :
				std::cout << "equal to ";
			std::cout << quoted(s2) << '\n';
		};

		auto cmp_icase = [](char x, char y) {
			const auto ux{ std::toupper(x) };
			const auto uy{ std::toupper(y) };
			return (ux < uy) ? std::strong_ordering::less :
				(ux > uy) ? std::strong_ordering::greater :
				std::strong_ordering::equal;
		};

		for (const auto& [s1, s2] : { std::pair{"one"sv, "ONE"sv},
											   {"two"sv, "four"sv},
											   {"three"sv, "two"sv} }) {
			const auto res = std::lexicographical_compare_three_way(
				s1.cbegin(), s1.cend(), s2.cbegin(), s2.cend(), cmp_icase);
			show_result(s1, s2, res);
		}
	}
	//*/

	/****************************************************************************/
	// Comparison operations
	/****************************************************************************/

	// std::is_permutation C++11
	// determines if two ranges are permutations of each other
	/*
	{
		auto v1 = { 1,2,3,4,5 };
		auto v2 = { 3,5,4,1,2 };
		auto v3 = { 3,5,4,1,1 };

		for (auto& i : v1)
			cout << i << " ";
		std::cout << " is a permutation of ";
		for (auto& i : v2)
			cout << i << " ";
		std::cout << ": " << std::boolalpha
			<< std::is_permutation(v1.begin(), v1.end(), v2.begin()) << '\n';


		for (auto& i : v3)
			cout << i << " ";
		std::cout << " is a permutation of ";
		for (auto& i : v1)
			cout << i << " ";
		std::cout << ": " << std::boolalpha
			<< std::is_permutation(v1.begin(), v1.end(), v3.begin()) << '\n';

	}
	//*/

	// std::ranges::is_permutation C++20
	// determines if two ranges are permutations of each other
	/*
	{
		auto& operator<< (auto& os, std::ranges::forward_range auto const& v) {
			os << "{ ";
			for (auto const& e : v) os << e << ' ';
			return os << "}";
		};

		static constexpr auto r1 = { 1,2,3,4,5 };
		static constexpr auto r2 = { 3,5,4,1,2 };
		static constexpr auto r3 = { 3,5,4,1,1 };

		static_assert(
			std::ranges::is_permutation(r1, r1) &&
			std::ranges::is_permutation(r1, r2) &&
			std::ranges::is_permutation(r2, r1) &&
			std::ranges::is_permutation(r1.begin(), r1.end(), r2.begin(), r2.end())
			);

		std::cout
			<< std::boolalpha
			<< "is_permutation( " << r1 << ", " << r2 << " ): "
			<< std::ranges::is_permutation(r1, r2) << '\n'
			<< "is_permutation( " << r1 << ", " << r3 << " ): "
			<< std::ranges::is_permutation(r1, r3) << '\n'

			<< "is_permutation with custom predicate and projections: "
			<< std::ranges::is_permutation(
				std::array{ -14, -11, -13, -15, -12 },  // 1st range
				std::array{ 'F', 'E', 'C', 'B', 'D' },  // 2nd range
				[](int x, int y) { return abs(x) == abs(y); }, // predicate
				[](int x) { return x + 10; },           // projection for 1st range
				[](char y) { return int(y - 'A'); })    // projection for 2nd range
			<< '\n';
	}
	//*/

	// std::next_permutation
	// generates the next greater lexicographic permutation of a range of elements
	/*
	{
		std::string s = "aba";
		std::sort(s.begin(), s.end());
		do {
			std::cout << s << '\n';
		} while (std::next_permutation(s.begin(), s.end()));
	}
	//*/

	// std::ranges::next_permutation, std::ranges::next_permutation_result C++20
	// generates the next greater lexicographic permutation of a range of elements
	/*
	{
		struct S {
			char c;
			int i;
			auto operator<=>(const S&) const = default;
			friend std::ostream& operator<< (std::ostream& os, const S& s) {
				return os << "{'" << s.c << "', " << s.i << "}";
			}
		};

		auto print = [](auto const& v, char term = ' ') {
			std::cout << "{ ";
			for (const auto& e : v) { std::cout << e << ' '; }
			std::cout << '}' << term;
		};

		std::cout << "Generate all permutations (iterators case):\n";
		std::string s{ "abc" };
		do { print(s); } while (std::ranges::next_permutation(s.begin(), s.end()).found);

		std::cout << "\n" "Generate all permutations (range case):\n";
		std::array a{ 'a', 'b', 'c' };
		do { print(a); } while (std::ranges::next_permutation(a).found);

		std::cout << "\n" "Generate all permutations using comparator:\n";
		using namespace std::literals;
		std::array z{ "█"s, "▄"s, "▁"s };
		do { print(z); } while (std::ranges::next_permutation(z, std::greater()).found);

		std::cout << "\n" "Generate all permutations using projection:\n";
		std::array<S, 3> r{ S{'A',3}, S{'B',2}, S{'C',1} };
		do { print(r, '\n'); } while (std::ranges::next_permutation(r, {}, &S::c).found);

	}
	//*/

	// std::prev_permutation
	// generates the next smaller lexicographic permutation of a range of elements
	/*
	{
		std::string s = "abc";
		std::sort(s.begin(), s.end(), std::greater<char>());
		do {
			std::cout << s << ' ';
		} while (std::prev_permutation(s.begin(), s.end()));
		std::cout << '\n';
	}
	//*/

	// std::ranges::prev_permutation, std::ranges::prev_permutation_result C++20
	// generates the next smaller lexicographic permutation of a range of elements
	/*
	{
		struct S {
			char c;
			int i;
			auto operator<=>(const S&) const = default;
			friend std::ostream& operator<< (std::ostream& os, const S& s) {
				return os << "{'" << s.c << "', " << s.i << "}";
			}
		};

		auto print = [](auto const& v, char term = ' ') {
			std::cout << "{ ";
			for (const auto& e : v) { std::cout << e << ' '; }
			std::cout << '}' << term;
		};

		std::cout << "Generate all permutations (iterators case):\n";
		std::string s{ "cba" };
		do { print(s); } while (std::ranges::prev_permutation(s.begin(), s.end()).found);

		std::cout << "\n" "Generate all permutations (range case):\n";
		std::array a{ 'c', 'b', 'a' };
		do { print(a); } while (std::ranges::prev_permutation(a).found);

		std::cout << "\n" "Generate all permutations using comparator:\n";
		using namespace std::literals;
		std::array z{ "▁"s, "▄"s, "█"s };
		do { print(z); } while (std::ranges::prev_permutation(z, std::greater()).found);

		std::cout << "\n" "Generate all permutations using projection:\n";
		std::array<S, 3> r{ S{'C',1}, S{'B',2}, S{'A',3} };
		do { print(r, '\n'); } while (std::ranges::prev_permutation(r, {}, &S::c).found);
	}
	//*/

	/****************************************************************************/
	// Numeric operations
	// header <numeric>
	/****************************************************************************/

	// std::iota C++11
	// fills a range with successive increments of the starting value
	// sta radi ovaj primer dole Bog sveti zna
	/*
	{
		class BigData // inefficient to copy
		{
			int data[1024]; // some raw data
		public:
			explicit BigData(int i = 0) { data[0] = i;}
			operator int() const { return data[0]; }
			BigData& operator=(int i) { data[0] = i; return *this; }
		};

		std::list<BigData> l(10);
		std::iota(l.begin(), l.end(), -4);

		std::vector<std::list<BigData>::iterator> v(l.size());
		std::iota(v.begin(), v.end(), l.begin());
		// Vector of iterators (to original data) is used to avoid expensive copying,
		// and because std::shuffle (below) cannot be applied to a std::list directly.

		std::shuffle(v.begin(), v.end(), std::mt19937{ std::random_device{}() });

		std::cout << "Original contents of the list l:\t";
		for (auto const& n : l) std::cout << std::setw(2) << n << ' ';
		std::cout << '\n';

		std::cout << "Contents of l, viewed via shuffled v:\t";
		for (auto const i : v) std::cout << std::setw(2) << *i << ' ';
		std::cout << '\n';
	}
	//*/

	// std::ranges::iota, std::ranges::iota_result C++23
	// fills a range with successive increments of the starting value
	/*
	{
		std::list<int> l(10);
		std::ranges::iota(l.begin(), l.end(), -4);

		std::vector<std::list<int>::iterator> v(l.size());
		std::ranges::iota(v, l.begin());

		std::ranges::shuffle(v, std::mt19937{ std::random_device{}() });

		std::cout << "Contents of the list: ";
		for (auto n : l) std::cout << n << ' ';
		std::cout << '\n';

		std::cout << "Contents of the list, shuffled: ";
		for (auto i : v) std::cout << *i << ' ';
		std::cout << '\n';
	}
	//*/

	// std::accumulate
	// sums up a range of elements
	/*
	{
		std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		int sum = std::accumulate(v.begin(), v.end(), 0);
		int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());
		auto dash_fold = [](std::string a, int b) {
			return std::move(a) + '-' + std::to_string(b);
		};

		std::string s = std::accumulate(std::next(v.begin()), v.end(),
			std::to_string(v[0]), // start with first element
			dash_fold);

		// Right fold using reverse iterators
		std::string rs = std::accumulate(std::next(v.rbegin()), v.rend(),
			std::to_string(v.back()), // start with last element
			dash_fold);

		std::cout << "sum: " << sum << '\n'
			<< "product: " << product << '\n'
			<< "dash-separated string: " << s << '\n'
			<< "dash-separated string (right-folded): " << rs << '\n';
	}
	//*/

	// std::inner_product
	// computes the inner product of two ranges of elements
	/*
	{
		std::vector<int> a{ 0, 1, 2, 3, 4 };
		std::vector<int> b{ 5, 4, 2, 3, 1 };

		int r1 = std::inner_product(a.begin(), a.end(), b.begin(), 0);
		std::cout << "Inner product of a and b: " << r1 << '\n';

		int r2 = std::inner_product(a.begin(), a.end(), b.begin(), 0,
			std::plus<>(), std::equal_to<>());
		std::cout << "Number of pairwise matches between a and b: " << r2 << '\n';
	}
	//*/

	// std::adjacent_difference
	// computes the differences between adjacent elements in a range
	/*
	{
		auto print = [](auto comment, auto const& sequence) {
			std::cout << comment;
			for (const auto& n : sequence)
				std::cout << n << ' ';
			std::cout << '\n';
		};

		// Default implementation - the difference b/w two adjacent items

		std::vector v{ 4, 6, 9, 13, 18, 19, 19, 15, 10 };
		print("Initially, v = ", v);
		std::adjacent_difference(v.begin(), v.end(), v.begin());
		print("Modified v = ", v);

		// Fibonacci

		std::array<int, 10> a{ 1 };
		adjacent_difference(begin(a), std::prev(end(a)), std::next(begin(a)), std::plus<> {});
		print("Fibonacci, a = ", a);
	}
	//*/

	// std::partial_sum
	// computes the partial sum of a range of elements
	/*
	{
		std::vector<int> v = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }; // or std::vector<int>v(10, 2);

		std::cout << "The first 10 even numbers are: ";
		std::partial_sum(v.begin(), v.end(),
			std::ostream_iterator<int>(std::cout, " "));
		std::cout << '\n';

		std::partial_sum(v.begin(), v.end(), v.begin(), std::multiplies<int>());
		std::cout << "The first 10 powers of 2 are: ";
		for (auto n : v)
			std::cout << n << " ";
		std::cout << '\n';
	}
	//*/

	// std::reduce C++17
	// computes the partial sum of a range of elements
	/*
	{
		auto eval = [](auto fun) {
			const auto t1 = std::chrono::high_resolution_clock::now();
			const auto [name, result] = fun();
			const auto t2 = std::chrono::high_resolution_clock::now();
			const std::chrono::duration<double, std::milli> ms = t2 - t1;
			std::cout << std::fixed << std::setprecision(1) << name << " result "
				<< result << " took " << ms.count() << " ms\n";
		};
		{
			const std::vector<double> v(100'000'007, 0.1);

			eval([&v] { return std::pair{ "std::accumulate (double)",
				std::accumulate(v.cbegin(), v.cend(), 0.0) }; });
			eval([&v] { return std::pair{ "std::reduce (seq, double)",
				std::reduce(std::execution::seq, v.cbegin(), v.cend()) }; });
			eval([&v] { return std::pair{ "std::reduce (par, double)",
				std::reduce(std::execution::par, v.cbegin(), v.cend()) }; });
		} {
			const std::vector<long> v(100'000'007, 1);

			eval([&v] { return std::pair{ "std::accumulate (long)",
				std::accumulate(v.cbegin(), v.cend(), 0) }; });
			eval([&v] { return std::pair{ "std::reduce (seq, long)",
				std::reduce(std::execution::seq, v.cbegin(), v.cend()) }; });
			eval([&v] { return std::pair{ "std::reduce (par, long)",
				std::reduce(std::execution::par, v.cbegin(), v.cend()) }; });
		}
	}
	//*/

	// std::exclusive_scan C++17
	// similar to std::accumulate, except out of order
	/*
	{
		std::vector data{ 3, 1, 4, 1, 5, 9, 2, 6 };

		std::cout << "exclusive sum: ";
		std::exclusive_scan(data.begin(), data.end(),
			std::ostream_iterator<int>(std::cout, " "),
			0);
		std::cout << "\ninclusive sum: ";
		std::inclusive_scan(data.begin(), data.end(),
			std::ostream_iterator<int>(std::cout, " "));

		std::cout << "\n\nexclusive product: ";
		std::exclusive_scan(data.begin(), data.end(),
			std::ostream_iterator<int>(std::cout, " "),
			1, std::multiplies<>{});
		std::cout << "\ninclusive product: ";
		std::inclusive_scan(data.begin(), data.end(),
			std::ostream_iterator<int>(std::cout, " "),
			std::multiplies<>{});
	}
	//*/

	// std::inclusive_scan C++17
	// similar to std::partial_sum, excludes the ith input element from the ith sum
	/*
	{
		std::vector data{ 3, 1, 4, 1, 5, 9, 2, 6 };

		std::cout << "exclusive sum: ";
		std::exclusive_scan(data.begin(), data.end(),
			std::ostream_iterator<int>(std::cout, " "),
			0);
		std::cout << "\ninclusive sum: ";
		std::inclusive_scan(data.begin(), data.end(),
			std::ostream_iterator<int>(std::cout, " "));

		std::cout << "\n\nexclusive product: ";
		std::exclusive_scan(data.begin(), data.end(),
			std::ostream_iterator<int>(std::cout, " "),
			1, std::multiplies<>{});
		std::cout << "\ninclusive product: ";
		std::inclusive_scan(data.begin(), data.end(),
			std::ostream_iterator<int>(std::cout, " "),
			std::multiplies<>{});
	}
	//*/

	// std::transform_reduce C++17
	// applies an invocable, then reduces out of order
	/*
	{
		std::vector<double> xvalues(10007, 1.0), yvalues(10007, 1.0);

		double result = std::transform_reduce(
			//  std::execution::par,
			xvalues.begin(), xvalues.end(),
			yvalues.begin(), 0.0
		);
		std::cout << result << '\n';
	}
	//*/

	// std::transform_exclusive_scan C++17
	// applies an invocable, then calculates exclusive scan
	/*
	{
		std::vector data{ 3, 1, 4, 1, 5, 9, 2, 6 };

		auto times_10 = [](int x) { return x * 10; };

		std::cout << "10 times exclusive sum: ";
		std::transform_exclusive_scan(data.begin(), data.end(),
			std::ostream_iterator<int>(std::cout, " "),
			0, std::plus<int>{}, times_10);
		std::cout << "\n10 times inclusive sum: ";
		std::transform_inclusive_scan(data.begin(), data.end(),
			std::ostream_iterator<int>(std::cout, " "),
			std::plus<int>{}, times_10);
	}
	//*/

	// std::transform_inclusive_scan
	// applies an invocable, then calculates inclusive scan
	/*
	{
		std::vector data{ 3, 1, 4, 1, 5, 9, 2, 6 };
		auto times_10 = [](int x) { return x * 10; };

		std::cout << "10 times exclusive sum: ";
		std::transform_exclusive_scan(data.begin(), data.end(),
			std::ostream_iterator<int>(std::cout, " "),
			0, std::plus<int>{}, times_10);
		std::cout << "\n10 times inclusive sum: ";
		std::transform_inclusive_scan(data.begin(), data.end(),
			std::ostream_iterator<int>(std::cout, " "),
			std::plus<int>{}, times_10);
	}
	//*/

	/****************************************************************************/
	// Operations on uninitialized memory
	// header <memory>
	/****************************************************************************/

	// std::uninitialized_copy
	// copies a range of objects to an uninitialized area of memory
	// ovo nece da se prevede, ne znam sta radi
	/*
	{
		const char* v[] = { "This", "is", "an", "example" };

		auto sz = std::size(v);

		if (void* pbuf = std::aligned_alloc(alignof(std::string), sizeof(std::string) * sz))
		{
			try
			{
				auto first = static_cast<std::string*>(pbuf);
				auto last = std::uninitialized_copy(std::begin(v), std::end(v), first);

				for (auto it = first; it != last; ++it)
					std::cout << *it << '_';
				std::cout << '\n';

				std::destroy(first, last);
			}
			catch (...) {}
			std::free(pbuf);
		}
	}
	//*/

	// std::ranges::uninitialized_copy, std::ranges::uninitialized_copy_result C++20
	// copies a range of objects to an uninitialized area of memory
	// i ovo nece isto
	/*
	{
		const char* v[] = { "This", "is", "an", "example" };

		auto sz = std::size(v);

		if (void* pbuf = std::aligned_alloc(alignof(std::string), sizeof(std::string) * sz))
		{
			try
			{
				auto first = static_cast<std::string*>(pbuf);
				auto last = std::ranges::uninitialized_copy(std::begin(v), std::end(v), first);

				for (auto it = first; it != last; ++it)
					std::cout << *it << '_';
				std::cout << '\n';

				std::destroy(first, last);
			}
			catch (...) {}
			std::free(pbuf);
		}
	}
	//*/

	// std::uninitialized_copy_n C++11
	// copies a number of objects to an uninitialized area of memory
	// nece da se prevede
	/*
	{
		std::vector<std::string> v = { "This", "is", "an", "example" };

		std::string* p;
		std::size_t sz;
		std::tie(p, sz) = std::get_temporary_buffer<std::string>(v.size());
		sz = std::min(sz, v.size());

		std::uninitialized_copy_n(v.begin(), sz, p);

		for (std::string* i = p; i != p + sz; ++i) {
			std::cout << *i << ' ';
			i->~basic_string<char>();
		}
		std::return_temporary_buffer(p);
	}
	//*/

	// std::ranges::uninitialized_copy_n, std::ranges::uninitialized_copy_n_result C++20
	// copies a number of objects to an uninitialized area of memory
	/*
	{
		const char* stars[]{ "Procyon", "Spica", "Pollux", "Deneb", "Polaris", };

		constexpr int n{ 4 };
		alignas(alignof(std::string)) char out[n * sizeof(std::string)];

		try
		{
			auto first{ reinterpret_cast<std::string*>(out) };
			auto last{ first + n };
			auto ret{ std::ranges::uninitialized_copy_n(std::begin(stars), n, first, last) };

			std::cout << "{ ";
			for (auto it{ first }; it != ret.out; ++it)
				std::cout << std::quoted(*it) << ", ";
			std::cout << "};\n";

			std::ranges::destroy(first, last);
		}
		catch (...)
		{
			std::cout << "uninitialized_copy_n exception\n";
		}
	}
	//*/

	// std::uninitialized_fill
	// copies an object to an uninitialized area of memory, defined by a range
	// nece da radi
	/*
	{
		std::string* p;
		std::size_t sz;
		std::tie(p, sz) = std::get_temporary_buffer<std::string>(4);

		std::uninitialized_fill(p, p + sz, "Example");

		for (std::string* i = p; i != p + sz; ++i) {
			std::cout << *i << '\n';
			i->~basic_string<char>();
		}
		std::return_temporary_buffer(p);
	}
	//*/

	// std::ranges::uninitialized_fill C++20
	// copies an object to an uninitialized area of memory, defined by a range
	/*
	{
		constexpr int n{ 4 };
		alignas(alignof(std::string)) char out[n * sizeof(std::string)];

		try
		{
			auto first{ reinterpret_cast<std::string*>(out) };
			auto last{ first + n };
			//std::ranges::uninitialized_fill(first, last, "▄▀▄▀▄▀▄▀");
			std::ranges::uninitialized_fill(first, last, "^_^_^_^_");

			int count{ 1 };
			for (auto it{ first }; it != last; ++it) {
				std::cout << count++ << ' ' << *it << '\n';
			}

			std::ranges::destroy(first, last);
		}
		catch (...)
		{
			std::cout << "Exception!\n";
		}
	}
	//*/

	// std::uninitialized_fill_n
	// copies an object to an uninitialized area of memory, defined by a start and a count
	// nece da radi
	/*
	{
		std::string* p;
		std::size_t sz;
		std::tie(p, sz) = std::get_temporary_buffer<std::string>(4);
		std::uninitialized_fill_n(p, sz, "Example");

		for (std::string* i = p; i != p + sz; ++i) {
			std::cout << *i << '\n';
			i->~basic_string<char>();
		}
		std::return_temporary_buffer(p);
	}
	//*/

	// std::ranges::uninitialized_fill_n C++20
	// copies an object to an uninitialized area of memory, defined by a start and a count
	/*
	{
		constexpr int n{ 3 };
		alignas(alignof(std::string)) char out[n * sizeof(std::string)];

		try
		{
			auto first{ reinterpret_cast<std::string*>(out) };
			auto last = std::ranges::uninitialized_fill_n(first, n, "cppreference");

			for (auto it{ first }; it != last; ++it) {
				std::cout << *it << '\n';
			}

			std::ranges::destroy(first, last);
		}
		catch (...)
		{
			std::cout << "Exception!\n";
		}
	}
	//*/

	// std::uninitialized_move C++17
	// moves a range of objects to an uninitialized area of memory
	// nece da radi
	/*
	{
		auto print = [](auto rem, auto first, auto last) {
			for (std::cout << rem; first != last; ++first)
				std::cout << std::quoted(*first) << ' ';
			std::cout << '\n';
		};

		std::string in[]{ "Home", "Work!" };
		print("initially, in: ", std::begin(in), std::end(in));

		if (
			constexpr auto sz = std::size(in);
			void* out = std::aligned_alloc(alignof(std::string), sizeof(std::string) * sz)
			) {
			try {
				auto first{ static_cast<std::string*>(out) };
				auto last{ first + sz };
				std::uninitialized_move(std::begin(in), std::end(in), first);

				print("after move, in: ", std::begin(in), std::end(in));
				print("after move, out: ", first, last);

				std::destroy(first, last);
			}
			catch (...) {
				std::cout << "Exception!\n";
			}
			std::free(out);
		}
	}
	//*/

	// std::ranges::uninitialized_move, std::ranges::uninitialized_move_result C++20
	// moves a range of objects to an uninitialized area of memory
	/*
	{
		auto print = [](auto rem, auto first, auto last) {
			for (std::cout << rem; first != last; ++first)
				std::cout << std::quoted(*first) << ' ';
			std::cout << '\n';
		};

		std::string in[]{ "Home", "World" };
		print("initially, in: ", std::begin(in), std::end(in));

		if (
			constexpr auto sz = std::size(in);
			void* out = std::aligned_alloc(alignof(std::string), sizeof(std::string) * sz)
			) {
			try {
				auto first{ static_cast<std::string*>(out) };
				auto last{ first + sz };
				std::ranges::uninitialized_move(std::begin(in), std::end(in), first, last);

				print("after move, in: ", std::begin(in), std::end(in));
				print("after move, out: ", first, last);

				std::ranges::destroy(first, last);
			}
			catch (...) {
				std::cout << "Exception!\n";
			}
			std::free(out);
		}
	}
	//*/

	// std::uninitialized_move_n C++17
	// moves a number of objects to an uninitialized area of memory
	/*
	{
		auto print = [](auto rem, auto first, auto last) {
			for (std::cout << rem; first != last; ++first)
				std::cout << std::quoted(*first) << ' ';
			std::cout << '\n';
		};

		std::string in[]{ "One", "Definition", "Rule" };
		print("initially, in: ", std::begin(in), std::end(in));

		if (
			constexpr auto sz = std::size(in);
			void* out = std::aligned_alloc(alignof(std::string), sizeof(std::string) * sz)
			) {
			try {
				auto first{ static_cast<std::string*>(out) };
				auto last{ first + sz };
				std::uninitialized_move_n(std::begin(in), sz, first);

				print("after move, in: ", std::begin(in), std::end(in));
				print("after move, out: ", first, last);

				std::destroy(first, last);
			}
			catch (...) {
				std::cout << "Exception!\n";
			}
			std::free(out);
		}
	}
	//*/

	// std::ranges::uninitialized_move_n, std::ranges::uninitialized_move_n_result C++20
	// moves a number of objects to an uninitialized area of memory
	// ne radi
	/*
	{
		auto print = [](auto rem, auto first, auto last) {
			for (std::cout << rem; first != last; ++first)
				std::cout << std::quoted(*first) << ' ';
			std::cout << '\n';
		};

		std::string in[]{ "No", "Diagnostic", "Required", };
		print("initially, in: ", std::begin(in), std::end(in));

		if (
			constexpr auto sz = std::size(in);
			void* out = std::aligned_alloc(alignof(std::string), sizeof(std::string) * sz)
			) {
			try {
				auto first{ static_cast<std::string*>(out) };
				auto last{ first + sz };
				std::ranges::uninitialized_move_n(std::begin(in), sz, first, last);

				print("after move, in: ", std::begin(in), std::end(in));
				print("after move, out: ", first, last);

				std::ranges::destroy(first, last);
			}
			catch (...) {
				std::cout << "Exception!\n";
			}
			std::free(out);
		}
	}
	//*/

	// std::uninitialized_default_construct C++17
	// constructs objects by default-initialization in an uninitialized area of memory, defined by a range
	/*
	{
		struct S{ std::string m{ "Default value" }; };

		constexpr int n{ 3 };
		alignas(alignof(S)) unsigned char mem[n * sizeof(S)];

		try
		{
			auto first{ reinterpret_cast<S*>(mem) };
			auto last{ first + n };

			std::uninitialized_default_construct(first, last);

			for (auto it{ first }; it != last; ++it) {
				std::cout << it->m << '\n';
			}

			std::destroy(first, last);
		}
		catch (...)
		{
			std::cout << "Exception!\n";
		}

		// Notice that for "trivial types" the uninitialized_default_construct
		// generally does not zero-fill the given uninitialized memory area.
		int v[]{ 1, 2, 3, 4 };
		const int original[]{ 1, 2, 3, 4 };
		std::uninitialized_default_construct(std::begin(v), std::end(v));
		// for (const int i : v) { std::cout << i << ' '; }
		// Maybe undefined behavior, pending CWG 1997.
		std::cout <<
			(std::memcmp(v, original, sizeof(v)) == 0 ? "Unmodified\n" : "Modified\n");
		// The result is unspecified.
	}
	//*/

	// std::ranges::uninitialized_default_construct C++20
	// constructs objects by default-initialization in an uninitialized area of memory, defined by a range
	/*
	{
		//struct S { std::string m{ "▄▀▄▀▄▀▄▀" }; };
		struct S { std::string m{ "^_^_^_^_" }; };

		constexpr int n{ 4 };
		alignas(alignof(S)) char out[n * sizeof(S)];

		try
		{
			auto first{ reinterpret_cast<S*>(out) };
			auto last{ first + n };

			std::ranges::uninitialized_default_construct(first, last);

			auto count{ 1 };
			for (auto it{ first }; it != last; ++it) {
				std::cout << count++ << ' ' << it->m << '\n';
			}

			std::ranges::destroy(first, last);
		}
		catch (...) { std::cout << "Exception!\n"; }

		// Notice that for "trivial types" the uninitialized_default_construct
		// generally does not zero-fill the given uninitialized memory area.
		constexpr char etalon[]{ 'A', 'B', 'C', 'D', '\n' };
		char v[]{ 'A', 'B', 'C', 'D', '\n' };
		std::ranges::uninitialized_default_construct(std::begin(v), std::end(v));
		if (std::memcmp(v, etalon, sizeof(v)) == 0) {
			std::cout << "  ";
			// Maybe undefined behavior, pending CWG 1997:
			// for (const char c : v) { std::cout << c << ' '; }
			for (const char c : etalon) { std::cout << c << ' '; }
		}
		else {
			std::cout << "Unspecified\n";
		}
	}
	//*/

	// std::uninitialized_default_construct_n C++17
	// constructs objects by default-initialization in an uninitialized area of memory, defined by a start and a count
	/*
	{
		struct S { std::string m{ "Default value" }; };

		constexpr int n{ 3 };
		alignas(alignof(S)) unsigned char mem[n * sizeof(S)];

		try
		{
			auto first{ reinterpret_cast<S*>(mem) };
			auto last = std::uninitialized_default_construct_n(first, n);

			for (auto it{ first }; it != last; ++it) {
				std::cout << it->m << '\n';
			}

			std::destroy(first, last);
		}
		catch (...)
		{
			std::cout << "Exception!\n";
		}

		// Notice that for "trivial types" the uninitialized_default_construct_n
		// generally does not zero-initialize the given uninitialized memory area.
		int v[]{ 1, 2, 3, 4 };
		const int original[]{ 1, 2, 3, 4 };
		std::uninitialized_default_construct_n(std::begin(v), std::size(v));
		// for (const int i : v) { std::cout << i << ' '; }
		// Maybe undefined behavior, pending CWG 1997.
		std::cout <<
			(std::memcmp(v, original, sizeof(v)) == 0 ? "Unmodified\n" : "Modified\n");
		// The result is unspecified.
	}
	//*/

	// std::ranges::uninitialized_default_construct_n C++20
	// constructs objects by default-initialization in an uninitialized area of memory, defined by a start and count
	/*
	{
		//struct S { std::string m{ "█▓▒░ █▓▒░ " }; };
		struct S { std::string m{ "43210 43210" }; };

		constexpr int n{ 4 };
		alignas(alignof(S)) char out[n * sizeof(S)];

		try
		{
			auto first{ reinterpret_cast<S*>(out) };
			auto last = std::ranges::uninitialized_default_construct_n(first, n);

			auto count{ 1 };
			for (auto it{ first }; it != last; ++it) {
				std::cout << count++ << ' ' << it->m << '\n';
			}

			std::ranges::destroy(first, last);
		}
		catch (...) { std::cout << "Exception!\n"; }

		// Notice that for "trivial types" the uninitialized_default_construct_n
		// generally does not zero-fill the given uninitialized memory area.
		constexpr int etalon[]{ 1, 2, 3, 4, 5, 6 };
		int v[]{ 1, 2, 3, 4, 5, 6 };
		std::ranges::uninitialized_default_construct_n(std::begin(v), std::size(v));
		if (std::memcmp(v, etalon, sizeof(v)) == 0) {
			// Maybe undefined behavior, pending CWG 1997:
			// for (const int i : v) { std::cout << i << ' '; }
			for (const int i : etalon) { std::cout << i << ' '; }
		}
		else {
			std::cout << "Unspecified!";
		}
		std::cout << '\n';
	}
	//*/

	// std::uninitialized_value_construct C++17
	// constructs objects by value-initialization in an uninitialized area of memory, defined by a range
	/*
	{
		struct S { std::string m{ "Default value" }; };

		constexpr int n{ 3 };
		alignas(alignof(S)) unsigned char mem[n * sizeof(S)];

		try
		{
			auto first{ reinterpret_cast<S*>(mem) };
			auto last{ first + n };

			std::uninitialized_value_construct(first, last);

			for (auto it{ first }; it != last; ++it) {
				std::cout << it->m << '\n';
			}

			std::destroy(first, last);
		}
		catch (...)
		{
			std::cout << "Exception!\n";
		}

		// Notice that for "trivial types" the uninitialized_value_construct
		// zero-fills the given uninitialized memory area.
		int v[]{ 1, 2, 3, 4 };
		for (const int i : v) { std::cout << i << ' '; }
		std::cout << '\n';
		std::uninitialized_value_construct(std::begin(v), std::end(v));
		for (const int i : v) { std::cout << i << ' '; }
		std::cout << '\n';
	}
	//*/

	// std::ranges::uninitialized_value_construct C++20
	// constructs objects by value-initialization in an uninitialized area of memory, defined by a range
	/*
	{
		//struct S { std::string m{ "▄▀▄▀▄▀▄▀" }; };
		struct S { std::string m{ "^_^_^_^_" }; };

		constexpr int n{ 4 };
		alignas(alignof(S)) char out[n * sizeof(S)];

		try
		{
			auto first{ reinterpret_cast<S*>(out) };
			auto last{ first + n };

			std::ranges::uninitialized_value_construct(first, last);

			auto count{ 1 };
			for (auto it{ first }; it != last; ++it) {
				std::cout << count++ << ' ' << it->m << '\n';
			}

			std::ranges::destroy(first, last);
		}
		catch (...)
		{
			std::cout << "Exception!\n";
		}

		// Notice that for "trivial types" the uninitialized_value_construct
		// zero-fills the given uninitialized memory area.
		int v[]{ 0, 1, 2, 3 };
		std::cout << ' ';
		for (const int i : v) { std::cout << ' ' << static_cast<char>(i + 'A'); }
		std::cout << "\n ";
		std::ranges::uninitialized_value_construct(std::begin(v), std::end(v));
		for (const int i : v) { std::cout << ' ' << static_cast<char>(i + 'A'); }
		std::cout << '\n';
	}
	//*/

	// std::uninitialized_value_construct_n C++17
	// constructs objects by value-initialization in an uninitialized area of memory, defined by a start and a count
	/*
	{
		struct S { std::string m{ "Default value" }; };

		constexpr int n{ 3 };
		alignas(alignof(S)) unsigned char mem[n * sizeof(S)];

		try
		{
			auto first{ reinterpret_cast<S*>(mem) };
			auto last = std::uninitialized_value_construct_n(first, n);

			for (auto it{ first }; it != last; ++it) {
				std::cout << it->m << '\n';
			}

			std::destroy(first, last);
		}
		catch (...)
		{
			std::cout << "Exception!\n";
		}

		// Notice that for "trivial types" the uninitialized_value_construct_n
		// zero-initializes the given uninitialized memory area.
		int v[]{ 1, 2, 3, 4 };
		for (const int i : v) { std::cout << i << ' '; }
		std::cout << '\n';
		std::uninitialized_value_construct_n(std::begin(v), std::size(v));
		for (const int i : v) { std::cout << i << ' '; }
	}
	//*/

	// std::ranges::uninitialized_value_construct_n C++20
	// constructs objects by value-initialization in an uninitialized area of memory, defined by a start and a count
	/*
	{
		//struct S { std::string m{ "█▓▒░ █▓▒░ █▓▒░ " }; };
		struct S { std::string m{ "3210 3210 3210" }; };

		constexpr int n{ 4 };
		alignas(alignof(S)) char out[n * sizeof(S)];

		try
		{
			auto first{ reinterpret_cast<S*>(out) };
			auto last = std::ranges::uninitialized_value_construct_n(first, n);

			auto count{ 1 };
			for (auto it{ first }; it != last; ++it) {
				std::cout << count++ << ' ' << it->m << '\n';
			}

			std::ranges::destroy(first, last);
		}
		catch (...)
		{
			std::cout << "Exception!\n";
		}

		// Notice that for "trivial types" the uninitialized_value_construct_n
		// zero-initializes the given uninitialized memory area.
		int v[]{ 1, 2, 3, 4, 5, 6, 7, 8 };
		std::cout << ' ';
		for (const int i : v) { std::cout << i << ' '; }
		std::cout << "\n ";
		std::ranges::uninitialized_value_construct_n(std::begin(v), std::size(v));
		for (const int i : v) { std::cout << i << ' '; }
		std::cout << '\n';
	}
	//*/

	// std::destroy C++17
	// destroys a range of objects
	/*
	{
		struct Tracer {
			int value;
			~Tracer() { std::cout << value << " destructed\n"; }
		};

		alignas(Tracer) unsigned char buffer[sizeof(Tracer) * 8];

		for (int i = 0; i < 8; ++i)
			new(buffer + sizeof(Tracer) * i) Tracer{ i }; //manually construct objects

		auto ptr = std::launder(reinterpret_cast<Tracer*>(buffer));

		std::destroy(ptr, ptr + 8);
	}
	//*/

	// std::ranges::destroy C++20
	// destroys a range of objects
	/*
	{
		struct Tracer {
			int value;
			~Tracer() { std::cout << value << " destructed\n"; }
		};

		alignas(Tracer) unsigned char buffer[sizeof(Tracer) * 8];

		for (int i = 0; i < 8; ++i)
			new(buffer + sizeof(Tracer) * i) Tracer{ i }; //manually construct objects

		auto ptr = std::launder(reinterpret_cast<Tracer*>(buffer));

		std::ranges::destroy(ptr, ptr + 8);
	}
	//*/

	// std::destroy_n C++17
	// destroys a number of objects in a range
	/*
	{
		struct Tracer {
			int value;
			~Tracer() { std::cout << value << " destructed\n"; }
		};

		alignas(Tracer) unsigned char buffer[sizeof(Tracer) * 8];

		for (int i = 0; i < 8; ++i)
			new(buffer + sizeof(Tracer) * i) Tracer{ i }; //manually construct objects

		auto ptr = std::launder(reinterpret_cast<Tracer*>(buffer));

		std::destroy_n(ptr, 8);
	}
	//*/

	// std::ranges::destroy_n C++20
	// destroys a number of objects in a range
	/*
	{
		struct Tracer {
			int value;
			~Tracer() { std::cout << value << " destructed\n"; }
		};

		alignas(Tracer) unsigned char buffer[sizeof(Tracer) * 8];

		for (int i = 0; i < 8; ++i)
			new(buffer + sizeof(Tracer) * i) Tracer{ i }; //manually construct objects

		auto ptr = std::launder(reinterpret_cast<Tracer*>(buffer));

		std::ranges::destroy_n(ptr, 8);
	}
	//*/

	// std::destroy_at C++17
	// destroys an object at a given address
	/*
	{
		struct Tracer {
			int value;
			~Tracer() { std::cout << value << " destructed\n"; }
		};

		alignas(Tracer) unsigned char buffer[sizeof(Tracer) * 8];

		for (int i = 0; i < 8; ++i)
			new(buffer + sizeof(Tracer) * i) Tracer{ i }; //manually construct objects

		auto ptr = std::launder(reinterpret_cast<Tracer*>(buffer));

		for (int i = 0; i < 8; ++i)
			std::destroy_at(ptr + i);
	}
	//*/

	// std::ranges::destroy_at C++20
	// destroys an object at a given address
	/*
	{
		struct Tracer {
			int value;
			~Tracer() { std::cout << value << " destructed\n"; }
		};

		alignas(Tracer) unsigned char buffer[sizeof(Tracer) * 8];

		for (int i = 0; i < 8; ++i)
			new(buffer + sizeof(Tracer) * i) Tracer{ i }; //manually construct objects

		auto ptr = std::launder(reinterpret_cast<Tracer*>(buffer));

		for (int i = 0; i < 8; ++i)
			std::ranges::destroy_at(ptr + i);

	}
	//*/

	// std::construct_at C++20
	// creates an object at a given address
	/*
	{
		struct S {
			int x;
			float y;
			double z;

			S(int x, float y, double z) : x{ x }, y{ y }, z{ z } { std::cout << "S::S();\n"; }
			~S() { std::cout << "S::~S();\n"; }

			void print() const {
				std::cout << "S { x=" << x << "; y=" << y << "; z=" << z << "; };\n";
			}
		};

		alignas(S) unsigned char storage[sizeof(S)];

		S* ptr = std::construct_at(reinterpret_cast<S*>(storage), 42, 2.71828f, 3.1415);
		ptr->print();

		std::destroy_at(ptr);
	}
	//*/

	// std::ranges::construct_at C++20
	// creates an object at a given address
	/*
	{
		struct S {
			int x;
			float y;
			double z;

			S(int x, float y, double z) : x{ x }, y{ y }, z{ z } { std::cout << "S::S();\n"; }
			~S() { std::cout << "S::~S();\n"; }

			void print() const {
				std::cout << "S { x=" << x << "; y=" << y << "; z=" << z << "; };\n";
			}
		};

		alignas(S) unsigned char buf[sizeof(S)];

		S* ptr = std::ranges::construct_at(reinterpret_cast<S*>(buf), 42, 2.71828f, 3.1415);
		ptr->print();

		std::ranges::destroy_at(ptr);
	}
	//*/

	/****************************************************************************/
	// C library
	// header <cstlib>
	/****************************************************************************/

	// std::qsort
	// sorts a range of elements with unspecified type
	/*
	{
		std::array a{ -2, 99, 0, -743, INT_MAX, 2, INT_MIN, 4 };

		std::qsort(
			a.data(),
			a.size(),
			sizeof(decltype(a)::value_type),
			[](const void* x, const void* y) {
				const int arg1 = *static_cast<const int*>(x);
				const int arg2 = *static_cast<const int*>(y);
				const auto cmp = arg1 <=> arg2;
				if (cmp < 0) return -1;
				if (cmp > 0) return 1;
				return 0;
			});

		for (int ai : a)
			std::cout << ai << ' ';

	}
	//*/

	// std::bsearch
	// searches an array for an element of unspecified type
	/*
	{
		template <typename T>
		int compare(const void* a, const void* b) {
			const auto& arg1 = *(static_cast<const T*>(a));
			const auto& arg2 = *(static_cast<const T*>(b));
			const auto cmp = arg1 <=> arg2;
			return cmp < 0 ? -1
				: cmp > 0 ? +1
				: 0;
		};

		std::array arr{ 1, 2, 3, 4, 5, 6, 7, 8 };

		for (const int key : { 4, 8, 9 }) {

			const int* p = static_cast<int*>(
				std::bsearch(&key,
					arr.data(),
					arr.size(),
					sizeof(decltype(arr)::value_type),
					compare<int>));

			std::cout << "value " << key;
			(p) ? std::cout << " found at position " << (p - arr.data()) << '\n'
				: std::cout << " not found\n";
		}
	}
	//*/

	return 0;
}

// 
/*
{
}
//*/