# CompilerTestFramework
A framework for testing code if it compile on different compilers

## Introduction

This framework for testing where code compile using unit testing framework and how many warning compiled code generates. This was primarily designed for template library writers to test if their library will or will not compile with different templete agruments. However compiler writer can use this to track regestion in compiler build. This only compiles and does not link


## Requirements

a C++ compiler including Clang and MSVC++, This depends on C++ 17 (for costexpr if) to build but can use any C++ compiler to run on clang, gcc, and MSVC++. I have tested it with Visual Studios 2019 and Visual Studion 2022. This is defined in the function in the header compilerTestInterface.h. Implimentation move to compilerTestInterface.cpp . Plans to support as well Linux, FreeBSD and other OS are in the works. Intel compiler and other compiler can be added if requested.

## Instructions

One simply uses the function compilerCode to test the code. This will return a tuple with the first element telling if the code compiles and the second element telling the warning count. The input argument for compilerCode are:

1. compilerTarget-this is the compiler that we are using to test the code under this a C++ 11 enum class with two values	Visual_C and	Clang_Win
2. code-test is the code we want to set if is build of not. This can just be a snippet and a full single file C++ program in an std::string
3. compilerPath-This is the path the compiler should be found. I have currently included the compiler call in this but may remove this in later iteration and use the enum to tell the compiler target 
4. flags-This is the a vector of strings the tell about the flags for the compile.

## Example

An example for windows usage is found in the WindowsCompilerTestFramework.cpp the path is for my computer so change in to fit you computer

## LinuxCompilerTestFrameworkTest 

An example using Linux remote tool and is tested using WSL 
