#include "hash_start/lru_set.h"
#include <algorithm>

void diskann::LruSet::insert(size_t id) {
    // should insert in set without duplicate. if element is already there, it is moved to the back. front is evicted if needed.

    auto it = std::find(_fifo.begin(), _fifo.end(), id);
    if (it != _fifo.end()) {
        _fifo.erase(it);
    }
    _fifo.push_back(id);
    if (_fifo.size() > _max_size) {
        _fifo.erase(_fifo.begin());
    }
}

std::vector<size_t> diskann::LruSet::get() {
    return _fifo;
}
