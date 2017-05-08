#include <iostream>
#include <vector>
#include <password.hpp>
#include <cxxopts.hpp>
#include <Odbcslap.hpp>
#include <fstream>


int main(int argc, char* argv[])
{

  cxxopts::Options options("Odbcslap", "Run and benchmark queries against a odbc database");

  options.add_options()
    ("help", "Print help")
    ("v,verbose", "Enable verbose output")
    ("d,dsn", "Dsn to connect with", cxxopts::value<std::string>())
    ("u,username", "Optional username to connect to database", cxxopts::value<std::string>())
    ("p,password", "Optional password to connect to database", cxxopts::value<std::string>())
    ("e,execute", "Query to execute", cxxopts::value<std::string>())
    ("i,iterations", "Number of iterations to run", cxxopts::value<uint>())
    ("t,threads", "Number of simultaneous clients to simulate", cxxopts::value<uint>())
    ("c,clients", "alias for -c/--clients", cxxopts::value<uint>())
    ("j,jobs", "alias for -t/--threads", cxxopts::value<uint>())
    ("f,file", "File containing queries to benchmark", cxxopts::value<std::string>())
    ;

  options.parse(argc, argv);

  if (options.count("help"))
  {
    std::cout << options.help({"", "Group"}) << std::endl;
    exit(0);
  }

  if(options.count("e") && options.count("f")) {
    std::cerr << "Cannot specify queryfile (-f/--file) and -e/--execute option!" << std::endl;
    return 1;
  }

  std::string password;
  if(options.count("p") && options["p"].as<std::string>().empty()) {

    SetStdinEcho(false);
    std::cout << "password: ";
    std::cin >> password;

    SetStdinEcho(true);
  } else {
    password = options["p"].as<std::string>();
  }

  uint iterations = 10;
  if(options.count("i")) {
    iterations = options["i"].as<uint>();
  }

  uint threads = 1;
  if(options.count("t")) {
    threads = options["t"].as<uint>();
  } else if(options.count("c")) {
    threads = options["c"].as<uint>();
  } else if(options.count("j")) {
    threads = options["j"].as<uint>();
  }

  std::vector<std::string> queries;
  if(options.count("e") && !options["e"].as<std::string>().empty()) {
    queries.push_back(options["e"].as<std::string>());
  } else if (options.count("f")) {
    std::ifstream ifs(options["f"].as<std::string>());
    if(!ifs.good()) {
      std::cerr << "Query file: " << options["f"].as<std::string>() << " not found" << std::endl;
      return 1;
    }
    std::string query((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));
    queries.push_back(query);
  }

  std::unique_ptr<Odbcslap> odbcslap;
  if(password.empty() && options.count("u") == 0) {
    odbcslap = std::unique_ptr<Odbcslap>(new Odbcslap(options["d"].as<std::string>(), queries, iterations, threads));
  } else {
    odbcslap = std::unique_ptr<Odbcslap>(new Odbcslap(options["d"].as<std::string>(), options["u"].as<std::string>(),
                        password, queries, iterations, threads));
  }

  odbcslap->benchmark();
  std::cout << *odbcslap << std::endl;

  return 0;
}