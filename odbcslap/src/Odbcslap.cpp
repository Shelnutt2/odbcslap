//
// Created by seth on 5/5/17.
//

#include <Odbcslap.hpp>

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

const uint &Odbcslap::getIterations() const {
  return iterations;
}

void Odbcslap::setIterations(const uint &iterations) {
  Odbcslap::iterations = iterations;
}

const std::vector<std::shared_ptr<Query>> &Odbcslap::getQueries() const {
  return queries;
}

void Odbcslap::addQuery(std::unique_ptr<Query> &query) {
  Odbcslap::queries.push_back(std::move(query));
}

Odbcslap::Odbcslap() {}


Odbcslap::Odbcslap(const std::string &dsn, const std::string &username, const std::string &password,
         const std::vector<std::string> &queries, const uint iterations) {
  setDsn(dsn);
  setUsername(username);
  setPassword(password);
  setIterations(iterations);
  for(auto it: queries) {
    std::unique_ptr<Query>  qptr(new Query(it));
    addQuery(qptr);
  }

}

Odbcslap::Odbcslap(const std::string &dsn, const std::vector<std::string> &queries, const uint iterations) {
  setDsn(dsn);
  setIterations(iterations);
  for(auto it: queries) {
    std::unique_ptr<Query>  qptr(new Query(it));
    addQuery(qptr);
  }
}


bool Odbcslap::connect() {
  if(username.empty() && password.empty()) {
    this->connection = nanodbc::connection(dsn);
  } else {
    this->connection = nanodbc::connection(dsn, username, password);
  }
  return this->connection.connected();
}

void Odbcslap::benchmark() {
  Odbcslap::connect();
  for(auto &query : getQueries()) {
    for(uint iteration = 0; iteration < Odbcslap::iterations; iteration++) {
      query->execute(connection);
    }
  }
}

