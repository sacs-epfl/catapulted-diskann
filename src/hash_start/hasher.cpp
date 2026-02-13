#include "hash_start/hasher.h"
#include <random>
#include <stdexcept>
#include <cmath>

namespace diskann {

    template<typename T>
    SimilarityHasher<T>::SimilarityHasher(size_t num_hash, size_t stored_vectors_dim)
        : stored_vectors_dim_(stored_vectors_dim)
    {

        // Safety check: ensure we can fit the signature into a size_t (usually 64 bits)
        if (num_hash > sizeof(size_t) * 8) {
            throw std::invalid_argument("num_hash cannot exceed the bit width of size_t (usually 64)");
        }
        if (stored_vectors_dim == 0) {
            throw std::invalid_argument("stored_vectors_dim must be greater than 0");
        }

        auto seed = 42;
        // Initialize random number generator with the provided seed
        std::mt19937_64 rng(seed);
        std::normal_distribution<float> dist(0.0f, 1.0f);

        projections_.reserve(num_hash);

        // Generate random hyperplanes
        for (size_t i = 0; i < num_hash; ++i) {
            std::vector<float> plane;
            plane.reserve(stored_vectors_dim);

            for (size_t j = 0; j < stored_vectors_dim; ++j) {
                plane.push_back(dist(rng));
            }
            projections_.push_back(std::move(plane));
        }
    }

    template<typename T>
    size_t SimilarityHasher<T>::hash_int(const T* vector) const {
        if (!vector) {
            throw std::invalid_argument("Input vector pointer cannot be null");
        }

        size_t projected = 0;
        float fvector[stored_vectors_dim_];
        for (size_t i = 0; i < stored_vectors_dim_; ++i) {
            fvector[i] = static_cast<float>(vector[i]);
        }

        // Iterate over each hyperplane, collecting those with positive dot product (vector is on the same side as their normal)
        for (const auto& plane : projections_) {
            // Compute dot product: plane · vector
            float dot = std::inner_product(plane.begin(), plane.end(), fvector, 0.0f);

            projected <<= 1;
            if (dot >= 0.0f) {
                projected |= 1;
            }
        }

        return projected;
    }

    template class SimilarityHasher<float>;
    template class SimilarityHasher<int8_t>;
    template class SimilarityHasher<uint8_t>;

} // namespace diskann
