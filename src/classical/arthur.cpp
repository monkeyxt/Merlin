/******************************************************************************
 * name     solver.cpp
 * author   Tian Xia (tian.xia.th@dartmouth.edu)
 * date     August 27, 2024
 *
 * Entrance for solving a MIS instance.
 ******************************************************************************/
#include <iostream>

#include "certificate.hpp"      /// For Certificate
#include "greedy.hpp"           /// For GreedyAlgo
#include "local.hpp"            /// For LocalSwapAlgo
#include "instance.hpp"         /// For Instance

using namespace MISSolver;

/******************************************************************************
 * Input Parser. Parses the input into Commands
 ******************************************************************************/
struct Command {
    std::string algorithm;
    std::string filename;
    std::string destination;
    std::string certificateName;
};

class InputParser {
public:
    InputParser(int &argc, char **argv) {
        for (int i = 1; i < argc; ++i) {
            this->tokens.push_back(std::string(argv[i]));
        }
    }
    ~InputParser() = default;

    /// Delete all other constructors
    InputParser(const InputParser&) = delete;
    InputParser& operator=(const InputParser&) = delete;
    InputParser(InputParser&&) = delete;
    InputParser& operator=(InputParser&&) = delete;

    /// Return the parsed command
    Command getCommand() const {
        std::string filename = getCmdOption("-f");
        std::string algorithm = getCmdOption("-a");
        std::string destination = getCmdOption("-o");
        return Command{algorithm, filename, destination};
    }

    bool empty() const {
        if (this->tokens.empty()) return true;
        return false;
    }

    bool cmdOptionExists(const std::string &option) const {
        return std::find(this->tokens.begin(), this->tokens.end(), option)
               != this->tokens.end();
    }
private:    
    const std::string& getCmdOption(const std::string& option) const {
        std::vector<std::string>::const_iterator itr;
        itr =  std::find(this->tokens.begin(), this->tokens.end(), option);
        if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
            return *itr;
        }
        static const std::string empty_string("");
        return empty_string;
    }
    std::vector<std::string> tokens;
};


/******************************************************************************
 * Run specified algorithm based on input instance and command
 ******************************************************************************/
void execute(const Instance& instance, const Command& cmd) {
    const std::string& algorithm = cmd.algorithm;
    if (algorithm == "greedy") {
        Certificate certificate = GreedyAlgo(instance);
    } 
    else if (algorithm == "local-search") {
        Certificate currentCertificate(instance);
        Certificate certificate = LocalSwapAlgo(instance, currentCertificate);
    }    
    else {
        std::cout << "Invalid algorithm option: " << algorithm << std::endl;
    }
}

void displayHelp() {
    std::cout << "Usage: ./Arthur [OPTION]...[INPUT FILE]" << std::endl;
    std::cout << "Runs classical algorithm given an input graph" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -a, set algorithm to run (greedy, local-search, gurobi)" << std::endl;
    std::cout << "  -f, set input graph file" << std::endl;
    std::cout << "  -o, set output destination" << std::endl;
}

/******************************************************************************
 * Main entry point
 ******************************************************************************/
int main (int argc, char **argv) {
    InputParser input(argc, argv);
    if(input.cmdOptionExists("-h")
        || input.empty()
        || !input.cmdOptionExists("-a")
        || !input.cmdOptionExists("-f")) {
        displayHelp();
        return 1;
    }
    Command cmd = input.getCommand();
    if (cmd.algorithm == "" || cmd.filename == "") {
        displayHelp();
        std::cout << "Need algorithm and input file!!" << std::endl;
        return 1;
    }

    /// Build & run instance
    Instance instance{};
    instance.read(cmd.filename);
    execute(instance, cmd);

    return 0;
}