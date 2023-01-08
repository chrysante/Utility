#include "single_header_generator.hpp"

#include <fstream>
#include <sstream>
#include <unordered_set>

#include <iostream>

namespace utl {

static std::string make_single_header_impl(std::filesystem::path const&, std::unordered_set<std::string>&);

std::string make_single_header(std::filesystem::path const& path) {
    std::unordered_set<std::string> map;
    return make_single_header_impl(path, map);
}

static void skip_space(std::string_view str, std::size_t* i) {
    while (*i < str.size() && std::isspace(str[*i])) {
        ++*i;
    }
}

static bool find_pragma_once(std::string_view text) {
    return text.find("#pragma once") != std::string_view::npos;
}

static std::string make_single_header_impl(std::filesystem::path const& path, std::unordered_set<std::string>& map) {
    std::fstream file(path);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + path.string());
    }

    std::stringstream sstr;
    sstr << file.rdbuf();
    std::string text = sstr.str();

    if (find_pragma_once(text)) {
        if (map.find(path.string()) != map.end()) {
            return {};
        }
        map.insert(path.string());
    }

    constexpr char const* token = "#include";

    std::size_t pos = 0;
    while ((pos = text.find(token, pos)) != std::string::npos) {
        std::size_t const line_begin = pos;
        pos += std::strlen(token);
        skip_space(text, &pos);
        if (text[pos] != '"') {
            continue;
        }
        std::size_t const end = text.find('"', pos + 1);
        if (end == std::string::npos) {
            throw std::runtime_error("Expected token \"");
        }
        std::string const include_filename =
            std::filesystem::path(path).replace_filename(text.substr(pos + 1, end - pos - 1));
        std::string contents = make_single_header_impl(include_filename, map);
        text.replace(line_begin, end - line_begin + 1, contents);
        pos = line_begin + contents.size();
    }

    if (text.find("#include \"") != std::string::npos) {
        std::cout << text << std::endl;
        __builtin_debugtrap();
    }

    return text;
}

} // namespace utl

//int _ = [] {
//    std::filesystem::path const path("/Users/chrysante/dev/imsui/external/utility/mtl/mtl.hpp");
//
//    auto const single_header_path =
//        (std::filesystem::path(path).remove_filename() / "../mtl_single_header/mtl.hpp").lexically_normal();
//
//    std::filesystem::create_directory(std::filesystem::path(single_header_path).remove_filename());
//
//    std::fstream file(single_header_path, std::ios::out | std::ios::trunc);
//
//    if (!file) {
//        throw std::runtime_error("Failed to open file: " + single_header_path.string());
//    }
//
//    file << utl::make_single_header(path);
//
//    return 0;
//}();
