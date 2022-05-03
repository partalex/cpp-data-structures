#include<iostream>
#include<iterator>
#include<ranges>
#include<vector>
#include<array>
#include<span>
#include<algorithm>

int main()
{
	/****************************************************************************/
	// Ranges access
	// header <ranges>
	// header <iterator>
	/****************************************************************************/

	// std::ranges::begin
	// returns an iterator to the beginning of a range
	/*
	{
		std::vector<int> v = { 3, 1, 4 };
		auto vi = std::ranges::begin(v);
		std::cout << *vi << '\n';
		*vi = 42; // OK

		int a[] = { -5, 10, 15 };
		auto ai = std::ranges::begin(a);
		std::cout << *ai << '\n';
		*ai = 42; // OK
	}
	//*/

	// std::ranges::end
	// returns a sentinel indicating the end of a range
	/*
	{
		std::vector<int> v = { 3, 1, 4 };
		namespace ranges = std::ranges;
		if (ranges::find(v, 5) != ranges::end(v)) {
			std::cout << "found a 5 in vector v!\n";
		}

		int a[] = { 5, 10, 15 };
		if (ranges::find(a, 5) != ranges::end(a)) {
			std::cout << "found a 5 in array a!\n";
		}
	}
	//*/

	// std::ranges::cbegin
	// returns an iterator to the beginning of a read-only range
	/*
	{
		std::vector<int> v = { 3, 1, 4 };
		auto vi = std::ranges::cbegin(v);
		std::cout << *vi << '\n';
		// *vi = 42; // Error: read-only variable is not assignable

		int a[] = { -5, 10, 15 };
		auto ai = std::ranges::cbegin(a);
		std::cout << *ai << '\n';
		// *ai = 42; // Error: read-only variable is not assignabl
	}
	//*/

	// std::ranges::cend
	// returns a sentinel indicating the end of a read-only range
	/*
	{
		std::vector<int> v = { 3, 1, 4 };
		namespace ranges = std::ranges;
		if (ranges::find(v, 5) != ranges::cend(v)) {
			std::cout << "found a 5 in vector v!\n";
		}

		int a[] = { 5, 10, 15 };
		if (ranges::find(a, 5) != ranges::cend(a)) {
			std::cout << "found a 5 in array a!\n";
		}
	}
	//*/

	// std::ranges::rbegin
	// returns a reverse iterator to a range
	/*
	{
		std::vector<int> v = { 3, 1, 4 };
		auto vi = std::ranges::rbegin(v);
		std::cout << *vi << '\n';
		*vi = 42; // OK

		int a[] = { -5, 10, 15 };
		auto ai = std::ranges::rbegin(a);
		std::cout << *ai << '\n';
		*ai = 42; // OK

		// auto x_x = std::ranges::rbegin(std::vector{6,6,6});
		// ill-formed: the argument is an rvalue (see Notes UP)

		auto si = std::ranges::rbegin(std::span{ a }); // OK:
		static_assert(std::ranges::enable_borrowed_range <
			std::remove_cv_t<decltype(std::span{ a }) >> );
		*si = 42; // OK
	}
	//*/

	// std::ranges::rend
	// returns a sentinel indicating the end of a reversed range
	/*
	{
		std::vector<int> v = { 3, 1, 4 };
		namespace ranges = std::ranges;
		if (ranges::find(ranges::rbegin(v), ranges::rend(v), 5) != ranges::rend(v)) {
			std::cout << "found a 5 in vector `v`!\n";
		}

		int a[] = { 5, 10, 15 };
		if (ranges::find(ranges::rbegin(a), ranges::rend(a), 5) != ranges::rend(a)) {
			std::cout << "found a 5 in array `a`!\n";
		}
	}
	//*/

	// std::ranges::crbegin
	// returns a reverse iterator to a read-only range
	/*
	{
		std::vector<int> v = { 3, 1, 4 };
		auto vi = std::ranges::crbegin(v);
		std::cout << *vi << '\n';

		int a[] = { -5, 10, 15 };
		auto ai = std::ranges::crbegin(a);
		std::cout << *ai << '\n';

		// auto x_x = std::ranges::crbegin(std::vector<int>{6,6,6});
		// ill-formed: the argument is an rvalue (see Notes UP)

		auto si = std::ranges::crbegin(std::span{ a }); // OK:
		static_assert(std::ranges::enable_borrowed_range <
			std::remove_cv_t<decltype(std::span{ a }) >> );
		std::cout << *si << '\n';
	}
	//*/

	// std::ranges::crend
	// returns a reverse end iterator to a read-only range
	/*
	{
		int a[] = { 4, 6, -3, 9, 10 };
		std::cout << "Array backwards: ";
		namespace ranges = std::ranges;
		ranges::copy(ranges::rbegin(a), ranges::rend(a),
			std::ostream_iterator<int>(std::cout, " "));

		std::cout << "\nVector backwards: ";
		std::vector<int> v = { 4, 6, -3, 9, 10 };
		ranges::copy(ranges::rbegin(v), ranges::rend(v),
			std::ostream_iterator<int>(std::cout, " "));
	}
	//*/

	// std::ranges::size
	// returns an integer equal to the size of a range
	/*
	{
		auto v = std::vector<int>{};
		std::cout << "ranges::size(v) == " << std::ranges::size(v) << '\n';

		auto il = { 7 };
		std::cout << "ranges::size(il) == " << std::ranges::size(il) << '\n';

		int array[] = { 4, 5 }; // array has a known bound
		std::cout << "ranges::size(array) == " << std::ranges::size(array) << '\n';

		std::cout << std::boolalpha << "is_signed: "
			<< std::is_signed_v<decltype(std::ranges::size(v))> << '\n';
	}
	//*/

	// std::ranges::ssize
	// returns a signed integer equal to the size of a range
	/*
	{
		std::array arr{ 1, 2, 3, 4, 5 };
		auto s = std::ranges::ssize(arr);

		std::cout << "ranges::ssize(arr) = " << s << '\n'
			<< "ranges::ssize is "
			<< (std::is_signed_v<decltype(s)> ? "signed" : "unsigned")
			<< '\n';

		std::cout << "reversed arr: ";

		for (--s; s >= 0; --s)
			std::cout << arr[s] << ' ';

		std::cout << "\n" "s = " << s << '\n';
	}
	//*/

	// std::ranges::empty
	// checks whether a range is empty
	/*
	{
		auto print = [](const char id, auto&& v) {
			std::cout << id << " :";
			if (std::ranges::empty(v)) {
				std::cout << '\t' << id << ") Empty\n";
				return;
			}

			std::cout << '\t' << id << ") Elements:";
			for (const auto& element : v) {
				std::cout << ' ' << element;
			}

			std::cout << '\n';
		};
		{
			auto v = std::vector<int>{ 1, 2, 3 };
			std::cout << "(1) ranges::empty uses std::vector::empty:\n";
			// make function that print vector

			print('a', v);

			v.clear();
			print('b', v);
		}
		{
			std::cout << "(2) ranges::empty uses ranges::size(initializer_list):\n";
			auto il = { 7, 8, 9 };
			print('a', il);

			print('b', std::initializer_list<int>{});
		}
		{
			std::cout << "(2) ranges::empty on a raw array uses ranges::size:\n";
			int array[] = { 4, 5, 6 }; // array has a known bound
			print('a', array);
		}
		{
			struct Scanty : private std::vector<int> {
				using std::vector<int>::begin;
				using std::vector<int>::end;
				using std::vector<int>::push_back;
				// Note: both empty() and size() are hidden
			};

			std::cout << "(3) calling ranges::empty on an object w/o empty() or size():\n";
			Scanty y;
			print('a', y);
			y.push_back(42);
			print('b', y);
		}
	}
	//*/

	// std::ranges::data
	// obtains a pointer to the beginning of a contiguous range
	/*
	{
		std::string s{ "Hello world!\n" };

		char a[20]; // storage for a C-style string
		std::strcpy(a, std::ranges::data(s));
		// [data(s), data(s) + size(s)] is guaranteed to be an NTBS

		std::cout << a;
	}
	//*/

	// std::ranges::cdata
	// obtains a pointer to the beginning of a read-only contiguous range
	/*
	{
		std::string src{ "hello world!\n" };

		//  std::ranges::cdata(src)[0] = 'H'; // error, src.data() is treated as read-only
		std::ranges::data(src)[0] = 'H'; // OK, src.data() is a non-const storage

		char dst[20]; // storage for a C-style string
		std::strcpy(dst, std::ranges::cdata(src));
		// [data(src), data(src) + size(src)] is guaranteed to be an NTBS

		std::cout << dst;
	}
	//*/

	/****************************************************************************/
	// Ranges primitives
	// header <ranges>
	/****************************************************************************/

	// neke glupostji

	// std::ranges::dangling
	// a placeholder type indicating that an iterator or a subrange should not be returned since it would be dangling
	// ne kontam za sta je ovo
	/*
	{
		auto get_array_by_value = [] { return std::array{ 0, 1, 0, 1 }; };
		auto dangling_iter = std::ranges::max_element(get_array_by_value());
		static_assert(std::is_same_v<std::ranges::dangling, decltype(dangling_iter)>);
		//  std::cout << *dangling_iter << '\n'; // compilation error: no match for 'operator*'
												 // (operand type is 'std::ranges::dangling')

		auto get_persistent_array = []() -> const std::array<int, 4>&{
			static constexpr std::array a{ 0, 1, 0, 1 };
			return a;
		};
		auto valid_iter = std::ranges::max_element(get_persistent_array());
		static_assert(!std::is_same_v<std::ranges::dangling, decltype(valid_iter)>);
		std::cout << *valid_iter << ' '; // 1


		auto get_string_view = [] { return std::string_view{ "alpha" }; };
		auto valid_iter2 = std::ranges::min_element(get_string_view());
		// OK: std::basic_string_view models borrowed_range
		static_assert(!std::is_same_v<std::ranges::dangling, decltype(valid_iter2)>);
		std::cout << '\'' << *valid_iter2 << '\'' << '\n'; // 'a'
	}
	//*/

	// ranges::borrowed_iterator_t; ranges::borrowed_subrange_t
	// obtains iterator type or subrange type of a borrowed_range

	// std::ranges::range
	// specifies that a type is a range, that is, it provides a begin iterator and an end sentinel
	// ovaj primer ne kontam sta je 
	/*
	{

		template <typename T>
		struct range_t : private T {
			using T::begin, T::end;
		};
		static_assert(std::ranges::range< range_t<std::vector<int>> >);

		template <typename T> struct scalar_t {
			T t{}; // no begin/end
		};
		static_assert(not std::ranges::range< scalar_t<int> >);

		int main() {
			if constexpr (range_t<std::vector<int>> r; std::ranges::range<decltype(r)>) {
				std::cout << "r is a range\n";
			}

			if constexpr (scalar_t<int> s; not std::ranges::range<decltype(s)>) {
				std::cout << "s is not a range\n";
			}
		}

	}
	//*/

	// std::ranges::borrowed_range, std::ranges::enable_borrowed_range
	// specifies that a type is a range and iterators obtained from an expression of it can be safely returned without danger of dangling
	/*
	{
		template <typename T, std::size_t N>
		struct MyRange : std::array<T, N> { };

		template <typename T, std::size_t N>
		inline constexpr bool std::ranges::enable_borrowed_range<MyRange<T, N>> = false;

		template <typename T, std::size_t N>
		struct MyBorrowedRange : std::span<T, N> { };

		template <typename T, std::size_t N>
		inline constexpr bool std::ranges::enable_borrowed_range<MyBorrowedRange<T, N>> = true;

		int main()
		{
			static_assert(std::ranges::range<MyRange<int, 8>>);
			static_assert(std::ranges::borrowed_range<MyRange<int, 8>> == false);
			static_assert(std::ranges::range<MyBorrowedRange<int, 8>>);
			static_assert(std::ranges::borrowed_range<MyBorrowedRange<int, 8>> == true);

			auto getMyRangeByValue = [] { return MyRange<int, 4>{ {1, 2, 42, 3} }; };
			auto dangling_iter = std::ranges::max_element(getMyRangeByValue());
			static_assert(std::is_same_v<std::ranges::dangling, decltype(dangling_iter)>);
			//  *dangling_iter; // compilation error (i.e. dangling protection works.)

			auto my = MyRange<int, 4>{ {1, 2, 42, 3} };
			auto valid_iter = std::ranges::max_element(my);
			std::cout << *valid_iter << ' '; // OK: 42

			auto getMyBorrowedRangeByValue = [] {
				static int sa[4]{ 1, 2, 42, 3 };
				return MyBorrowedRange<int, std::size(sa)>{sa};
			};
			auto valid_iter2 = std::ranges::max_element(getMyBorrowedRangeByValue());
			std::cout << *valid_iter2 << '\n'; // OK: 42
		}
	}
	//*/

	// std::ranges::sized_range, std::ranges::disable_sized_range
	// specifies that a range knows its size in constant time
	// nema pojma sta je ovo

	// std::ranges::view, std::ranges::enable_view, std::ranges::view_base
	// specifies that a range is a view, that is, it has constant time copy/move/assignment

	// std::ranges::input_range
	// specifies a range whose iterator type satisfies input_iterator

	// std::ranges::output_range
	// specifies a range whose iterator type satisfies output_iterator

	// std::ranges::forward_range
	// specifies a range whose iterator type satisfies forward_iterator

	// std::ranges::bidirectional_range
	// specifies a range whose iterator type satisfies bidirectional_iterator

	// std::ranges::random_access_range
	// specifies a range whose iterator type satisfies random_access_iterator

	// std::ranges::contiguous_range
	// specifies a range whose iterator type satisfies contiguous_iterator

	// std::ranges::common_range
	// specifies that a range has identical iterator and sentinel types

	// std::ranges::viewable_range
	// specifies the requirements for a range to be safely convertible to a view

	/****************************************************************************/
	// Views
	// header <ranges>
	/****************************************************************************/


	return 0;
}


// 
/*
{
}
//*/