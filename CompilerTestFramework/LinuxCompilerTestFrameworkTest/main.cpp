#include "compilerTestInterface.h"
#include <iostream>


int main()
{
	std::vector<std::string> setup = {  };
	std::vector<std::string> flags = { "std=c++20", "Wextra", "S" };
	std::vector<std::string> includes = {  };

	auto code =
		R"(
[[deprecated]]
auto square(int x, int y)
{
	return x*x;
}

int main()
{
	square(9,2);
	return 0;
}
)";
	auto code2 =
		R"(
#include <type_traits>
template<typename T>
auto square(T x)
{
	static_assert(std::is_floating_point<T>::value || std::is_integral<T>::value,  "requires numberic type");
	return x*x;
}

int main()
{
	square(2);
	return 0;
}
)";

	auto code3 =
		R"(
#include <type_traits>
#include <string>
template<typename T>
auto square(T x)
{
	static_assert(std::is_floating_point<T>::value || std::is_integral<T>::value,  "requires numberic type");
	return x*x;
}

int main()
{
	std::string str1("2");
	square(str1);
	return 0;
}
)";

	std::cout << "Code 1\n";
	auto [a, b] = compileCodeTest(compilerSystem::Gcc_ix, code, (std::string)"g++", setup, flags, includes);
	std::cout << "g++ " << std::boolalpha << a << " " << b << " warning\n";
	auto [c, d] = compileCodeTest(compilerSystem::Clang_ix, code, (std::string)"clang++", setup, flags, includes);
	std::cout << "clang++ " << std::boolalpha << c << " " << d << " warning\n";
	std::cout << "\nCode 2\n";
	auto [e, f] = compileCodeTest(compilerSystem::Gcc_ix, code2, (std::string)"g++", setup, flags, includes);
	std::cout << "g++ " << std::boolalpha << e << " " << f << " warning\n";
	auto [g, h] = compileCodeTest(compilerSystem::Clang_ix, code2, (std::string)"clang++", setup, flags, includes);
	std::cout << "clang++ " << std::boolalpha << g << " " << h << " warning\n";
	std::cout << "\nCode 3\n";
	auto [i, j] = compileCodeTest(compilerSystem::Gcc_ix, code3, (std::string)"g++", setup, flags, includes);
	std::cout << "g++ " << std::boolalpha << i << " " << j << " warning\n";
	auto [k, l] = compileCodeTest(compilerSystem::Clang_ix, code3, (std::string)"clang++", setup, flags, includes);
	std::cout << "clang++ " << std::boolalpha << k << " " << l << " warning\n";
	return 0;
}