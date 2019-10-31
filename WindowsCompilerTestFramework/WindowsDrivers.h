#pragma once
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <tuple>
#include <cstdlib>
//#define BEGIN_BLOCK(name)***V*** auto name = R"( V )";
enum class compilerSystem
{
	Visual_C,
	Clang_Win
};
namespace fs = std::filesystem;
auto compilerCode(compilerSystem compTarg, const std::string& code, const std::string& compilerPath, const std::vector<std::string>& flags)
{
	{
		std::ofstream sampl("sample.cpp");
		sampl << code;
	}
	auto compileCall = (std::string)"";
	if (compTarg == compilerSystem::Visual_C)
		compileCall += (std::string)"C:/Program Files (x86)/Microsoft Visual Studio/2019/Preview/Common7/Tools/VsDevCmd.bat\r\n";
	compileCall += (std::string)"\"" + compilerPath + (std::string)"\"";
	for (const auto& flag : flags)
	{
		compileCall += (std::string)" -" + flag;
	}
	compileCall += (std::string)" sample.cpp > build.result 2>&1";
	auto retVal = std::system(compileCall.c_str());
	auto count = 0;
	{
		std::ifstream reslt("build.result");
		std::string str;
		if (compTarg == compilerSystem::Visual_C)
			str = (std::string)(": warning");
		else
			str = ("warning:");
		std::string line;
		while (std::getline(reslt, line))
		{
			if (line.find(str) != std::string::npos)
				count++;
		}
	}
	if (retVal != 0)
		return std::make_tuple(false, count);
	else
		return std::make_tuple(true, count);
}