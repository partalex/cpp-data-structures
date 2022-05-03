#include<algorithm>
#include<array>
#include<cassert>
#include<cctype>
#include<iomanip>
#include<iostream>
#include<iterator>
#include<list>
#include<map>
#include<numeric>
#include<ranges>
#include<span>
#include<sstream>
#include<string>
#include<string_view>
#include<tuple>
#include<vector>

// R | C | D <=> (R | C) | D
// different of R | (C | D) 

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

	// std::ranges::views::empty, std::ranges::empty_view
	// an empty view with no elements
	/*
	{
		std::ranges::empty_view<long> e;
		static_assert(std::ranges::empty(e));
		static_assert(0 == e.size());
		static_assert(nullptr == e.data());
		static_assert(nullptr == e.begin());
		static_assert(nullptr == e.end());
	}
	//*/

	// std::ranges::views::single, std::ranges::single_view
	// a view that contains a single element of a specified value
	/*
	{
		constexpr std::ranges::single_view sv1{ 3.1415 }; // uses (const T&) constructor
		static_assert(sv1);
		static_assert(not sv1.empty());

		std::cout << "1) *sv1.data(): " << *sv1.data() << '\n'
			<< "2) *sv1.begin(): " << *sv1.begin() << '\n'
			<< "3)  sv1.size(): " << sv1.size() << '\n'
			<< "4)  distance: " << std::distance(sv1.begin(), sv1.end()) << '\n';

		std::string str{ "C++20" };
		std::cout << "5)  str = " << std::quoted(str) << '\n';
		std::ranges::single_view sv2{ std::move(str) }; // uses (T&&) constructor
		std::cout << "6) *sv2.data(): " << quoted(*sv2.data()) << '\n'
			<< "7)  str = " << quoted(str) << '\n';

		std::ranges::single_view<std::tuple<int, double, std::string>>
			sv3{ std::in_place, 42, 3.14, "hehe" }; // uses (std::in_place_t, Args&&... args)

		std::cout << "8)  sv3 holds a tuple: { "
			<< std::get<0>(sv3[0]) << ", "
			<< std::get<1>(sv3[0]) << ", "
			<< std::get<2>(sv3[0]) << " }\n";
	}
	//*/

	// std::ranges::views::iota, std::ranges::iota_view
	// a view consisting of a sequence generated by repeatedly incrementing an initial value
	/*
	{
		for (int i : std::ranges::iota_view{ 1, 10 })
			std::cout << i << ' ';
		std::cout << '\n';

		for (int i : std::views::iota(1, 10))
			std::cout << i << ' ';
		std::cout << '\n';

		struct Bound
		{
			int bound;
			bool operator==(int x) const { return x == bound; }
		};

		for (int i : std::views::iota(1, Bound{ 10 }))
			std::cout << i << ' ';
		std::cout << '\n';

		for (int i : std::views::iota(1) | std::views::take(9))
			std::cout << i << ' ';
		std::cout << '\n';

		std::ranges::for_each(std::views::iota(1, 10), [](int i) {
			std::cout << i << ' ';
			});
		std::cout << '\n';
	}
	//*/

	// std::ranges::views::istream, std::ranges::basic_istream_view, std::ranges::istream_view, std::ranges::wistream_view
	// a view consisting of the elements obtained by successive application of operator>> on the associated input stream
	/*
	{
		auto words = std::istringstream{ "today is yesterday’s tomorrow" };
		for (const auto& s : std::ranges::istream_view<std::string>(words)) {
			std::cout << std::quoted(s, '/') << ' ';
		}
		std::cout << '\n';

		auto floats = std::istringstream{ "1.1  2.2\t3.3\v4.4\f55\n66\r7.7  8.8" };
		std::ranges::copy(
			std::ranges::istream_view<float>(floats),
			std::ostream_iterator<float>{std::cout, ", "});
		std::cout << '\n';

	}
	//*/

	/****************************************************************************/
	// Range factories
	// header <ranges>
	// namespace std::ranges
	/****************************************************************************/

	// std::ranges::views::all, std::ranges::views::all_t
	// a view that includes all elements of a range
	/*
	{
		std::vector<int> v{ 0,1,2,3,4,5 };
		for (int n : std::views::all(v) | std::views::take(2)) {
			std::cout << n << ' ';
		}

		static_assert(std::is_same<
			decltype(std::views::single(42)),
			std::ranges::single_view<int>
		>{});

		static_assert(std::is_same<
			decltype(std::views::all(v)),
			std::ranges::ref_view<std::vector<int, std::allocator<int>>>
		>{});

		int a[]{ 1,2,3,4 };
		static_assert(std::is_same<
			decltype(std::views::all(a)),
			std::ranges::ref_view<int[4]>
		>{});

		static_assert(std::is_same<
			decltype(std::ranges::subrange{ std::begin(a) + 1, std::end(a) - 1 }),
			std::ranges::subrange<int*, int*, std::ranges::subrange_kind(1)>
		> {});
	}
	//*/

	// std::ranges::ref_view
	// a view of the elements of some other range
	/*
	{
		const std::string s{ "cosmos" };

		const std::ranges::take_view tv{ s, 3 };
		const std::ranges::ref_view rv{ tv };

		std::cout
			<< std::boolalpha
			<< "call empty() : " << rv.empty() << '\n'
			<< "call size()  : " << rv.size() << '\n'
			<< "call begin() : " << *rv.begin() << '\n'
			<< "call end()   : " << *(rv.end() - 1) << '\n'
			<< "call data()  : " << rv.data() << '\n'
			<< "call base()  : " << rv.base().size() << '\n' // ~> tv.size()
			<< "range-for    : ";

		for (const auto c : rv) { std::cout << c; }
		std::cout << '\n';
	}
	//*/

	// std::ranges::owning_view
	// a view with unique ownership of some range
	/*
	{
		using namespace std::literals;
		std::ranges::owning_view ov{ "cosmos"s }; // the deduced type of R is std::string;
												  // `ov` is the only owner of this string
		std::cout
			<< std::boolalpha
			<< "call empty() : " << ov.empty() << '\n'
			<< "call size()  : " << ov.size() << '\n'
			<< "call front() : " << ov.front() << '\n' // same as *(ov.begin())
			<< "call back()  : " << ov.back() << '\n' // equals to *(ov.end()-1)
			<< "call data()  : " << ov.data() << '\n'
			<< "call base()  : " << ov.base().size() << '\n' // ~> ov.size()
			<< "sizeof(ov)   : " << sizeof(ov) << '\n' // typically equals to sizeof(R)
			<< "range-for    : \"";

		for (const char c : ov)
			std::cout << c;
		std::cout << "\"\n";

		std::ranges::owning_view<std::string> ov2;
		assert(ov2.empty());
		//  ov2 = ov; // compile-time error: copy assignment operator is deleted
		ov2 = std::move(ov); // OK
		assert(ov.empty());
		assert(ov2.size() == 6);
	}
	//*/

	// std::ranges::views::filter, std::ranges::filter_view
	// a view that consists of the elements of a range that satisfies a predicate
	/*
	{
		auto even = [](int i) { return 0 == i % 2; };
		auto square = [](int i) { return i * i; };

		for (int i : std::views::iota(0, 6)
			| std::views::filter(even)
			| std::views::transform(square)) {
			std::cout << i << ' ';
		}
	}
	//*/

	// std::ranges::views::transform, std::ranges::transform_view
	// a view of a sequence that applies a transformation function to each element
	/*
	{
		char rot13a(const char x, const char a)
		{
			return a + (x - a + 13) % 26;
		}

		char rot13(const char x)
		{
			if (x >= 'A' && x <= 'Z') {
				return rot13a(x, 'A');
			}

			if (x >= 'a' && x <= 'z') {
				return rot13a(x, 'a');
			}

			return x;
		}

		auto show = [](const unsigned char x) { std::putchar(x); };

		std::string in{ "cppreference.com\n" };
		std::ranges::for_each(in, show);
		std::ranges::for_each(in | std::views::transform(rot13), show);

		std::string out;
		std::ranges::copy(std::views::transform(in, rot13), std::back_inserter(out));
		std::ranges::for_each(out, show);
		std::ranges::for_each(out | std::views::transform(rot13), show);
	}
	//*/

	// std::ranges::views::take, std::ranges::take_view
	// a view consisting of the first N elements of another view
	/*
	{
		auto print = [](char x) { std::cout << x; };

		constexpr char pi[]{ '3', '.', '1', '4', '1', '5', '9', '2' };

		std::ranges::for_each(pi | std::ranges::views::take(6), print);
		std::cout << '\n';

		std::ranges::for_each(std::ranges::take_view{ pi, 42 }, print); // safely takes only 8 chars
		std::cout << '\n';
	}
	//*/

	// std::ranges::views::take_while, std::ranges::take_while_view
	// a view consisting of the initial elements of another view, until the first element on which a predicate returns false
	/*
	{
		for (int year : std::views::iota(2017)
			| std::views::take_while([](int y) { return y <= 2020; })) {
			std::cout << year << ' ';
		}
		std::cout << '\n';

		const char idea[]{ "Today is yesterday's tomorrow!.." };
		for (char x : std::ranges::take_while_view(idea, [](char c) { return c != '.'; })) {
			std::cout << x;
		}
		std::cout << '\n';
	}
	//*/

	// std::ranges::views::drop, std::ranges::drop_view
	// a view consisting of elements of another view, skipping the first N elements
	/*
	{
		const auto nums = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		for (int i : nums | std::views::drop(2))
			std::cout << i << ' ';
		std::cout << '\n';

		for (int i : std::views::iota(1, 10) | std::views::drop(2))
			std::cout << i << ' ';
		std::cout << '\n';

		for (int i : std::ranges::drop_view{ nums, 2 })
			std::cout << i << ' ';
		std::cout << '\n';
	}
	//*/

	// std::ranges::views::drop_while, std::ranges::drop_while_view
	// a view consisting of the elements of another view, skipping the initial subsequence of elements until the first element where the predicate returns false
	/*
	{
		std::string trim(std::string_view const in)
		{
			auto view
				= in
				| std::views::drop_while(isspace)
				| std::views::reverse
				| std::views::drop_while(isspace)
				| std::views::reverse
				;
			return { view.begin(), view.end() };
		};
		const auto = trim(" \f\n\t\r\vHello, C++20!\f\n\t\r\v ");
		std::cout << std::quoted(s) << '\n';

		static constexpr auto v = { 0, 1, 2, 3, 4, 5 };
		for (int n : v | std::views::drop_while([](int i) { return i < 3; })) {
			std::cout << n << ' ';
		}
	}
	//*/

	// std::ranges::views::join, std::ranges::join_view
	// a view consisting of the sequence obtained from flattening a view of ranges
	/*
	{
		using namespace std::literals;
		const auto bits = { "https:"sv, "//"sv, "cppreference"sv, "."sv, "com"sv };
		for (char const c : bits | std::views::join) std::cout << c;
		std::cout << '\n';

		const std::vector<std::vector<int>> v{ {1,2}, {3,4,5}, {6}, {7,8,9} };
		auto jv = std::ranges::join_view(v);
		for (int const e : jv) std::cout << e << ' ';
		std::cout << '\n';
	}
	//*/

	// std::ranges::views::split, std::ranges::split_view
	// a view over the subranges obtained from splitting another view using a delimiter
	/*
	{
		constexpr std::string_view words{ "Hello-_-C++-_-20-_-!" };
		constexpr std::string_view delim{ "-_-" };
		for (const auto word : std::views::split(words, delim))
			std::cout << std::quoted(std::string_view(word.begin(), word.end())) << ' ';
	}
	//*/

	// std::ranges::views::lazy_split, std::ranges::lazy_split_view
	// a view over the subranges obtained from splitting another view using a delimiter
	/*
	{
		auto print = [](auto const& view)
		{
			// `view` is a std::views::lazy_split_view::::value_type

			for (std::cout << "{ "; const auto element : view)
				std::cout << element << ' ';
			std::cout << "} ";
		};

		constexpr static auto source = { 0, 1, 0, 2, 3, 0, 4, 5, 6, 0, 7, 8, 9 };
		constexpr int delimiter{ 0 };
		constexpr std::ranges::lazy_split_view outer_view{ source, delimiter };
		std::cout << "splits[" << std::ranges::distance(outer_view) << "]:  ";
		for (auto const& inner_view : outer_view)
			print(inner_view);

		constexpr std::string_view hello{ "Hello C++ 20 !" };
		std::cout << "\n" "substrings: ";
		std::ranges::for_each(hello | std::views::lazy_split(' '), print);

		constexpr std::string_view text{ "Hello-+-C++-+-20-+-!" };
		constexpr std::string_view delim{ "-+-" };
		std::cout << "\n" "substrings: ";
		std::ranges::for_each(text | std::views::lazy_split(delim), print);
	}
	//*/

	// std::ranges::views::counted
	// creates a subrange from an iterator and a count
	/*
	{
		const int a[] = { 1, 2, 3, 4, 5, 6, 7 };
		for (int i : std::views::counted(a, 3))
			std::cout << i << ' ';
		std::cout << '\n';

		const auto il = { 1, 2, 3, 4, 5 };
		for (int i : std::views::counted(il.begin() + 1, 3))
			std::cout << i << ' ';
		std::cout << '\n';
	}
	//*/

	// std::ranges::views::common, std::ranges::common_view
	// converts a view into a common_range
	/*
	{
		auto v1 = { 1, 2, 3, 4, 5 };
		auto i1 = std::counted_iterator{ v1.begin(), std::ssize(v1) };
		auto r1 = std::ranges::subrange{ i1, std::default_sentinel };
		//  auto e1 = std::accumulate(r1.begin(), r1.end(), 0); // error: "common range" required
		auto c1 = std::ranges::common_view{ r1 };
		std::cout << "accumulate: " << std::accumulate(c1.begin(), c1.end(), 0) << '\n';

		// inherited from ranges::view_interface:
		std::cout << "c1.front(): " << c1.front() << '\n';
		std::cout << "c1.back(): " << c1.back() << '\n';
		std::cout << "c1.data(): " << c1.data() << '\n';
		std::cout << "c1[0]: " << c1[0] << '\n';

		auto v2 = std::list{ 1, 2, 3, 4, 5 };
		auto i2 = std::counted_iterator{ v2.begin(), std::ssize(v2) };
		auto r2 = std::ranges::subrange{ i2, std::default_sentinel };
		//  auto e2 = std::accumulate(r2.begin(), r2.end(), 0); // error: "common range" required
		auto c2 = std::ranges::common_view{ r2 };
		std::cout << "accumulate: " << std::accumulate(c2.begin(), c2.end(), 0) << '\n';

		// inherited from ranges::view_interface:
		std::cout << "c2.front(): " << c2.front() << '\n';
		//  auto e3 = c2.back(); // error: "contiguous range" required
		//  auto e4 = c2.data(); // error: "contiguous range" required
		//  auto e5 = c2[0];     // error: "contiguous range" required
	}
	//*/

	// std::ranges::views::reverse, std::ranges::reverse_view
	// a view that iterates over the elements of another bidirectional view in reverse order
	/*
	{
		auto il = { 3, 1, 4, 1, 5, 9 };

		std::ranges::reverse_view rv{ il };
		for (int i : rv)
			std::cout << i << ' ';
		std::cout << '\n';

		for (int i : il | std::views::reverse)
			std::cout << i << ' ';
		std::cout << '\n';

		// operator[] is inherited from `view_interface`
		for (auto i{ 0U }; i != rv.size(); ++i)
			std::cout << rv[i] << ' ';
		std::cout << '\n';
	}
	//*/

	// std::ranges::views::elements, std::ranges::elements_view
	// takes a view consisting of tuple-like values and a number N and produces a view of N'th element of each tuple
	/*
	{
		const std::vector<std::tuple<int, char, std::string>> vt{
			{1, 'A', "a"},
			{2, 'B', "b"},
			{3, 'C', "c"},
			{4, 'D', "d"},
			{5, 'E', "e"},
		};

		for (int const e : std::views::elements<0>(vt)) { std::cout << e << ' '; }
		std::cout << '\n';
		for (char const e : vt | std::views::elements<1>) { std::cout << e << ' '; }
		std::cout << '\n';
		for (std::string const& e : std::views::elements<2>(vt)) { std::cout << e << ' '; }
		std::cout << '\n';
	}
	//*/

	// std::ranges::views::keys, std::ranges::keys_view
	// takes a view consisting of pair-like values and produces a view of the first elements of each pair
	/*
	{
		const std::vector<std::pair<std::string, double>> quark_mass{ // MeV/c²
			{"up", 2.3},      {"down", 4.8},
			{"charm", 1275},  {"strange", 95},
			{"top", 173'210}, {"bottom", 4'180},
		};

		std::cout << "quark name:  | ";
		for (std::string const& name : std::views::keys(quark_mass))
			std::cout << std::setw(9) << name << " | ";

		std::cout << "\n" "mass MeV/c2: | ";
		for (const double mass : std::views::values(quark_mass))
			std::cout << std::setw(9) << mass << " | ";
		std::cout << '\n';
	}
	//*/

	// std::ranges::views::values, std::ranges::values_view
	// takes a view consisting of pair-like values and produces a view of the second elements of each pair
	/*
	{
		std::map<char, int> map{ {'A', 1}, {'B', 2}, {'C', 3}, {'D', 4}, {'E', 5} };

		auto odd = [](int x) { return 0 != (x & 1); };

		std::cout << "Odd values in the map: ";
		for (int value : map | std::views::values | std::views::filter(odd))
			std::cout << value << ' ';
	}
	//*/

	// std::ranges::views::zip, std::ranges::zip_view C++23
	// a view consisting of tuples of references to corresponding elements of the adapted views
	// ovo nece da se prevede jer je C++23
	/*
	{
		auto print = [](auto const rem, auto const& range) {
			for (std::cout << rem; auto const& elem : range)
				std::cout << elem << ' ';
			std::cout << '\n';
		};

		auto x = std::vector{ 1, 2, 3, 4 };
		auto y = std::list<std::string>{ "a", "b", "c", "d", "e" };
		auto z = std::array{ 'A', 'B', 'C', 'D', 'E', 'F' };

		print("Source views:", "");
		print("x: ", x);
		print("y: ", y);
		print("z: ", z);

		print("\nzip(x,y,z):", "");
		for (std::tuple<int&, std::string&, char&> elem : std::views::zip(x, y, z)) {
			std::cout << std::get<0>(elem) << ' '
				<< std::get<1>(elem) << ' '
				<< std::get<2>(elem) << '\n';

			std::get<char&>(elem) += ('a' - 'A'); // modifies the element of z
		}

		print("\nAfter modification, z: ", z);
	}
	//*/

	// std::ranges::views::zip_transform, std::ranges::zip_transform_view C++23
	// a view consisting of tuples of results of application of a transformation function to corresponding elements of the adapted views
	/*
	{
		auto print = [](auto const rem, auto const& r) {
			for (std::cout << rem; auto const& e : r)
				std::cout << e << ' ';
			std::cout << '\n';
		};

		auto v1 = std::vector<float>{ 1, 2, 3 };
		auto v2 = std::list<short>{ 1, 2, 3, 4 };
		auto v3 = std::to_array({ 1, 2, 3, 4, 5 });

		auto add = [](auto a, auto b, auto c) { return a + b + c; };

		auto sum = std::views::zip_transform(add, v1, v2, v3);

		print("v1:  ", v1);
		print("v2:  ", v2);
		print("v3:  ", v3);
		print("sum: ", sum);
	}
	//*/

	// ranges::adjacent_view, views::adjacent C++23
	// a view consisting of tuples of references to adjacent elements of the adapted view

	// ranges::adjacent_transform_view, views::adjacent_transform C++23
	// a view consisting of tuples of results of application of a transformation function to adjacent elements of the adapted view

	// std::ranges::views::join_with, std::ranges::join_with_view C++23
	// a view consisting of the sequence obtained from flattening a view of ranges, with the delimiter in between elements
	/*
	{
		using namespace std::literals;

		std::vector v{ "This"sv, "is"sv, "a"sv, "test."sv };
		auto joined = v | std::views::join_with(' ');

		for (auto c : joined) std::cout << c;
		std::cout << '\n';
	}
	//*/

	return 0;
}


//
//
/*
{
}
//*/