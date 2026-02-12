#include <benchmark/benchmark.h>

#include "func.hpp"

/*
radek@5zzftt-dell:~/PLAY/GEN_IPS/build$ ./gen_ips_benchmark --benchmark_min_time=1000000x
2026-01-25T22:50:12+01:00
Running ./gen_ips_benchmark
Run on (16 X 2173.41 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x8)
  L1 Instruction 32 KiB (x8)
  L2 Unified 1280 KiB (x8)
  L3 Unified 24576 KiB (x1)
Load Average: 1.35, 1.22, 1.05
----------------------------------------------------------
Benchmark                Time             CPU   Iterations
----------------------------------------------------------
BM_SomeFunction       1389 ns         1388 ns      1000000

*/

static void BM_SomeFunction(benchmark::State& state) {
  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
    const auto res = genIPs("112233445");
  }
}

static void BM_IsOctetOk(benchmark::State& state) {
  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
    const auto res = isOctetOk("245");
  }
}

// Register the function as a benchmark
BENCHMARK(BM_SomeFunction);

BENCHMARK_MAIN();