//
// Created by seth on 5/5/17.
//

#include <odbcslap.hpp>

const std::string &Odbcslap::getUsername() const {
  return username;
}

void Odbcslap::setUsername(const std::string &username) {
  Odbcslap::username = username;
}

const std::string &Odbcslap::getPassword() const {
  return password;
}

void Odbcslap::setPassword(const std::string &password) {
  Odbcslap::password = password;
}

const std::string &Odbcslap::getDsn() const {
  return dsn;
}

void Odbcslap::setDsn(const std::string &dsn) {
  Odbcslap::dsn = dsn;
}

const std::vector<std::string> &Odbcslap::getQueries() const {
  return queries;
}

void Odbcslap::setQueries(const std::vector<std::string> &queries) {
  Odbcslap::queries = queries;
}

Odbcslap::Odbcslap() {}


Odbcslap::Odbcslap(const std::string &dsn, const std::string &username, const std::string &password,
         const std::vector<std::string> &queries) {

}

Odbcslap::Odbcslap(const std::string &dsn, const std::vector<std::string> &queries) {

}
