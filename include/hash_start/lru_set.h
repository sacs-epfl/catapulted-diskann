#pragma once

#include <cstddef>
#include <vector>

namespace diskann {
    class LruSet {
    private:
        std::vector<size_t> _lru;
        size_t _max_size;

    public:
        LruSet(size_t lru_evict) {
            _lru.reserve(lru_evict);
            _max_size = lru_evict;
        }
        void insert(size_t id);

        std::vector<size_t> get();
    };
}
