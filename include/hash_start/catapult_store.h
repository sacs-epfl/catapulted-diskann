#pragma once

#include "hash_start/hasher.h"
#include "locked_bucket.h"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

namespace diskann {

    template<typename T>
    class CatapultStore {
        private:
            std::size_t _dimensions;
            std::size_t _num_hash;
            std::size_t _fifo_evict;
            std::unique_ptr<std::optional<LockedBucket>[]> buckets;
            SimilarityHasher<T> hasher;

        public:
            CatapultStore(size_t dimensions, size_t num_hash, size_t fifo_evict);
            uint64_t signature(const T* vector);
            void insert(uint64_t signature, size_t id);
            std::vector<size_t> get_bucket(uint64_t signature);

    };
}
