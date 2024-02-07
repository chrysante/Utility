#include <optional>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <utl/small_ptr_vector.hpp>

static int gInt;
static int* gPtr = &gInt;

TEST_CASE("small_ptr_vector") {
    SECTION("default") {
        utl::small_ptr_vector<int*> v;
        CHECK(v.empty());
        CHECK(v.size() == 0);
    }
    SECTION("count value") {
        size_t count = GENERATE(0, 1, 2, 5);
        utl::small_ptr_vector<int*> v(count);
        CHECK(v.empty() == (count == 0));
        CHECK(v.size() == count);
        SECTION("copy ctor") {
            auto w = v;
            CHECK(v.empty() == w.empty());
            CHECK(v.size() == w.size());
        }
        SECTION("move ctor") {
            auto w = std::move(v);
            CHECK(w.empty() == (count == 0));
            CHECK(w.size() == count);
            CHECK(v.size() <= 1);
        }
        SECTION("copy assign") {
            size_t other_count = GENERATE(0, 1, 2, 5);
            utl::small_ptr_vector<int*> w(other_count);
            w = v;
            CHECK(v.empty() == w.empty());
            CHECK(v.size() == w.size());
        }
        SECTION("move assign") {
            size_t other_count = GENERATE(0, 1, 2, 5);
            utl::small_ptr_vector<int*> w(other_count);
            w = std::move(v);
            CHECK(w.empty() == (count == 0));
            CHECK(w.size() == count);
            CHECK(v.size() <= 1);
        }
        SECTION("assign ilist empty") {
            v = {};
            CHECK(v.empty());
        }
        SECTION("assign ilist one") {
            v = { gPtr };
            CHECK(v.size() == 1);
            CHECK(v.front() == gPtr);
        }
        SECTION("assign ilist three") {
            v = { gPtr, gPtr + 1, gPtr + 2 };
            CHECK(v.size() == 3);
            CHECK(v[0] == gPtr);
            CHECK(v[1] == gPtr + 1);
            CHECK(v[2] == gPtr + 2);
        }
        SECTION("clear") {
            v.clear();
            CHECK(v.empty());
            CHECK(v.size() == 0);
        }
        SECTION("insert") {
            int insert_offset = GENERATE(0, 1, 3);
            SECTION("insert single value") {
                if (insert_offset < v.size()) {
                    v.insert(v.begin() + insert_offset, gPtr);
                    CHECK(v.size() == count + 1);
                    CHECK(v[insert_offset] == gPtr);
                }
            }
            SECTION("insert count values") {
                if (insert_offset < v.size()) {
                    int insert_count = GENERATE(0, 1, 5);
                    v.insert(v.begin() + insert_offset, insert_count, gPtr);
                    CHECK(v.size() == count + insert_count);
                    for (int i = 0; i < insert_count; ++i) {
                        CHECK(v[insert_offset + i] == gPtr);
                    }
                }
            }
            SECTION("insert ilist empty") {
                if (insert_offset < v.size()) {
                    v.insert(v.begin() + insert_offset, {});
                    CHECK(v.size() == count);
                }
            }
            SECTION("insert ilist one") {
                if (insert_offset < v.size()) {
                    v.insert(v.begin() + insert_offset, { gPtr });
                    CHECK(v.size() == count + 1);
                    CHECK(v[insert_offset] == gPtr);
                }
            }
            SECTION("insert ilist three") {
                if (insert_offset < v.size()) {
                    v.insert(v.begin() + insert_offset,
                             { gPtr, gPtr + 1, gPtr + 2 });
                    CHECK(v.size() == count + 3);
                    CHECK(v[insert_offset] == gPtr);
                    CHECK(v[insert_offset + 1] == gPtr + 1);
                    CHECK(v[insert_offset + 2] == gPtr + 2);
                }
            }
        }
        SECTION("erase") {
            int erase_offset = GENERATE(0, 1, 3);
            SECTION("erase single value") {
                if (erase_offset < v.size()) {
                    v.erase(v.begin() + erase_offset);
                    CHECK(v.size() == count - 1);
                }
            }
            SECTION("erase multiple values") {
                int erase_count = GENERATE(0, 1, 3);
                if (erase_offset + erase_count < v.size()) {
                    v.erase(v.begin() + erase_offset,
                            v.begin() + erase_offset + erase_count);
                    CHECK(v.size() == count - erase_count);
                }
            }
        }
        SECTION("push_back") {
            v.push_back(gPtr);
            CHECK(v.size() == count + 1);
            CHECK(v.back() == gPtr);
        }
        SECTION("pop_back") {
            if (!v.empty()) {
                v.pop_back();
                CHECK(v.size() == count - 1);
            }
        }
        SECTION("resize") {
            size_t new_size = GENERATE(0, 1, 5, 10);
            v.resize(new_size);
            CHECK(v.size() == new_size);
        }
        SECTION("swap") {
            size_t other_count = GENERATE(0, 1, 5, 10);
            utl::small_ptr_vector<int*> w(other_count);
            v.swap(w);
            CHECK(v.size() == other_count);
            CHECK(w.size() == count);
        }
    }
    SECTION("init list empty") {
        utl::small_ptr_vector<int*> v = {};
        CHECK(v.empty());
    }
    SECTION("init list one") {
        utl::small_ptr_vector<int*> v = { gPtr };
        CHECK(v.size() == 1);
        CHECK(v.front() == gPtr);
    }
    SECTION("init list three") {
        utl::small_ptr_vector<int*> v = { gPtr, gPtr + 1, gPtr + 2 };
        CHECK(v.size() == 3);
        CHECK(v[0] == gPtr);
        CHECK(v.front() == gPtr);
        CHECK(v[1] == gPtr + 1);
        CHECK(v[2] == gPtr + 2);
        CHECK(v.back() == gPtr + 2);
        int index = 0;
        for (auto ptr : v) {
            CHECK(ptr == gPtr + index);
            ++index;
        }
        CHECK(index == 3);
    }
    SECTION("reserve") {
        utl::small_ptr_vector<int*> v;
        v.reserve(100);
        CHECK(v.capacity() >= 100);
        CHECK(v.empty());
        CHECK(v.size() == 0);
    }
    SECTION("operator==, operator<=>") {
        CHECK(utl::small_ptr_vector{ gPtr, gPtr + 1 } ==
              utl::small_ptr_vector{ gPtr, gPtr + 1 });
        CHECK(utl::small_ptr_vector{ gPtr, gPtr + 1 } !=
              utl::small_ptr_vector{ gPtr, gPtr + 2 });
        CHECK(utl::small_ptr_vector{ gPtr, gPtr + 1 } !=
              utl::small_ptr_vector{ gPtr });
    }
}
