#!/usr/bin/env bash

# Creating report
make odbcslap_coverage
cd ${TRAVIS_BUILD_DIR}
lcov --directory . --capture --output-file coverage.info # capture coverage info
lcov --remove coverage.info '/usr/*' --output-file coverage.info # filter out system
lcov --remove coverage.info '*/googletest/*' --output-file coverage.info # filter out google test
lcov --remove coverage.info '*/alternate_shared_mutex.hpp' --output-file coverage.info # filter out 3rd party libs
lcov --remove coverage.info '*/yamc_rwlock_sched.hpp' --output-file coverage.info # filter out 3rd party libs
lcov --remove coverage.info '*/ctpl_stl.h' --output-file coverage.info # filter out 3rd party libs
lcov --list coverage.info #debug info
# Uploading report to CodeCov
bash <(curl -s https://codecov.io/bash) || echo "Codecov did not collect coverage reports"