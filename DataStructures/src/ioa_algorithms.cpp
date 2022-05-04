#include<algorithm>
#include<bitset>
#include<cassert>
#include<cmath>
#include<iostream>
#include<memory>
#include<numeric>
#include<random>
#include<string>
#include<vector>

namespace partalex {

	uint32_t BinomialCoefficient(const uint32_t n, const uint32_t k) {
		std::vector<unsigned> aSolutions(k);
		aSolutions[0] = n - k + 1;

		for (unsigned i = 1; i < k; ++i)
			aSolutions[i] = aSolutions[i - 1] * (n - k + 1 + i) / (i + 1);

		return aSolutions[k - 1];
	}

	uint32_t bellNUmber(const uint32_t n, const uint32_t k) {
		uint32_t result = 0;
		for (size_t i = 1; i <= n; i++)
			result += BinomialCoefficient(n, i);
		return result;
	}

	/********************************************************************************************/
	namespace combinatorics {
		/********************************************************************************************/
		// iz skupa od n elemenata biramo podskup od k elem ( redosled nije bitan )
		// pun naziv kobminacije k-te klase skupa Xn ( eng: combinations )
		//
		// (5, 3)
		// 1 2 3
		// 1 2 4
		// 1 2 5
		// 1 3 4
		// 1 3 5
		// 1 4 5
		// 2 3 4
		// 2 3 5
		// 2 4 5
		// 3 4 5

		template <typename T>
		uint32_t combination_without_repetition(const uint32_t n, const uint32_t k, const std::vector<T>& reference, std::vector<std::vector<T>>& result) {

			assert(n <= reference.size() && k <= n);

			std::vector<uint32_t> P(k);
			std::iota(P.begin(), P.end(), 1); // 1 2 3 ... n
			std::vector<T> Pt(k);

			int i, j;
			bool b;
			uint32_t ii, index{ 0 };

			uint32_t size = BinomialCoefficient(n, k);
			result.resize(size);

			do
			{
				ii = 0;
				for (const auto& i : P)
					Pt[ii++] = reference[i - 1];
				result[index++] = Pt;

				b = false;
				for (i = k - 1; i >= 0; i--) {
					if (P[i] < n - k + i + 1)
					{
						P[i] ++;

						for (j = i + 1; j < k; j++)
							P[j] = P[j - 1] + 1;

						b = true;
						break;
					}
				}

			} while (b);

			return size;
		}

		/********************************************************************************************/
		// na koliko nacina se moze rasporediti n elemenata na k mesta
		// broj nacina rasporedjivanje je n na stepen k
		// eng: n-tuples
		// formiranje kao broj sa k cifara a cifre su 1..n
		//
		// 1111 1112 ... 111n
		// 1111 1122 ... 112n
		// ...
		// nnn1 nnn2 ... nnnn
		//
		// (2,1)
		// 0
		// 1
		//
		// (2,2)
		// 0 0
		// 0 1
		// 1 0
		// 1 1
		//
		// (3,3)
		// 0 0
		// 0 1
		// 0 2
		// 1 0
		// 1 1
		// 1 2
		// 2 0
		// 2 1
		// 2 2

		template <typename T>
		uint32_t varations_with_repetitition(const uint32_t n, const uint32_t k, const std::vector<T>& reference, std::vector<std::vector<T>>& result) {

			assert(n <= reference.size());

			std::vector<uint32_t> P(k, 0);
			std::vector<T> Pt(k);
			uint32_t size = pow(n, k);
			result.resize(size);

			int q, ii;
			uint32_t index = 0;

			do
			{
				ii = 0;
				for (const auto& i : P)
					Pt[ii++] = reference[i];
				result[index++] = Pt;
				q = k - 1;
				while (q >= 0)
				{
					P[q]++;
					if (P[q] == n)
					{
						P[q] = 0;
						q--;
					}
					else break;
				}
			} while (q >= 0);

			return size;
		}

