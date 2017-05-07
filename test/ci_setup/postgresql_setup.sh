#!/bin/bash -ue

sudo odbcinst -i -d -f /usr/share/psqlodbc/odbcinst.ini.template
psql -c "CREATE DATABASE test;" -U postgres
export ODBCSLAP_TEST_DSN="DRIVER={PostgreSQL ANSI};Server=localhost;Port=5432;Database=test;UID=postgres;"
export ODBCSLAP_TEST_DSN_NO_PW="DRIVER={PostgreSQL ANSI};Server=localhost;Port=5432;Database=test"
export ODBCSLAP_TEST_USERNAME="postgres"
export ODBCSLAP_TEST_PASSWORD=""
