#include <utl/dynamic_library.hpp>

#include <sstream>
#include <stdexcept>

#include <utl/__debug.hpp>
#include <utl/scope_guard.hpp>

#if defined(__unix__) || defined(__APPLE__)
#include <dlfcn.h>
#else
#error Unsupported system
#endif

using namespace utl;

static bool operator!(dynamic_load_mode mode) {
    return !static_cast<int>(mode);
}

dynamic_library::dynamic_library(std::filesystem::path libpath,
                                 dynamic_load_mode mode):
    _path(std::move(libpath)), _handle(nullptr), _mode(mode) {
    _handle = load_impl(_path.c_str(), mode);
}

dynamic_library::dynamic_library(dynamic_library&& rhs) noexcept:
    _path(std::move(rhs._path)), _handle(rhs._handle) {
    rhs._handle = nullptr;
}

dynamic_library::~dynamic_library() {
    destroy();
}

dynamic_library& dynamic_library::operator=(dynamic_library&& rhs) & noexcept {
    if (this == &rhs) {
        return *this;
    }
    destroy();
    _path = std::move(rhs._path);
    _handle = rhs._handle;
    _mode = rhs._mode;
    rhs._handle = nullptr;
    return *this;
}

dynamic_library dynamic_library::global(dynamic_load_mode mode) {
    dynamic_library lib;
    lib._mode = mode;
    lib._handle = load_impl(nullptr, mode);
    return lib;
}

void* dynamic_library::resolve(std::string_view name) const {
    std::string_view err;
    void* sym = resolve(name, &err);
    if (!sym) {
        throw std::runtime_error(std::string(err));
    }
    return sym;
}

void* dynamic_library::resolve(std::string_view name,
                               std::string_view* error) const {
    clear_errors();
    auto* const result = dlsym(_handle, name.data());
    if (char const* native = dlerror()) {
        if (error) {
            *error = native;
        }
        return nullptr;
    }
    return result;
}

static int translateMode(dynamic_load_mode mode) {
    using enum dynamic_load_mode;
    int result = 0;
    if (!!(mode & lazy)) {
        result |= RTLD_LAZY;
    }
    if (!!(mode & now)) {
        result |= RTLD_NOW;
    }
    if (!!(mode & local)) {
        result |= RTLD_LOCAL;
    }
    if (!!(mode & global)) {
        result |= RTLD_GLOBAL;
    }
    return result;
}

void* dynamic_library::load_impl(char const* path, dynamic_load_mode mode) {
    clear_errors();
    void* handle = dlopen(path, translateMode(mode));
    char const* errorStr = dlerror();
    if (!errorStr) {
        return handle;
    }
    std::stringstream err;
    err << "Failed to load library";
    if (path) {
        err << " " << path;
    }
    err << ". Native Error: " << errorStr;
    throw std::runtime_error(err.str());
}

void dynamic_library::destroy() noexcept {
    if (!_handle) {
        return;
    }
    dlclose(_handle);
    _handle = nullptr;
}

void dynamic_library::clear_errors() {
    dlerror();
}
