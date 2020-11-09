// WindowsCompilerTestFramework.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "WindowsDrivers.h"

int main()
{
	std::vector<std::string> setup = { "set __VSCMD_PREINIT_INCLUDE=\"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/VC/Tools/MSVC/14.28.29333/include\";\"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/SDK/ScopeCppSDK/vc15/SDK/include/ucrt\";\"C:/Program Files (x86)/Windows Kits/10/Include/10.0.19041.0/ucrt/stddef.h\"" };
	std::vector<std::string> setup2 = {  };
	std::vector<std::string> flags = { "std:c++latest", "W4", "nologo", "c", "EHsc" };
	std::vector<std::string> flags2 = { "std=c++20", "Wextra", "S" };
	std::vector<std::string> includes = { "\"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/VC/Tools/MSVC/14.28.29333/include\"","\"C:/Program Files (x86)/Windows Kits/10/Include/10.0.19041.0/ucrt\"", "\"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/SDK/ScopeCppSDK/vc15/VC/include\"","\"C:/Program Files (x86)/Windows Kits/10/Include/10.0.19041.0/ucrt\"", "\"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/SDK/ScopeCppSDK/vc15/SDK/include/ucrt\"" };
	std::vector<std::string> includes2 = {  };
	std::vector<std::string> includes3 = { "\"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/VC/Tools/MSVC/14.28.29333/include\"","\"C:/Program Files (x86)/Windows Kits/10/Include/10.0.19041.0/ucrt\"", "\"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/SDK/ScopeCppSDK/vc15/VC/include\"", "\"C:/Program Fils (x86)/Microsoft Visual Studio/2019/Preview/SDK/ScopeCppSDK/vc15/SDK/include/ucrt\"", "C:/Users/Vishal/source/repos/timeContainer/timeContainer" };
	std::vector<std::string> includes4 = { "C:/Users/Vishal/source/repos/timeContainer/timeContainer" };

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
#include <string>

int main()
{
	data_ledger<std::string> leg("0");
	return 0;
}
)";

auto code6 =
R"(
#include <data_ledger.h>
#include <complex>

int main()
{
	data_ledger<std::complex<double>> leg(0.0);
	return 0;
}
)";

auto code7 =
R"(
#include <data_ledger.h>
#include <string>

int main()
{
	data_ledger<std::string> leg("0");
	return 0;
}
)";

auto code8 =
R"(
#include <data_ledger.h>
#include <vector>

int main()
{
	data_ledger<int, std::chrono::steady_clock, std::chrono::time_point<std::chrono::steady_clock>, std::vector<std::pair<int, std::chrono::time_point<std::chrono::steady_clock>>>> leg(0);
	return 0;
}
)";

auto code9 =
R"(
#include <data_ledger.h>
#include <map>

