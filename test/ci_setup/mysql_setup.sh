#!/bin/bash

sudo odbcinst -i -d -f /usr/share/libmyodbc/odbcinst.ini
mysql -e "DROP DATABASE IF EXISTS test;" -uroot
mysql -e "CREATE DATABASE IF NOT EXISTS test;" -uroot
mysql -e "GRANT ALL PRIVILEGES ON *.* TO 'root'@'localhost';" -uroot
export TEST_DSN="Driver=MySQL;Server=localhost;Database=test;User=root;Password=;"