		/********************************************************************************************/
		// next_permutation(n, k)
		// na koliko nacina je moguce rasporediti n elemanata na n mesta ( bez ponavljanja )
		// broj razlicitih rasporedjivanja je n!
		// eng: permutations ( permutacije skupa Xn )
		// 1 2 3 4 5 start permutation
		//
		// 1 2 3 5 4
		// 1 2 4 3 5
		// 1 2 4 5 3
		// 1 2 5 3 4
		// ... 

		template <typename T>
		uint32_t permutation_without_repetition(std::vector<T>& to_permute, std::vector<std::vector<T>>& result, auto pred = std::less{}) {
			sort(to_permute.begin(), to_permute.end(), pred); // should be given sorted 

			uint32_t number_of_pemrutation = std::tgamma(to_permute.size() + 1);
			result.resize(number_of_pemrutation);
			uint32_t index = 0;
			do {
				result[index++] = to_permute;
			} while (std::next_permutation(to_permute.begin(), to_permute.end(), pred));
			return number_of_pemrutation;
		}

		/********************************************************************************************/

		void print_combinatorics(auto& arr, const std::string_view name = "Combinatorics :") {
			std::cout << name << " :\n";
			for (auto& r : arr) {
				for (auto& i : r)
					std::cout << i << " ";
				std::cout << "\n";
			}
		}

		namespace test {
			void test() {
				std::cout << "podskup moze biti i sam skup ili manji skupa" << "\n";
				std::vector<uint32_t> to_combinate{ 0, 1, 2, 3, 4 };
				std::vector<std::vector<uint32_t>> combinations;
				//combination_without_repetition(4, 3, to_combinate, combinations);
				combination_without_repetition(4, 3, to_combinate, combinations);
				//print_combinatorics(combinations, "\ncombinations(4,3) - svi podskupovi K3 od skupa N4");

				std::vector<uint32_t> to_varitation{ 0, 1, 2, 3 };
				std::vector<std::vector<uint32_t>> variations;
				varations_with_repetitition(2, 4, to_varitation, variations);
				print_combinatorics(variations, "\nvariations(3,3) - uredjene n-torke(K2) skupa N3");

				std::vector to_permute{ 0, 1, 2 };
				std::vector<std::vector<int>> permutations;
				permutation_without_repetition(to_permute, permutations, std::less{});
				//print_combinatorics(permutations, "\npermutations(3) - uredjene n-torke(N3) skupa N3");
			}
		}

	}

	/********************************************************************************************/
	namespace not_useful {

		/********************************************************************************************/
		// particija ( podela / razbijanje) prirodnog broja n je niz pozitivnih prirodnih brojeva

		template <typename T>
		bool next_permutation(std::vector<T>& p, const uint32_t n) {
			int k, i;
			int q = 0;

			if (p[0] == 0) // thre first one
			{
				p[0] = n;
				return true;
			}
			else // finding k
			{
				for (i = 0; i < n; i++)
					if (p[i] != 0)
						k = i;
					else break;
			}

			while (k >= 0 && p[k] == 1) {
				q++;
				k--;
			}

			if (k < 0)
				return false;

			p[k] --;
			q++;

			while (q > p[k])
			{
				p[k + 1] = p[k];
				q = q - p[k];
				k++;
			}

			p[k + 1] = q;
			k++;

			for (i = k + 1; i < n; i++)
				p[i] = 0;

			return true;
		}

		template <typename T>
		void driver_next_partition(const uint32_t n, std::vector<std::vector<T>>& result) {
			std::vector<T> P(n, 0);
			result.reserve(n); // should be miniumum space for result
			uint32_t index = 0;
			while (next_permutation(P, n))
				result.push_back(P);
		}

		/********************************************************************************************/
		// particije skupa RGS
		// s = { 1, 2, 3, 4 } started set 
		//
		// s = { 1, 2, 3, 4 }
		// s = { 1, 2, 3 }, { 4 }
		// s = { 1, 2, 4 }, { 3 }
		// s = { 1, 2 }, { 3, 4 }
		// s = { 1, 2 }, { 3 } , { 4 }
		// ...
		// s = { 1 }, { 2 }, { 3 }, { 4 }

