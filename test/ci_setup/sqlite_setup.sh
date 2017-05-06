#!/bin/bash -ue

# Licensed under MIT per nanodb project.
# Taken from https://github.com/lexicalunit/nanodbc/blob/master/utility/ci/travis/before_script.sqlite.sh

export TEST_DSN="DRIVER=SQLite3;Database=test.db"

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
