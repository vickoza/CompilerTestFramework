#pragma once
#include <vector>
#include <string>
#include <tuple>

enum class compilerSystem
{
	Visual_C,
	Clang_Win,
	Gcc_ix,
	Clang_ix
};

std::tuple<bool, int> compileCodeTest(compilerSystem compTarg, const std::string& code, const std::string& compilerPath, const std::vector<std::string>& setups, const std::vector<std::string>& flags, const std::vector<std::string>& includes);