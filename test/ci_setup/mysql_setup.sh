#!/bin/bash

sudo odbcinst -i -d -f /usr/share/libmyodbc/odbcinst.ini
mysql -e "DROP DATABASE IF EXISTS test;" -uroot
mysql -e "CREATE DATABASE IF NOT EXISTS test;" -uroot
mysql -e "GRANT ALL PRIVILEGES ON *.* TO 'root'@'localhost';" -uroot
export ODBCSLAP_TEST_DSN="Driver=MySQL;Server=localhost;Database=test;User=root;Password=;"
export ODBCSLAP_TEST_DSN_NO_PW="Driver=MySQL;Server=localhost;Database=test"
export ODBCSLAP_TEST_USERNAME="root"
export ODBCSLAP_TEST_PASSWORD=""
