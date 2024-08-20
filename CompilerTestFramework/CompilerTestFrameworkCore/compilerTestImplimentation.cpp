#include "compilerTestInterface.h"
#include <iostream>
#include <fstream>
//#include <filesystem>
#include <cstdlib>
//#define BEGIN_BLOCK(name)***V*** auto name = R"( V )";
enum class OSEnviment
{
	windows,
	android,
	linux,
	bsd,
	hpux,
	aix,
	iOS,
	mac,
	solaris,
	unknown
};
#if defined(_WIN32)
constexpr auto osTarger = OSEnviment::windows;
#elif defined(_WIN64)
constexpr auto osTarger = OSEnviment::windows;
#elif defined(__CYGWIN__) && !defined(_WIN32)
constexpr auto osTarger = OSEnviment::windows;
#elif defined(__ANDROID__)
constexpr auto osTarger = OSEnviment::android
#elif defined(__linux__)
constexpr auto osTarger = OSEnviment::linux;
#elif defined(__unix__) || !defined(__APPLE__) && defined(__MACH__)
constexpr auto osTarger = OSEnviment::bsd;
#elif defined(__hpux)
constexpr auto osTarger = OSEnviment::hpux;
#elif defined(_AIX)
constexpr auto osTarger = OSEnviment::aix;
#elif defined(__APPLE__) && defined(__MACH__) // Apple OSX and iOS (Darwin)
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR == 1
constexpr auto osTarger = OSEnviment::ios;
#elif TARGET_OS_IPHONE == 1
constexpr auto osTarger = OSEnviment::ios;
#elif TARGET_OS_MAC == 1
constexpr auto osTarger = OSEnviment::mac;
#endif
#elif defined(__sun) && defined(__SVR4)
constexpr auto osTarger = OSEnviment::solaris;
#else
constexpr auto osTarger = OSEnviment::unknown;
#endif
std::tuple<bool, int> compileCodeTest(compilerSystem compTarg, const std::string& code, const std::string& compilerPath, const std::vector<std::string>& setups, const std::vector<std::string>& flags, const std::vector<std::string>& includes)
{
	{
		std::ofstream sampl("sample.cpp");
		sampl << code;
	}
	auto compileCall = (std::string)"";
	for (const auto& setup : setups)
	{
		compileCall += setup + " && ";
	}
	compileCall += (std::string)"\"" + compilerPath + (std::string)"\"";
	if constexpr(osTarger == OSEnviment::windows)
	{ 
		if (compTarg == compilerSystem::Visual_C)
		{
			//compileCall += (std::string)" /c";
			for (const auto& flag : flags)
			{
				compileCall += (std::string)" /" + flag;
			}
			for (const auto& includeFile : includes)
			{
				compileCall += (std::string)" /I " + includeFile;
			}
		}
		else
		{
			for (const auto& flag : flags)
			{
				compileCall += (std::string)" -" + flag;
			}
			for (const auto& includeFile : includes)
			{
				compileCall += (std::string)" -I" + includeFile;
			}
		}
	}
	else if constexpr (osTarger == OSEnviment::linux)
	{
		for (const auto& flag : flags)
		{
			compileCall += (std::string)" -" + flag;
		}
		for (const auto& includeFile : includes)
		{
			compileCall += (std::string)" -I" + includeFile;
		}
	}
	else
	{
		for (const auto& flag : flags)
		{
			compileCall += (std::string)" -" + flag;
		}
		for (const auto& includeFile : includes)
		{
			compileCall += (std::string)" -I" + includeFile;
		}
	}
	compileCall += (std::string)" sample.cpp > build.result 2>&1";

	std::cout.flush();
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

	//fs::path dir = fs::temp_directory_path();
	std::remove("sample.cpp");
	std::remove("sample.s");
	std::remove("sample.obj");
	std::remove("build.result");

	if (retVal != 0)
		return std::make_tuple(false, count);
	else
		return std::make_tuple(true, count);
}
