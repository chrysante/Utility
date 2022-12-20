#pragma once

#include <functional>
#include <vector>
#include <string>
#include <filesystem>

namespace CodeGen {

	struct CodeGenerator {
		std::function<std::string()> function;
		std::filesystem::path outpath;
	};
	
	std::vector<CodeGenerator>& _registeredGenerators();

}

#define ANONVAR_IMPL(Name, Line) Name##Line
#define ANONVAR(Name) ANONVAR_IMPL(Name, __LINE__)

#define REGISTER_GENERATOR(Name, File) \
int ANONVAR(Register##_Name) = []{ \
	CodeGen::_registeredGenerators().push_back(CodeGen::CodeGenerator{ Name, File }); \
	return 0; \
}()

