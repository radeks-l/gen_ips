#include <benchmark/benchmark.h>

#include "func.hpp"

/*
radek@5zzftt-dell:~/PLAY/GEN_IPS/build$ ./gen_ips_benchmark --benchmark_min_time=1000000x
2026-01-23T12:57:24+01:00
Running ./gen_ips_benchmark
Run on (16 X 4800 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x8)
  L1 Instruction 32 KiB (x8)
  L2 Unified 1280 KiB (x8)
  L3 Unified 24576 KiB (x1)
Load Average: 1.87, 1.79, 1.61
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
----------------------------------------------------------
Benchmark                Time             CPU   Iterations
----------------------------------------------------------
BM_SomeFunction        132 ns          132 ns      1000000

radek@5zzftt-dell:~/PLAY/GEN_IPS/build$ ./gen_ips_benchmark --benchmark_min_time=1000000x
2026-01-23T12:58:27+01:00
Running ./gen_ips_benchmark
Run on (16 X 800 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x8)
  L1 Instruction 32 KiB (x8)
  L2 Unified 1280 KiB (x8)
  L3 Unified 24576 KiB (x1)
Load Average: 1.52, 1.71, 1.59
----------------------------------------------------------
Benchmark                Time             CPU   Iterations
----------------------------------------------------------
BM_SomeFunction       38.6 ns         38.6 ns      1000000

*/

static void BM_SomeFunction(benchmark::State& state) {
  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
    genIPs("1234");
  }
}
// Register the function as a benchmark
BENCHMARK(BM_SomeFunction);

BENCHMARK_MAIN();