//
// Created by Seth Shelnutt on 5/7/17.
//

#include <Query.hpp>
#include <stdexcept>
#include <Timer.hpp>
#include <numeric>
#include <algorithm>



template <class T>
double computeAverage(std::vector<T> v) {
  if(v.size() == 1)
    return v[0];
  double sum = std::accumulate(v.begin(), v.end(), 0.0);
  double mean = sum / v.size();
  return mean;
}

template <class T>
T computeMin(std::vector<T> v) {
  return *std::min_element(v.begin(), v.end());
}

template <class T>
T computeMax(std::vector<T> v) {
  return *std::max_element(v.begin(), v.end());
}

template <class T>
T computeMedian(std::vector<T> &v) {
  if(v.size() == 1)
    return v[0];

  size_t n = v.size() / 2;
  std::nth_element(v.begin(), v.begin()+n, v.end());
  return v[n];
}

Query::Query(const std::string &query) : query(query) {}

const std::string &Query::getQuery() const {
  return query;
}

void Query::setQuery(const std::string &query) {
  Query::query = query;
}

const std::vector<double, std::allocator<double>> &Query::getQuery_times() const {
  return query_times;
}

double Query::getAverage_query_times() const {
  return average_query_times;
}

double Query::getMin_query_time() const {
  return min_query_time;
}

double Query::getMax_query_time() const {
  return max_query_time;
}

double Query::getMedian_query_time() const {
  return median_query_time;
}

void Query::addQueryTime(double query_time) {
  // Get write lock for query times vector
  query_times_mutex.lock();
  query_times.push_back(query_time);
  // Release write lock for query times vector
  query_times_mutex.unlock();
}

int Query::execute(nanodbc::connection connection) {
  // Check if connected to database
  if(!connection.connected())
    throw std::invalid_argument("Database connection passed not connected when trying to run query!");

  try {
    Timer tmr;
    nanodbc::execute(connection, query);
    double t = tmr.elapsed();
    addQueryTime(t);
    update_statistics();
  } catch(std::exception e) {
    std::cerr << "Caught exception trying to execute query: " << query << std::endl;
    std::cerr << e.what() << std::endl;
  }
}

void Query::update_statistics() {
  // Get lock for query_times vector
  query_times_mutex.lock_shared();
  Query::max_query_time = computeMax(query_times);
  Query::min_query_time = computeMin(query_times);
  Query::average_query_times = computeAverage(query_times);
  Query::median_query_time = computeMedian(query_times);
  // Release lock for query_times vector
  query_times_mutex.unlock_shared();
}
