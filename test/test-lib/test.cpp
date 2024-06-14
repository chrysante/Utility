
#if defined(__GNUC__)
__attribute__((visibility("default"))) extern "C" int
#elif defined(_MSC_VER)
extern "C" int __declspec(dllexport) __stdcall
#else 
int
#endif 
test_function() { return 42; }