		template <typename T>
		bool next_partition_of_set(std::vector<T>& a, const int n) {
			//const int n = a.size();
			std::vector<T> b(n);

			int j;
			for (j = 0; j < n; j++)
				b[j] = j == 0 ? 0 : std::max(b[j - 1], a[j - 1] + 1); // sta je ovo 

			for (j = n - 1; j >= 0; j--)
			{
				if (a[j] < b[j])
				{
					a[j]++;
					break;
				}
				else
					a[j] = 0;
			}
			if (j == -1)
				return false;
			return true;
		}

		template <typename T>
		uint32_t driver_next_partition_of_set(uint32_t const k, uint32_t const n, std::vector<T>& set, std::vector<std::vector<T>>& result) {
			assert(n <= set.size() && k <= n);

			std::vector<T> partition(n, 0);

			uint32_t number_of_partition = bellNUmber(n, k);
			result.reserve(number_of_partition); // should be miniumum space for result

			int i;
			do
			{
				result.push_back(partition);
				for (i = 0; i < n; i++)	std::cout << partition[i] << " ";
				std::cout << "\n";
			} while (next_partition_of_set(partition, n));

			return number_of_partition;
		}

		/********************************************************************************************/
		// particija skupa na tacno m podskupova
			// saamo uzeti pretnodni algoritam i uzeti one skupove koji potrvrdjuju zahetv m = 2
		// m = 2 
		// s = { 1, 2, 3, 4 } started set 
		//
		// s = { 1, 2, 3 }, { 4 }
		// s = { 1, 2, 4 }, { 3 }
		// s = { 1, 2 }, { 3, 4 }
		// ...
		// s = { 1 }, { 2, 3, 4 }

		/********************************************************************************************/
		// pretrazivanje po stablima grafa: kompletan graf
			// izmedju svakoh para cvorova postoji grdna ( svi cvorovi su povezani )
		//
		// kodovanje stabla u sekvence
		// dekodovanje sekvence u stabla

		void sequence_to_spanning_tree(int* P, int len, int* T)
		{
			int i, j, q = 0;
			int n = len + 2;
			int* V = new int[n];

			memset(V, 0, sizeof(int) * n);

			for (i = 0; i < len; i++)
				V[P[i] - 1] += 1;

			for (i = 0; i < len; i++)
				for (j = 0; j < n; j++)
					if (V[j] == 0)
					{
						V[j] = -1;
						T[q++] = j + 1;
						T[q++] = P[i];
						V[P[i] - 1] --;
						break;
					}
			j = 0;
			for (i = 0; i < n; i++)
			{
				if (V[i] == 0 && j == 0)
				{
					T[q++] = i + 1;
					j++;
				}
				else if (V[i] == 0 && j == 1)
				{
					T[q++] = i + 1;
					break;
				}
			}
			delete[] V;
		}

		void test_sequence_to_spanning_tree() {
			int P[] = { 1, 2, 2 };
			int len = sizeof(P) / sizeof(int);

			int* T = new int[2 * (len + 1)];
			sequence_to_spanning_tree(P, len, T);

			for (int i = 0; i < 2 * (len + 1); i++)
			{
				std::cout << " " << T[i];
				if ((i + 1) % 2 == 0 && i < 2 * len)
					std::cout << "  - ";
			}
			std::cout << "\n";
			delete[]T;
		}

		/********************************************************************************************/


		void varations_with_repetitition(int n, int k)
		{
			int q;
			int* P = new int[k];
			memset(P, 0, sizeof(int) * k);

			size_t size = pow(n, k);

			do
			{
				for (size_t i = 0; i < k; i++)
					std::cout << P[i] << " ";
				std::cout << "\n";

				q = k - 1;
				while (q >= 0)
				{
					P[q]++;
					if (P[q] == n)
					{
						P[q] = 0;
						q--;
					}
					else break;
				}
			} while (q >= 0);
			delete[] P;
		}

		uint32_t permutation_without_repetition(const uint32_t n) {

			uint32_t* arr = new uint32_t[n];
			arr[0] = 0;
			for (size_t i = 1; i < n; i++)
				arr[i] = arr[i - 1] + 1;

			auto print = [&]() {
				for (size_t i = 0; i < n; i++)
					std::cout << arr[i] << " ";
				std::cout << "\n";
			};

			do {
				print();
			} while (std::next_permutation(arr, arr + n));

			std::cout << "\n";
			std::string s = "aba";
			std::sort(s.begin(), s.end());
			do {
				std::cout << s << '\n';
			} while (std::next_permutation(s.begin(), s.end()));
			delete[] arr;

			return std::tgamma(n + 1);
		};

