#pragma once

#include <atomic>

namespace diskann {
    class Stats {
        private:
            std::atomic<int> _num_calls;

        public:
            Stats() : _num_calls(0) {}

            void record_call() {
                _num_calls.fetch_add(1, std::memory_order_relaxed);
            }

            int get_num_calls() const {
                return _num_calls.load(std::memory_order_relaxed);
            }
    };
}
