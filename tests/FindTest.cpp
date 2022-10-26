/*
 * LRUCache11 - a templated C++11 based LRU cache class that allows
 * specification of key, value and optionally the map container type (defaults
 * to std::unordered_map) By using the std::map and a linked list of keys it
 * allows O(1) insert, delete and refresh operations.
 *
 * This is a header-only library and all you need is the LRUCache11.hpp file
 *
 * Github: https://github.com/mohaps/lrucache11
 *
 * This is a follow-up to the LRUCache project -
 * https://github.com/mohaps/lrucache
 *
 * Copyright (c) 2012-22 SAURAV MOHAPATRA <mohaps@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

// compile with g++ -std=c++11 -o sample_test LRUCache11Test.cpp
#include <cassert>
#include <cstdint>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "lrucache11/LRUCache11.hpp"

using namespace lru11;
typedef Cache<std::string, int32_t> KVCache;

int main(int argc, char** argv) {
#if __cplusplus >= 201703L
    Cache<std::string, int32_t> cache(4, 0);

    cache.insert("a", 23);
    cache.insert("br", 98);
    cache.insert("zz", 418);
    cache.insert("ll", 11);
    // cache is full

    std::string search = "zz";

    std::optional<int32_t> found =
        cache.findCopy([&search](auto& k, auto& v) { return k == search; });

    assert(found.has_value());
    assert(found.value() == 418);
    std::cout << "Found " << found.value() << std::endl;

    found =
        cache.findCopy([](std::string& k, int32_t& v) { return k == "___"; });
    assert(!found.has_value());

    // add one more, will delete {a, 23}
    cache.insert("f", 8);

    // ensure deleted
    found = cache.findCopy([](auto& k, auto& v) { return k == "a"; });
    assert(!found.has_value());

    // ensure added
    found = cache.findCopy([](auto& k, auto& v) { return k == "f"; });
    assert(found.has_value());
    assert(found.value() == 8);
#endif

    std::cout << "Tests passed\n";

    return 0;
}
