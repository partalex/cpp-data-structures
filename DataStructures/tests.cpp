#include<iostream>
#include<vector>
#include<array>
#include<string>
#include<numeric>
#include<bitset>
#include<algorithm>

using std::vector;
using std::array;

void print(auto v) {
	for (auto& i : v)
		std::cout << i << " ";
	std::cout << "\n";
}

int main()
{
	vector zeros{ 0, 0, 0 };
	vector ones{ 1, 1, 1 };
	vector iota{ 1, 2, 2, 3 };

	int x = 10;
	int y = 20;
	// find min max

	//vector<int> iota(5); std::iota(iota.begin(), iota.end(), 1); // 1 2 3 4 5

	// accumulate
	/*
	{
		std::cout << "accumulate :" << "\n";
		std::cout << std::accumulate(iota.begin(), iota.end(), 0) << "\n";
		std::cout << "accumulate :" << "\n";
		std::cout << std::accumulate(iota.begin(), iota.end(), 1, std::multiplies()) << "\n";
	}
	//*/

	// transform
	/*
	{
		std::cout << "transform :" << "\n";
		std::transform(iota.begin(), iota.end(), zeros.begin(), [](int t) { return t + 1; });
		print(zeros);
	}
	//*/

	// reduce
	/*
	{
		std::cout << "transform :" << "\n";
		std::cout << std::transform_reduce(ones.begin(), ones.end(), ones.begin(), 0) << "\n";
	}
	//*/

	// inner_product
	/*
	{
		std::cout << "inner_product :" << "\n";
		//std::cout << std::inner_product(iota.begin(), iota.end(), ones.begin(), 0) << "\n"; // 6
		std::cout << std::inner_product(iota.begin(), iota.end(), ones.begin(), 0,
			[](int x, int y) { return x + y; },
			[](int x, int y) { return x * y; }
		) << "\n"; // 6
		//std::cout << std::inner_product(iota.begin(), iota.end(), iota.begin(), 0) << "\n";
	}
	//*/

	return 0;
}

//
/*
{

}
//*/
