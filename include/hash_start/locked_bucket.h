#pragma once

#include "lru_set.h"
#include <cstddef>
#include <mutex>
#include <shared_mutex>
#include <vector>
namespace diskann {

    class LockedBucket {
        private:
            LruSet data;
            mutable std::shared_mutex mutex;

        public:
            LockedBucket(size_t max_size) : data(max_size), mutex() {}

            void insert(size_t id) {
                std::unique_lock<std::shared_mutex> lock(mutex);
                data.insert(id);
            }

            std::vector<size_t> get() {
                std::shared_lock<std::shared_mutex> lock(mutex);
                return data.get();
            }
    };
}
