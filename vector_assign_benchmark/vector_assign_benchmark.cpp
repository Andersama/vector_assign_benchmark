// vector_assign_benchmark.cpp : Defines the entry point for the application.
//

#define ANKERL_NANOBENCH_IMPLEMENT
#include "nanobench.h"

#include <vector>

int main() {
  ankerl::nanobench::Bench benchmark;
  benchmark.warmup(4);
  benchmark.performanceCounters(true);
  benchmark.relative(true);

  uint32_t bench_size = 1024;
  uint32_t target_size = 1024 * 128;

  uint32_t total = 0;

  std::vector<uint32_t> vec_0;
  std::vector<uint32_t> vec_1;

  std::string title = "_______________________________________";

  while (bench_size < target_size) {
    benchmark.batch(bench_size);
    vec_0.reserve(bench_size);
    vec_1.reserve(bench_size);

    std::string bench_num = std::to_string(bench_size);

    title = std::string{"operator= ("} + bench_num + ")";
    benchmark.run(title, [&]() {
      std::vector<uint32_t> v = vec_0;
      ankerl::nanobench::doNotOptimizeAway(v);
      total += v.size();
    });

    title = std::string{"assign ("} + bench_num + ")";
    benchmark.run(title, [&]() {
      vec_1.assign(vec_0.begin(), vec_0.end());
      total += vec_1.size();
    });

    bench_size *= 2;
  }

  return 0;
}
