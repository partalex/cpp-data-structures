#include <iostream>
#include <utility>
#include <vector>
#include <iterator>

void f() { std::cout << "f()"; }

int main()
{
	{
		using namespace std;
		int a = 3;
		int b = 5;
		b = std::exchange(a, b);
		cout << a << ' ' << b << endl;
	}

	std::vector<int> v;
	std::exchange(v, { 1,2,3,4 });

	std::copy(begin(v), end(v), std::ostream_iterator<int>(std::cout, ", "));

	std::cout << "\n\n";

	void (*fun)();

	// the default value of template parameter also makes possible to use a
	// normal function as second argument. The expression below is equivalent to
	// std::exchange(fun, static_cast<void(*)()>(f))
	std::exchange(fun, f);
	fun();

	std::cout << "\n\nFibonacci sequence: ";
	for (int a{ 0 }, b{ 1 }; a < 100; a = std::exchange(b, a + b))
		std::cout << a << ", ";
	std::cout << "...\n";
}