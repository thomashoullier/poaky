# Poaky
Poaky is low-level sequential raytracing API for optical design.
It is part of the RobinTrace project. It is implemented in C++.

<img src="doc/images/robintrace-logo.png" alt="RobinTrace logo" width="256"/>

## Documentation
The main value of Poaky is the documentation. The report can
be compiled from the LaTeX files in `doc`. A compiled version
is edited at
[Poaky documentation PDF](https://thomashoullier.com/writeups/robintrace-poaky/robintrace-poaky.html).

## Build
Switch to a `/build` directory at the root of the project folder. Run:

```shell
cmake ..
```

This will download the dependencies and prepare the build targets.
The build targets are the following:

* `main`: Manual example file for trying out code.
* `test`: Test suite.
* `coverage_report`: Code coverage report of the test suite. The report
  may be consulted at `build/coverage_report/index.html`.
* `benchmark`: Benchmark suite.

## Dependencies
We use the following libraries:
* `Eigen3`.
* `Catch2` for tests and benchmark.

They are downloaded automatically through CMake when building.

## Licensing
The software is licensed under MIT, the documentation under CC-BY.
