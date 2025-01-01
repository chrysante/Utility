#ifndef UTL_DYNAMIC_LIBRARY_HPP_
#define UTL_DYNAMIC_LIBRARY_HPP_

#include <filesystem>
#include <string>
#include <string_view>
#include <type_traits>

#include <utl/__base.hpp>
#include <utl/api.hpp>

namespace utl {

/// Different modes to pass to `dynamic_library` constructor and `load()` method
/// See https://linux.die.net/man/3/dlopen
enum class dynamic_load_mode : int {
    /// Perform lazy binding
    lazy = 0x1,

    /// Eager binding, this is the default
    now = 0x2,

    /// This is the converse of `global`, and the default if neither flag is
    /// specified
    local = 0x4,

    /// The symbols defined by this library will be made available for symbol
    /// resolution of subsequently loaded libraries.
    global = 0x8,
};

///
inline dynamic_load_mode operator|(dynamic_load_mode a, dynamic_load_mode b) {
    return static_cast<dynamic_load_mode>(static_cast<int>(a) |
                                          static_cast<int>(b));
}

///
inline dynamic_load_mode operator&(dynamic_load_mode a, dynamic_load_mode b) {
    return static_cast<dynamic_load_mode>(static_cast<int>(a) &
                                          static_cast<int>(b));
}

/// Wraps a native shared libary handle
class UTL_API dynamic_library {
public:
    /// Construct an empty library
    dynamic_library() = default;

    /// Construct and load the shared library at \p libpath with open mode
    /// \p mode
    /// \Note \p libpath must be a null terminated utf8 string on both Windows
    /// and Unix so we pass by `std::string`
    /// \p mode is ignored on Windows
    explicit dynamic_library(std::string libpath,
                             dynamic_load_mode mode = dynamic_load_mode::lazy);

    /// Lifetime functions @{
    dynamic_library(dynamic_library const& other) = delete;
    dynamic_library(dynamic_library&&) noexcept;
    ~dynamic_library();
    dynamic_library& operator=(dynamic_library const&) & = delete;
    dynamic_library& operator=(dynamic_library&&) & noexcept;
    /// @}

    /// \Returns a library containing the symbols of the currently running
    /// executable
    static dynamic_library
    global(dynamic_load_mode mode = dynamic_load_mode::lazy);

    /// Close the currently loaded library
    void close() { destroy(); }

    /// \Returns `true` if a library is currently loaded
    bool is_open() const noexcept { return !!native_handle(); }

    /// \Returns `is_open()`
    explicit operator bool() const { return is_open(); }

    /// Access the symbol \p name from the shared library
    /// Throws if the symbol cannot be resolved
    /// FIXME: The OS APIs require a zero terminated string here
    void* resolve(std::string_view name) const;

    /// \overload
    /// If the symbol can not be resolved a human readable error string is
    /// written into \p error if it is non-null
    void* resolve(std::string_view name, std::string* error) const;

    /// \Returns `reinterpret_cast<std::add_pointer_t<T>>(resolve(name))`
    template <typename T>
    std::add_pointer_t<T> resolve_as(std::string_view name) const {
        return reinterpret_cast<std::add_pointer_t<T>>(resolve(name));
    }

    /// \overload
    template <typename T>
    std::add_pointer_t<T> resolve_as(std::string_view name,
                                     std::string* error) const {
        return reinterpret_cast<std::add_pointer_t<T>>(resolve(name, error));
    }

    /// \Returns the native library handle as `void*`
    void* native_handle() noexcept { return _handle; }

    /// \Returns the native library handle as `void const*`
    void const* native_handle() const noexcept { return _handle; }

    /// \Returns the filepath of the currently loaded library
    /// The return value is a default constructed path if this library was
    /// constructed by a call to `dynamic_library::global()`
    std::filesystem::path const& current_path() const noexcept { return _path; }

private:
    static void* load_impl(char const* path, dynamic_load_mode mode);
    void destroy() noexcept;
    static void clear_errors();
    void handle_error(std::string_view) const;

private:
    std::filesystem::path _path;
    void* _handle = nullptr;
    dynamic_load_mode _mode =
        dynamic_load_mode::lazy | dynamic_load_mode::local;
};

} // namespace utl

#endif // UTL_DYNAMIC_LIBRARY_HPP_
