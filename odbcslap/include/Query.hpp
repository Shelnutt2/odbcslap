//
// Created by Seth Shelnutt on 5/7/17.
//

#ifndef PROJECT_QUERY_HPP
#define PROJECT_QUERY_HPP

#include <string>
#include <vector>
#include <nanodbc.h>
#include <iostream>
#include <sstream>      // std::stringstream, std::stringbuf

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

    void execute(nanodbc::connection connection);

    std::string to_string() const {
      std::stringstream ret;
      ret << "Response Time: average: " << average_query_times
                                    << " , median: " << median_query_time << ", min: "
                                    << min_query_time << ", max: " << max_query_time;
      return ret.str();
    };

    friend std::ostream& operator<<(std::ostream& output, const Query& query) {
      output << query.to_string();
      return output;
    };

    operator const std::string () const { return to_string(); }

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
