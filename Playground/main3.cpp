#include <mtl/mtl.hpp>

#include <optional>

using namespace mtl;

static void test() {
	true ? std::optional<int>{std::nullopt} : 0;
}