		bool next_permutation(int* p, int n) {
			int k, i;

			if (p[0] == 0) // thre first one
			{
				p[0] = n;
				return true;
			}
			else // finding k
			{
				for (i = 0; i < n; i++)
					if (p[i] != 0)
						k = i;
					else break;
			}

			int q = 0;
			while (k >= 0 && p[k] == 1) {
				q++;
				k--;
			}

			if (k < 0)
				return false;

			p[k] --;
			q++;

			while (q > p[k])
			{
				p[k + 1] = p[k];
				q = q - p[k];
				k++;
			}

			p[k + 1] = q;
			k++;

			for (i = k + 1; i < n; i++)
				p[i] = 0;

			return true;
		}

		void driver_next_partition() {

			int n = 7;
			int* p = new int[n];
			memset(p, 0, sizeof(int) * n);

			while (next_permutation(p, n))
			{
				// print current partition
				for (size_t i = 0; i < n; i++)
					std::cout << p[i] << " ";
				std::cout << "\n";
			}
			delete[] p;
		}

		bool next_partition_of_set(int* a, int n)
		{
			int j;
			int* b = new int[n];

			for (j = 0; j < n; j++)
				b[j] = j == 0 ? 0 : std::max(b[j - 1], a[j - 1] + 1);

			for (j = n - 1; j >= 0; j--)
			{
				if (a[j] < b[j])
				{
					a[j]++;
					break;
				}
				else
					a[j] = 0;
			}
			if (j == -1)
				return false;
			delete[] b;
			return true;
		}

		uint32_t combination_without_repetition(const uint32_t n, const uint32_t k) {
			assert(k <= n);

			int i, j;
			bool b;
			uint32_t* P = new uint32_t[k];

			for (i = 0; i < k; i++)
				P[i] = i + 1;

			do
			{
				for (i = 0; i < k; i++)
					std::cout << P[i] << " ";
				std::cout << "\n";

				b = false;
				for (i = k - 1; i >= 0; i--) {
					if (P[i] < n - k + i + 1)
					{
						P[i] ++;

						for (j = i + 1; j < k; j++)
							P[j] = P[j - 1] + 1;

						b = true;
						break;
					}
				}

			} while (b);

			if (P != nullptr)
				delete[] P;
			return BinomialCoefficient(n, k);
		}

		uint32_t driver_next_partition_of_set()
		{
			int n = 4;
			int* a = new int[n];
			int i;
			uint32_t number_of_partition = bellNUmber(n, n);
			memset(a, 0, sizeof(int) * n);
			do
			{
				for (i = 0; i < n; i++)
					std::cout << a[i] << " ";
				std::cout << "\n";
			} while (next_partition_of_set(a, n));

			delete[] a;

			return number_of_partition;
		}

		// random nubmers

		int random_int(int a, int b) {
			return rand() % (b - a + 1) + a;
		}

		float random_float(float a, float b) {
			return (float)rand() / (float)RAND_MAX * (b - a) + a;
		}

		// c++1 radnom
		void c11_radnom() {
			std::random_device rd;
			std::mt19937 mt(rd());

			std::uniform_real_distribution<double> radnom_float(1.0, 10.0);
			for (size_t i = 0; i < 16; i++)
				std::cout << radnom_float(mt) << "\n";

			std::uniform_int_distribution<int> radnom_int(1, 5);
			for (size_t i = 0; i < 16; i++)
				std::cout << radnom_int(mt) << "\n";
		}
		/********************************************************************************************/
		// varijacija sa ponavaljanjem
			// za svako od k mesta gerise se jedan slucajan ceo broj iz skupa od n elemenata

