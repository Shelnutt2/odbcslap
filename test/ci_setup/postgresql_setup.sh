#!/bin/bash -ue

sudo odbcinst -i -d -f /usr/share/psqlodbc/odbcinst.ini.template
psql -c "CREATE DATABASE test;" -U postgres
export TEST_DSN="DRIVER={PostgreSQL ANSI};Server=localhost;Port=5432;Database=test;UID=postgres;"
