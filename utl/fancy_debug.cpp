#include "fancy_debug.hpp"

#include <ctime>
#include <iomanip>
#include <thread>

#include "bit.hpp"
#include "functional.hpp"
#include "stdio.hpp"
#include "typeinfo.hpp"

namespace utl {

std::false_type __utl_report_assertion_failure(__utl_assertion_kind kind,
                                               char const* module_name,
                                               source_info data,
                                               char const* expr,
                                               std::string expanded,
                                               char const* message) __utl_noreturn {
    bool const has_msg   = message && std::strlen(message) > 0;
    char const* kind_str = [&] {
        switch (kind) {
        case __utl_assertion_kind::assertion: return "Assertion";
        case __utl_assertion_kind::precondition: return "Precondition";
        case __utl_assertion_kind::postcondition: return "Postcondition";
        }
    }();

    auto const message_ends_with_dot = [&] {
        if (!has_msg)
            return false;
        char const last = message[strlen(message) - 1];
        return last == '.' || last == '!' || last == '?';
    }();

    utl::print("{}{}:{} {}{} failed{}: {}{}{} \n"
               "\twith expansion {}  {}  {}\n"
               "\t[{}{}{} : line {}]\n"
               "\t[{}{}{}]\n"
               "was not satisfied{}{}{}{}{}\n\n",
               format_codes::gray,
               module_name,
               format_codes::reset,

               format_codes::red | format_codes::bold,
               kind_str,
               format_codes::reset | format_codes::gray,
               format_codes::reset,
               expr,
               format_codes::gray,

               format_codes::reset | format_codes::background_red | format_codes::light_gray,
               expanded,
               format_codes::reset | format_codes::gray,

               format_codes::italic,
               data.function,
               format_codes::reset | format_codes::gray,
               data.line,

               format_codes::italic,
               data.file,
               format_codes::reset | format_codes::gray,

               has_msg ? ": " : ".",
               has_msg ? format_codes::blue | format_codes::italic : format_codes::reset,
               has_msg ? message : "",
               !has_msg || message_ends_with_dot ? "" : ".",
               format_codes::reset);

    return {};
};

} // namespace utl