		void driver_radnom_variation()
		{
			srand((unsigned int)time(NULL));

			int n = 10;
			int k = 4;
			int s = 15;
			int* r = new int[k];

			for (size_t i = 0; i < s; i++) {
				for (size_t j = 0; j < k; j++) {
					r[j] = random_int(0, n - 1);
					std::cout << r[j] << " ";
				}
				std::cout << "\n";
			}
			delete[] r;
		}

		void driver_radnom_vector()
		{
			srand((unsigned int)time(NULL));

			double xmin = -1.0;
			double xmax = 1.0;
			int k = 4;
			int s = 15;

			double* r = new double[k];

			for (size_t i = 0; i < s; i++) {
				for (size_t j = 0; j < k; j++) {
					r[j] = random_float(xmin, xmax);
					std::cout << r[j] << " ";
				}
				std::cout << "\n";
			}
			delete[] r;
		}

		/********************************************************************************************/
		// slucajno generisna kombinacija bez ponavljanja
			// iz skupa od od n elemenata slucajno izabrati k razlicitih elemanta
			// ponavaljanje nije dozvoljeno
		// ne kontam sta je ovo 

		void random_combinataion(int n, int k, int* P)
		{
			if (k > n) return;

			int i, j, r, c;
			int* Q = new int[n];

			memset(Q, 0, sizeof(int) * n);

			for (i = 0; i < k; i++) {
				r = random_int(0, n - 1 - i);
				c = 0;
				for (j = 0; j < n; j++)
					if (Q[j] == 0)
					{
						if (c == r)
						{
							Q[j] ++;
							break;
						}
						c++;
					}
			}
			c = 0;
			for (i = 0; i < n; i++)
				if (Q[i] == 1) {
					P[c] = i + 1;
					c++;
				}
			delete[] Q;
		}

		void driver_radnom_combination() {
			int n = 5;
			int k = 3;
			int* P = new int[k];

			for (int i = 0; i < 100; i++)
			{
				random_combinataion(n, k, P);
				for (int j = 0; j < k; j++)
					std::cout << P[j] << " ";
				std::cout << "\n";
			}
			delete[] P;
		}

		/********************************************************************************************/
		// slucajno generisana permutacija
			// iz niza elemenata skucajno se biraju njegovi elem
				// nema ponavljanja

		void random_permutation(int n, int* p)
		{
			int i, j, s;
			for (i = n - 1; i > 0; i--)
			{
				j = random_int(0, i);
				if (i != j)
				{
					s = p[i];
					p[i] = p[j];
					p[j] = s;
				}
			}
		}

		void driver_random_permutation()
		{
			int n = 3;
			int* p = new int[n];
			int* s = new int[n];
			int T = 1000;

			for (size_t i = 0; i < n; i++)
			{
				p[i] = i + 1;
				s[i] = 0;
			}

			for (size_t i = 0; i < T; i++)
			{
				random_permutation(n, p);

				for (int j = 0; j < n; j++)
					std::cout << p[j] << " ";
				std::cout << "\n";

				s[p[0] - 1]++;
			}

			for (size_t i = 0; i < n; i++)
				std::cout << s[i] * 1.0 / T << " ";

			delete[] p;
			delete[] s;
		}
	}

	/********************************************************************************************/
	// slucajno generisane particije i stabla grafa
	// 4to predavanje, 6ti slajd
	/********************************************************************************************/

}

namespace test {
	class Test {
	public:
		int a;
		// overlaod operator<
		bool operator<(const Test& t) const {
			return a < t.a;
		}
		// overlaod operator= 
		Test& operator=(const Test& t) {
			a = t.a;
			return *this;
		}
		Test() {
			a = 0;
			std::cout << "ctor Test" << "\n";
		};
		Test(int a) {
			this->a = a;
			std::cout << "ctor Test(" << a << ")" << "\n";
		}
		Test(const Test& t) {
			std::cout << "copy ctor Test" << "\n";
		}
		Test(const Test&& t) {
			std::cout << "move ctor Test" << "\n";
		}
		~Test() {
			std::cout << "dtor Test" << "\n";
		}
		friend std::ostream& operator<<(std::ostream& os, const Test& t) {
			os << "Test.a = " << t.a << "\n";
			return os;
		}
	};
}

int main()
{
	partalex::combinatorics::test::test();
	return 0;
}