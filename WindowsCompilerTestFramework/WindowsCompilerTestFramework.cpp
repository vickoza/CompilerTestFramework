// WindowsCompilerTestFramework.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "WindowsDrivers.h"

int main()
{
	//fs::path dir = fs::temp_directory_path();
	/*{
		std::ofstream sampl("sample.cpp");
		sampl << "auto square(int x, int y)\n{\n\treturn x*x;\n}";
	}
	auto retVal = std::system("\"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/VC/Tools/MSVC/14.20.27508/bin/Hostx64/x64/cl.exe\" /experimental:module /std:c++latest /Wall /c sample.cpp > build.result");
	auto count = 0;
	{
		std::ifstream reslt("build.result");
		std::string str(": warning");
		std::string line;
		while (std::getline(reslt, line))
		{
			if (line.find(str) != std::string::npos)
				count++;
		}
	}
	std::cout << count << " warning \n";*/
	std::vector<std::string> flags = { "experimental:module", "std:c++latest", "Wall", "nologo","c" };
	std::vector<std::string> flags2 = { "std=c++2a", "Wextra", "S" };
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
	auto [a, b] = compilerCode(compilerSystem::Visual_C, code, (std::string)"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/VC/Tools/MSVC/14.26.28801/bin/Hostx86/x86/cl.exe", flags);
	std::cout << "VC++ " << std::boolalpha << a << " " << b << " warning\n";
	auto [c, d] = compilerCode(compilerSystem::Clang_Win, code, (std::string)"C:/Program Files/LLVM/bin/clang++", flags2);
	std::cout << "clang++ " << std::boolalpha << c << " " << d << " warning\n";
	auto [e, f] = compilerCode(compilerSystem::Visual_C, code2, (std::string)"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/VC/Tools/MSVC/14.16.27023/bin/Hostx64/x64/cl", flags);
	std::cout << "VC++ " << std::boolalpha << e << " " << f << " warning\n";
	auto [g, h] = compilerCode(compilerSystem::Clang_Win, code2, (std::string)"C:/Program Files (x86)/LLVM/bin/clang++", flags2);
	std::cout << "clang++ " << std::boolalpha << g << " " << h << " warning\n";
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
