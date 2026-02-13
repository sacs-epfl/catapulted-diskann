#include "hash_start/lru_set.h"
#include <algorithm>

void diskann::LruSet::insert(size_t id) {
    // should insert in set without duplicate. LRU behavior (back is youngest).
    // if element is already there, it is moved to the back. front is evicted if needed
    auto it = std::find(_lru.begin(), _lru.end(), id);
    if (it != _lru.end()) {
        _lru.erase(it);
    }
    _lru.push_back(id);
    if (_lru.size() > _max_size) {
        _lru.erase(_lru.begin());
    }
}

std::vector<size_t> diskann::LruSet::get() {
    return _lru;
}
