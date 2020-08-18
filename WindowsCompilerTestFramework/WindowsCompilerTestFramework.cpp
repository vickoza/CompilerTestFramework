// WindowsCompilerTestFramework.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "WindowsDrivers.h"

int main()
{
	std::vector<std::string> setup = { "set __VSCMD_PREINIT_INCLUDE=\"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/VC/Tools/MSVC/14.28.29115/include\";\"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/SDK/ScopeCppSDK/vc15/SDK/include/ucrt\"" };
	std::vector<std::string> setup2 = {  };
	std::vector<std::string> flags = { "experimental:module", "std:c++latest", "Wall", "nologo","c" };
	std::vector<std::string> flags2 = { "std=c++2a", "Wextra", "S" };
	std::vector<std::string> includes = { "\"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/SDK/ScopeCppSDK/vc15/VC/include\"", "\"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/SDK/ScopeCppSDK/vc15/SDK/include/ucrt\"" };
	std::vector<std::string> includes2 = {  };
	std::vector<std::string> includes3 = { "\"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/SDK/ScopeCppSDK/vc15/VC/include\"", "\"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/SDK/ScopeCppSDK/vc15/SDK/include/ucrt\"", "C:/Users/Vishal/source/repos/timeContainer/timeContainer" };
	std::vector<std::string> includes4 = { "C:/Users/Vishal/source/repos/timeContainer/timeContainer" };
	auto code =
R"(auto square(int x, int y)
{
	return x*x;
})";
	auto code2 =
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
	square(2);
	//square(str1);
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
	square(2);
	square(str1);
	return 0;
}
)";

auto code4 =
R"(
#include <data_ledger_old.h>

int main()
{
	data_ledger<int> leg(0);
	return 0;
}
)";
auto code5 =
R"(
#include <data_ledger_old.h>

int main()
{
	data_ledger<std::string> leg("0");
	return 0;
}
)";

	auto [a, b] = compilerCode(compilerSystem::Visual_C, code, (std::string)"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/VC/Tools/MSVC/14.28.29115/bin/Hostx86/x86/cl", setup, flags, includes);
	std::cout << "VC++ " << std::boolalpha << a << " " << b << " warning\n";
	auto [c, d] = compilerCode(compilerSystem::Clang_Win, code, (std::string)"C:/Program Files/LLVM/bin/clang++", setup2, flags2, includes2);
	std::cout << "clang++ " << std::boolalpha << c << " " << d << " warning\n";
	auto [e, f] = compilerCode(compilerSystem::Visual_C, code2, (std::string)"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/VC/Tools/MSVC/14.28.29115/bin/Hostx64/x64/cl", setup, flags, includes);
	std::cout << "VC++ " << std::boolalpha << e << " " << f << " warning\n";
	auto [g, h] = compilerCode(compilerSystem::Clang_Win, code2, (std::string)"C:/Program Files/LLVM/bin/clang++", setup2, flags2, includes2);
	std::cout << "clang++ " << std::boolalpha << g << " " << h << " warning\n";
	auto [i, j] = compilerCode(compilerSystem::Visual_C, code3, (std::string)"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/VC/Tools/MSVC/14.28.29115/bin/Hostx64/x64/cl", setup, flags, includes);
	std::cout << "VC++ " << std::boolalpha << i << " " << j << " warning\n";
	auto [k, l] = compilerCode(compilerSystem::Clang_Win, code3, (std::string)"C:/Program Files/LLVM/bin/clang++", setup2, flags2, includes2);
	std::cout << "clang++ " << std::boolalpha << k << " " << l << " warning\n";
	auto [m, n] = compilerCode(compilerSystem::Visual_C, code4, (std::string)"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/VC/Tools/MSVC/14.28.29115/bin/Hostx64/x64/cl", setup, flags, includes3);
	std::cout << "VC++ " << std::boolalpha << m << " " << n << " warning\n";
	auto [o, p] = compilerCode(compilerSystem::Clang_Win, code4, (std::string)"C:/Program Files/LLVM/bin/clang++", setup2, flags2, includes4);
	std::cout << "clang++ " << std::boolalpha << o << " " << p << " warning\n";
	auto [q, r] = compilerCode(compilerSystem::Visual_C, code5, (std::string)"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/VC/Tools/MSVC/14.28.29115/bin/Hostx64/x64/cl", setup, flags, includes3);
	std::cout << "VC++ " << std::boolalpha << q << " " << r << " warning\n";
	auto [s, t] = compilerCode(compilerSystem::Clang_Win, code5, (std::string)"C:/Program Files/LLVM/bin/clang++", setup2, flags2, includes4);
	std::cout << "clang++ " << std::boolalpha << s << " " << t << " warning\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
