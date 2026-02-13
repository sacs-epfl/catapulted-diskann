#pragma once

#include <cstddef>
#include <vector>

namespace diskann {
    class LruSet {
    private:
        std::vector<size_t> _fifo;
        size_t _max_size;

    public:
        LruSet(size_t fifo_evict) {
            _fifo.reserve(fifo_evict);
            _max_size = fifo_evict;
        }
        void insert(size_t id);

        std::vector<size_t> get();
    };
}
