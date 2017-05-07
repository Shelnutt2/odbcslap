#!/bin/bash -ue

# Licensed under MIT per nanodb project.
# Taken from https://github.com/lexicalunit/nanodbc/blob/master/utility/ci/travis/before_script.sqlite.sh

export ODBCSLAP_TEST_DSN="DRIVER=SQLite3;Database=test.db"
export ODBCSLAP_TEST_DSN_NO_PW="DRIVER=SQLite3;Database=test.db"
export ODBCSLAP_TEST_USERNAME=""
export ODBCSLAP_TEST_PASSWORD=""

if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
    DRIVER="$(brew ls -v sqliteodbc | grep libsqlite3odbc.dylib)"
    cat >"$(odbc_config --odbcinstini)" <<EOF
[SQLite3]
Description             = SQLite3 ODBC Driver
Setup                   = $DRIVER
Driver                  = $DRIVER
Threading               = 2

EOF
else
    sudo odbcinst -i -d -f /usr/share/sqliteodbc/unixodbc.ini
fi
