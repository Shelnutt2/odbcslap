# odbcslap
Like mysqlslap but for odbc

[![Build Status](https://travis-ci.org/Shelnutt2/odbcslap.svg?branch=master)](https://travis-ci.org/Shelnutt2/odbcslap)

## Installation

```bash
git clone --depth=10 https://github.com/Shelnutt2/odbcslap.git
cd odbcslap
mkdir build
cd build
cmake ..
make -j4
sudo make install
```

## Example Usage


```bash
odbcslap --help
Run and benchmark queries against a odbc database
Usage:
  Odbcslap [OPTION...]

      --help            Print help
  -v, --verbose         Enable verbose output
  -d, --dsn arg         Dsn to connect with
  -u, --username arg    Optional username to connect to database
  -p, --password arg    Optional password to connect to database
  -e, --execute arg     Query to execute
  -i, --iterations arg  Number of iterations to run
  -t, --threads arg     Number of simultaneous clients to simulate
  -c, --clients arg     alias for -c/--clients
  -j, --jobs arg        alias for -t/--threads
  -f, --file arg        File containing queries to benchmark
```

Run against DSN specified in odbc.ini:

```bash
odbcslap -d "MyDSN" -e "Select 'Hello World'"
```

Give DSN on command line:

```bash
odbcslap -d "Driver=MySQL;Server=localhost;Database=test;User=odbcslap_test;Password=;" -e "Select 'Hello World'"
```

Use file containing sql queries:

```bash
odbcslap -d "MyDSN -f /path/to/file.sql
```

See [test/test.sql](test/test.sql) for sample sql file


Set iterations and threads

```bash
odbcslap -d "MyDSN" -f /path/to/file.sql --iterations 100 --threads 25
```
