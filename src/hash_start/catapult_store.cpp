#include "hash_start/catapult_store.h"
#include "hash_start/hasher.h"
#include <cassert>
#include <cstdlib>

namespace diskann {

    template<typename T>
    CatapultStore<T>::CatapultStore(size_t dimensions, size_t num_hash, size_t fifo_evict)
        : _dimensions(dimensions), _num_hash(num_hash), _fifo_evict(fifo_evict), hasher(num_hash, dimensions) {
        auto bucket_count = 1 << num_hash;

        buckets = std::make_unique<std::optional<LockedBucket>[]>(bucket_count);
        for (size_t i = 0; i < bucket_count; ++i) {
            buckets[i].emplace(fifo_evict);
        }
    }

    template<typename T>
    uint64_t CatapultStore<T>::signature(const T* vector) {
        return hasher.hash_int(vector);
    }

    template<typename T>
    void CatapultStore<T>::insert(uint64_t signature, size_t id) {
        assert(signature < (1 << _num_hash));
        buckets[signature].value().insert(id);
    }

    template<typename T>
    std::vector<size_t> CatapultStore<T>::get_bucket(uint64_t signature) {
        assert(signature < (1 << _num_hash));
        return buckets[signature].value().get();
    }
}

template class diskann::CatapultStore<float>;
template class diskann::CatapultStore<int8_t>;
template class diskann::CatapultStore<uint8_t>;
