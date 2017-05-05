#include <iostream>
#include <vector>
#include <password.hpp>
#include <cxxopts.hpp>
#include <odbcslap.hpp>


int main(int argc, char* argv[])
{

  cxxopts::Options options("Odbcslap", "Run and benchmark queries against a odbc database");

  options.add_options()
      ("v,verbose", "Enable verbose output")
      ("d,dsn", "Dsn to connect with", cxxopts::value<std::string>())
      ("u,username", "Optional username to connect to database", cxxopts::value<std::string>())
      ("p,password", "Optional password to connect to database", cxxopts::value<std::string>())
      ;

  options.parse(argc, argv);

  std::string password;
  if(options["p"].as<std::string>().empty()) {

    SetStdinEcho(false);
    std::cout << "password: ";
    std::cin >> password;

    SetStdinEcho(true);
  } else {
    password = options["p"].as<std::string>();
  }

  std::vector<std::string> queries;

  Odbcslap odbcslap;
  if(password.empty() && options.count("u") == 0) {
    odbcslap = Odbcslap(options["d"].as<std::string>(), queries);
  } else {
    odbcslap = Odbcslap(options["d"].as<std::string>(), options["u"].as<std::string>(), password, queries);
  }

  return 0;
}