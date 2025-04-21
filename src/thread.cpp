#include <utl/thread.hpp>

#if defined(_WIN32)
#include <windows.h>
#elif defined(__APPLE__) || defined(__linux__)
#include <pthread.h>
#endif

bool utl::set_current_thread_name(std::string name) {
#if defined(_WIN32)
    HRESULT hr =
        SetThreadDescription(GetCurrentThread(),
                             std::wstring(name.begin(), name.end()).c_str());
    return SUCCEEDED(hr);
#elif defined(__APPLE__)
    return pthread_setname_np(name.c_str()) == 0;
#elif defined(__linux__)
    return pthread_setname_np(pthread_self(), name.substr(0, 15).c_str()) == 0;
#else
    return false;
#endif
}
