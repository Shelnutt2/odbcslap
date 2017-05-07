//
// Created by seth on 5/5/17.
//

#ifndef PROJECT_ODBCSLAP_HPP
#define PROJECT_ODBCSLAP_HPP

#include <string>
#include <vector>
#include <nanodbc.h>

class Odbcslap {
public:
    Odbcslap();

    Odbcslap(const std::string &dsn, const std::string &username, const std::string &password,
             const std::vector<std::string> &queries);

    Odbcslap(const std::string &dsn, const std::vector<std::string> &queries);

    virtual ~Odbcslap(){};

    const std::string &getPassword() const;

    void setPassword(const std::string &password);

    const std::string &getUsername() const;

    void setUsername(const std::string &username);

    const std::string &getDsn() const;

    void setDsn(const std::string &dsn);

    const std::vector<std::string> &getQueries() const;

    void setQueries(const std::vector<std::string> &queries);

    bool connect();
private:



    std::string dsn;
    std::string username;
    std::string password;
    std::vector<std::string> queries;
    nanodbc::connection connection;

};
#endif //PROJECT_ODBCSLAP_HPP

