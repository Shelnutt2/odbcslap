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
#include <display.hpp>

class Odbcslap {
public:
    Odbcslap();

    Odbcslap(const std::string &dsn, const std::string &username, const std::string &password,
             const std::vector<std::string> &queries, const uint iterations = 10, const uint threads = 1);

    Odbcslap(const std::string &dsn, const std::vector<std::string> &queries,
             const uint iterations = 10, const uint threads = 1);

    virtual ~Odbcslap(){};

    const std::string &getPassword() const;

    void setPassword(const std::string &password);

    const std::string &getUsername() const;

    void setUsername(const std::string &username);

    const std::string &getDsn() const;

    void setDsn(const std::string &dsn);

    const uint &getIterations() const;

    void setIterations(const uint &iterations);

    const uint &getThreads() const;

    void setThreads(const uint &threads);

    const std::vector<std::shared_ptr<Query>> &getQueries() const;

    void addQuery(std::shared_ptr<Query> &query);

    void benchmark();

    void benchmark(const std::shared_ptr<Query> &query);

    std::string to_string() const {
      std::stringstream ret;
      for(uint query = 0; query < queries.size(); query++) {
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

    std::string dsn;
    std::string username;
    std::string password;
    std::vector<std::shared_ptr<Query>> queries;
    uint iterations;
    uint threads;
    nanodbc::connection connection;
    ctpl::thread_pool thpool;

    ncurses::Environment env;

};
#endif //PROJECT_ODBCSLAP_HPP

