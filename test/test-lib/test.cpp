
#if defined(__GNUC__)
__attribute__((visibility("default")))
#endif
extern "C" int test_function() { return 42; }
