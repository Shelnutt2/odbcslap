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

const uint32_t &Odbcslap::getIterations() const {
  return iterations;
}

void Odbcslap::setIterations(const uint32_t &iterations) {
  Odbcslap::iterations = iterations;
}

const uint32_t &Odbcslap::getThreads() const {
  return threads;
}

void Odbcslap::setThreads(const uint32_t &threads) {
  Odbcslap::threads = threads;
}

const std::vector<std::shared_ptr<Query>> &Odbcslap::getQueries() const {
  return queries;
}

void Odbcslap::addQuery(std::shared_ptr<Query> &query) {
  Odbcslap::queries.push_back(std::move(query));
}

Odbcslap::Odbcslap() {
  env = ncurses::Environment();
}


Odbcslap::Odbcslap(const std::string &dsn, const std::string &username, const std::string &password,
         const std::vector<std::string> &queries, const uint32_t iterations, const uint32_t threads) {
  setDsn(dsn);
  setUsername(username);
  setPassword(password);
  setIterations(iterations);
  setThreads(threads);
  thpool.resize(threads);
  for(auto it: queries) {
    std::shared_ptr<Query>  qptr(new Query(it));
    addQuery(qptr);
  }

  env = ncurses::Environment();
}

Odbcslap::Odbcslap(const std::string &dsn, const std::vector<std::string> &queries,
                   const uint32_t iterations, const uint32_t threads) {
  setDsn(dsn);
  setIterations(iterations);
  setThreads(threads);
  thpool.resize(threads);
  for(auto it: queries) {
    std::shared_ptr<Query>  qptr(new Query(it));
    addQuery(qptr);
  }

  env = ncurses::Environment();
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

  // If we have more than one thread we need to use the threadpool
  if(threads > 1) {
    // Vector of futures to wait on
    std::vector<std::future<void>> futures;
    // Add each query to a thread
    for (auto &query : getQueries()) {
      futures.push_back(thpool.push([&, this](int id){ this->benchmark(query); }));
    }

    // Wait for threads to finish by blocking on futures
    for(auto &future : futures) {
      future.wait();
    }
  // Special case for when threads == 1
  } else {
    for (auto &query : getQueries()) {
      benchmark(query);
    }
  }
}

void Odbcslap::benchmark(const std::shared_ptr<Query> &query) {
  for (uint32_t iteration = 0; iteration < Odbcslap::iterations; iteration++) {
    query->execute(connection);
    ncurses::printline(query->to_string());
  }
}

