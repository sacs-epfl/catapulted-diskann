#pragma once

#include <vector>
#include <cstddef> // for size_t
#include <cstdint>

#include "distance.h"

namespace diskann {

    template <typename T>
    class SimilarityHasher {
    public:
        SimilarityHasher(size_t num_hash, size_t stored_vectors_dim);

        size_t hash_int(const T* vector) const;

    private:
        size_t stored_vectors_dim_;
        // Stores hyperplanes. Each inner vector is a normal vector of size stored_vectors_dim_.
        std::vector<std::vector<float>> projections_;
        AVXDistanceInnerProductFloat dot_computer_;
    };

} // namespace diskann
