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

class Odbcslap {
public:
    Odbcslap();

    Odbcslap(const std::string &dsn, const std::string &username, const std::string &password,
             const std::vector<std::string> &queries, const uint iterations = 10);

    Odbcslap(const std::string &dsn, const std::vector<std::string> &queries, const uint iterations = 10);

    virtual ~Odbcslap(){};

    const std::string &getPassword() const;

    void setPassword(const std::string &password);

    const std::string &getUsername() const;

    void setUsername(const std::string &username);

    const std::string &getDsn() const;

    void setDsn(const std::string &dsn);

    const uint &getIterations() const;

    void setIterations(const uint &iterations);

    const std::vector<std::shared_ptr<Query>> &getQueries() const;

    void addQuery(std::unique_ptr<Query> &query);

    void benchmark();

    friend std::ostream& operator<<(std::ostream& output, const Odbcslap& odbcslap) {
      for(int query = 0; query < odbcslap.queries.size(); query++) {
        output << "Query " << query << " " << *odbcslap.queries[query];
      }
      return output;
    };
private:

    bool connect();

    std::string dsn;
    std::string username;
    std::string password;
    std::vector<std::shared_ptr<Query>> queries;
    uint iterations;
    nanodbc::connection connection;

};
#endif //PROJECT_ODBCSLAP_HPP

