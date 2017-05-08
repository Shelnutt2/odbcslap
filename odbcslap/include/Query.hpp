//
// Created by Seth Shelnutt on 5/7/17.
//

#ifndef PROJECT_QUERY_HPP
#define PROJECT_QUERY_HPP

#include <string>
#include <vector>
#include <nanodbc.h>
#include <iostream>

#define YAMC_RWLOCK_SCHED_DEFAULT yamc::rwlock::WriterPrefer
#include <alternate_shared_mutex.hpp>

class Query {
public:
    Query(const std::string &query);

    const std::string &getQuery() const;

    void setQuery(const std::string &query);

    const std::vector<double, std::allocator<double>> &getQuery_times() const;

    void addQueryTime(double query_time);

    double getAverage_query_times() const;

    double getMin_query_time() const;

    double getMax_query_time() const;

    double getMedian_query_time() const;

    int execute(nanodbc::connection connection);

    friend std::ostream& operator<<(std::ostream& output, const Query& query) {
      output << "Response Time: average: " << query.average_query_times
             << " , median: " << query.median_query_time << ", min: "
             << query.min_query_time << ", max: " << query.max_query_time;
      return output;
    };

private:
    std::string query;
    std::vector<double> query_times;
    double average_query_times;
    double min_query_time;
    double max_query_time;
    double median_query_time;

    yamc::alternate::basic_shared_mutex<yamc::rwlock::WriterPrefer> query_times_mutex;

    void update_statistics();
};


#endif //PROJECT_QUERY_HPP
