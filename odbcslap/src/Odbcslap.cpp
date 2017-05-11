//
// Created by seth on 5/5/17.
//

#include <Odbcslap.hpp>
#include <cstring>
#include <cursesp.h>

#ifndef __MINGW32__
extern "C" unsigned int sleep(unsigned int);
#endif

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

void Odbcslap::setVerbose(const bool verbose) {
  Odbcslap::verbose = verbose;
}

Odbcslap::Odbcslap(const std::string &dsn, const std::string &username, const std::string &password,
         const std::vector<std::string> &queries, const uint32_t iterations, const uint32_t threads, const bool verbose)
        : NCursesApplication(verbose){
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

  last_screen_update = std::chrono::steady_clock::now();
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
    if(verbose)
      printStatusUpdate();
  }
}

void Odbcslap::title() {
  const char * const titleText = "Simple C++ Binding Demo";
  const int len = ::strlen(titleText);

  titleWindow->bkgd(screen_titles());
  titleWindow->addstr(0, (titleWindow->cols() - len)/2, titleText);
  titleWindow->noutrefresh();
}

int Odbcslap::run() {
  mystd = std::make_shared<NCursesPanel>();
  NCursesPanel P(mystd->lines() - titlesize(), mystd->cols(), titlesize() - 1, 0);
  P.label("ODBC Slap", NULL);
  P.show();

  QueriesPanel = std::make_shared<NCursesPanel>(mystd->lines() - P.lines(), mystd->cols(), titlesize(), 0);

  if (NCursesApplication::getApplication()->useColors()) {
    QueriesPanel->bkgd(' '|COLOR_PAIR(1));
  }

  mystd->refresh();
  benchmark();

  mystd->clear();
  mystd->refresh();
  return 0;
}

void Odbcslap::printStatusUpdate() {
  std::chrono::milliseconds diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - last_screen_update);
  if( diff >= std::chrono::milliseconds(500)) {
    QueriesPanel->clear();
    for (uint32_t index = 0; index < queries.size(); index++) {
      std::string query_details = "Query " + std::to_string(index) + ": " + queries[index]->to_string();
      QueriesPanel->printw(index, 0, query_details.c_str());
    }
    QueriesPanel->refresh();
    mystd->refresh();
    last_screen_update = std::chrono::steady_clock::now();
  }
}