int main()
{
	data_ledger<int, std::chrono::steady_clock, std::chrono::time_point<std::chrono::steady_clock>, std::map<int, std::chrono::time_point<std::chrono::steady_clock>>> leg(0);
	return 0;
}
)";

	std::cout << "Code 1\n";
	auto [a, b] = compilerCode(compilerSystem::Visual_C, code, (std::string)"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/VC/Tools/MSVC/14.28.29333/bin/Hostx86/x86/cl", setup, flags, includes);
	std::cout << "VC++ " << std::boolalpha << a << " " << b << " warning\n";
	auto [c, d] = compilerCode(compilerSystem::Clang_Win, code, (std::string)"C:/Program Files/LLVM/bin/clang++", setup2, flags2, includes2);
	std::cout << "clang++ " << std::boolalpha << c << " " << d << " warning\n";
	std::cout << "\nCode 2\n";
	auto [e, f] = compilerCode(compilerSystem::Visual_C, code2, (std::string)"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/VC/Tools/MSVC/14.28.29333/bin/Hostx86/x86/cl", setup, flags, includes);
	std::cout << "VC++ " << std::boolalpha << e << " " << f << " warning\n";
	auto [g, h] = compilerCode(compilerSystem::Clang_Win, code2, (std::string)"C:/Program Files/LLVM/bin/clang++", setup2, flags2, includes2);
	std::cout << "clang++ " << std::boolalpha << g << " " << h << " warning\n";
	std::cout << "\nCode 3\n";
	auto [i, j] = compilerCode(compilerSystem::Visual_C, code3, (std::string)"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/VC/Tools/MSVC/14.28.29333/bin/Hostx64/x64/cl", setup, flags, includes);
	std::cout << "VC++ " << std::boolalpha << i << " " << j << " warning\n";
	auto [k, l] = compilerCode(compilerSystem::Clang_Win, code3, (std::string)"C:/Program Files/LLVM/bin/clang++", setup2, flags2, includes2);
	std::cout << "clang++ " << std::boolalpha << k << " " << l << " warning\n";
	std::cout << "\nCode 4\n";
	auto [m, n] = compilerCode(compilerSystem::Visual_C, code4, (std::string)"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/VC/Tools/MSVC/14.28.29333/bin/Hostx64/x64/cl", setup, flags, includes3);
	std::cout << "VC++ " << std::boolalpha << m << " " << n << " warning\n";
	auto [o, p] = compilerCode(compilerSystem::Clang_Win, code4, (std::string)"C:/Program Files/LLVM/bin/clang++", setup2, flags2, includes4);
	std::cout << "clang++ " << std::boolalpha << o << " " << p << " warning\n";
	std::cout << "\nCode 5\n";
	auto [q, r] = compilerCode(compilerSystem::Visual_C, code5, (std::string)"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/VC/Tools/MSVC/14.28.29333/bin/Hostx64/x64/cl", setup, flags, includes3);
	std::cout << "VC++ " << std::boolalpha << q << " " << r << " warning\n";
	auto [s, t] = compilerCode(compilerSystem::Clang_Win, code5, (std::string)"C:/Program Files/LLVM/bin/clang++", setup2, flags2, includes4);
	std::cout << "clang++ " << std::boolalpha << s << " " << t << " warning\n";
	std::cout << "\nCode 6\n";
	auto [u, v] = compilerCode(compilerSystem::Visual_C, code6, (std::string)"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/VC/Tools/MSVC/14.28.29333/bin/Hostx64/x64/cl", setup, flags, includes3);
	std::cout << "VC++ " << std::boolalpha << u << " " << v << " warning\n";
	auto [w, x] = compilerCode(compilerSystem::Clang_Win, code6, (std::string)"C:/Program Files/LLVM/bin/clang++", setup2, flags2, includes4);
	std::cout << "clang++ " << std::boolalpha << w << " " << x << " warning\n";
	std::cout << "\nCode 7\n";
	auto [y, z] = compilerCode(compilerSystem::Visual_C, code7, (std::string)"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/VC/Tools/MSVC/14.28.29333/bin/Hostx64/x64/cl", setup, flags, includes3);
	std::cout << "VC++ " << std::boolalpha << y << " " << z << " warning\n";
	auto [a1, b1] = compilerCode(compilerSystem::Clang_Win, code7, (std::string)"C:/Program Files/LLVM/bin/clang++", setup2, flags2, includes4);
	std::cout << "clang++ " << std::boolalpha << a1 << " " << b1 << " warning\n";
	std::cout << "\nCode 8\n";
	auto [c1, d1] = compilerCode(compilerSystem::Visual_C, code8, (std::string)"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/VC/Tools/MSVC/14.28.29333/bin/Hostx64/x64/cl", setup, flags, includes3);
	std::cout << "VC++ " << std::boolalpha << c1 << " " << d1 << " warning\n";
	auto [e1, f1] = compilerCode(compilerSystem::Clang_Win, code8, (std::string)"C:/Program Files/LLVM/bin/clang++", setup2, flags2, includes4);
	std::cout << "clang++ " << std::boolalpha << e1 << " " << f1 << " warning\n";
	std::cout << "\nCode 9\n";
	auto [g1, h1] = compilerCode(compilerSystem::Visual_C, code9, (std::string)"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/VC/Tools/MSVC/14.28.29333/bin/Hostx64/x64/cl", setup, flags, includes3);
	std::cout << "VC++ " << std::boolalpha << g1 << " " << h1 << " warning\n";
	auto [i1, j1] = compilerCode(compilerSystem::Clang_Win, code9, (std::string)"C:/Program Files/LLVM/bin/clang++", setup2, flags2, includes4);
	std::cout << "clang++ " << std::boolalpha << i1 << " " << j1 << " warning\n";
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
