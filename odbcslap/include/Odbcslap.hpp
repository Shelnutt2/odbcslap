//
// Created by seth on 5/5/17.
//

#ifndef PROJECT_ODBCSLAP_HPP
#define PROJECT_ODBCSLAP_HPP

#include <string>
#include <vector>
#include <nanodbc.h>
#include <iostream>
#include <Query.hpp>
#include <ctpl_stl.h>
#include <cursesapp.h>
#include <chrono>


class Odbcslap : public NCursesApplication {
public:
    Odbcslap() : Odbcslap(std::string(), std::string(), std::string(), {}){};

    Odbcslap(const std::string &dsn, const std::string &username, const std::string &password,
             const std::vector<std::string> &queries, const uint32_t iterations = 10, const uint32_t threads = 1,
             const bool verbose = false);

    Odbcslap(const std::string &dsn, const std::vector<std::string> &queries,
             const uint32_t iterations = 10, const uint32_t threads = 1,
             const bool verbose = false) : Odbcslap(dsn, std::string(), std::string(),
                                                    queries, iterations, threads, verbose){};

    virtual ~Odbcslap(){};

    const std::string &getPassword() const;

    void setPassword(const std::string &password);

    const std::string &getUsername() const;

    void setUsername(const std::string &username);

    const std::string &getDsn() const;

    void setDsn(const std::string &dsn);

    const uint32_t &getIterations() const;

    void setIterations(const uint32_t &iterations);

    const uint32_t &getThreads() const;

    void setThreads(const uint32_t &threads);

    const std::vector<std::shared_ptr<Query>> &getQueries() const;

    void addQuery(std::shared_ptr<Query> &query);

    void setVerbose(const bool verbose);

    void benchmark();

    void benchmark(const std::shared_ptr<Query> &query);

    int run();

    void printStatusUpdate();

    std::string to_string() const {
      std::stringstream ret;
      for(uint32_t query = 0; query < queries.size(); query++) {
        ret << "Query " << query << " " << *queries[query] << std::endl;
      }
      return ret.str();
    };

    friend std::ostream& operator<<(std::ostream& output, const Odbcslap& odbcslap) {
      output << odbcslap.to_string();
      return output;
    };

    operator const std::string () const { return to_string(); }
private:

    bool connect();
    int titlesize() const { return 2; };
    void title();

    std::string dsn;
    std::string username;
    std::string password;
    std::vector<std::shared_ptr<Query>> queries;
    uint32_t iterations;
    uint32_t threads;
    nanodbc::connection connection;
    ctpl::thread_pool thpool;
    bool verbose;

    std::shared_ptr<NCursesPanel> mystd;
    std::shared_ptr<NCursesPanel> QueriesPanel;
    std::chrono::steady_clock::time_point last_screen_update;
};
#endif //PROJECT_ODBCSLAP_HPP

