#include <iostream>
#include <vector>

#include <utl/vector.hpp>

struct X{
    
    explicit X(struct XAlloc const&);
    
};

struct XAlloc {
    using value_type = X;
    X* allocate(size_t) { return nullptr; }
    void deallocate(X* p, size_t) { assert(p == nullptr); }
    void construct(X* p) { std::construct_at(p, *this); }
};

X::X(XAlloc const&) {}

int main() {
    std::vector<X, XAlloc> v;
    try {
        v.emplace_back();
    }
    catch (std::bad_alloc const& e) {
        std::cout << e.what() << std::endl;
    }
}

