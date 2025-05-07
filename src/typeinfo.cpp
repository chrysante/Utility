#include <utl/typeinfo.hpp>

#include <utl/__debug.hpp>

#if defined(__GNUC__)

#include <cxxabi.h>

std::string utl::demangle_name(char const* mangled_name) {
    int status = 0;
    char* demangled_name =
        abi::__cxa_demangle(mangled_name, nullptr, nullptr, &status);
    __utl_assert(status == 0, "Name demangling failed");

    std::string const result(demangled_name);
    std::free(demangled_name);
    return result;
}

#else

std::string utl::demangle_name(char const* mangled_name) {
    return mangled_name;
}

#endif

std::string utl::qualified_function_name(std::string_view pretty) {
    try {
        auto const end = pretty.find('(');
        auto const begin = [&]() -> std::size_t {
            std::size_t i = end;
            int openAngle = 0;
            while (i > 0) {
                --i;
                if (pretty[i] == '>') {
                    ++openAngle;
                    continue;
                }
                if (pretty[i] == '<') {
                    --openAngle;
                    continue;
                }
                if (pretty[i] == ' ' && openAngle == 0) {
                    return i + 1;
                }
            }
            return 0;
        }();

        return std::string(pretty.substr(begin, end - begin));
    }
    catch (...) {
        std::abort();
    }
}
