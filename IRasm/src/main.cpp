#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

#include <boost/program_options.hpp>

#include "compiler.h"
#include "utf8lib.h"

namespace bpo = boost::program_options;
namespace fs = std::filesystem;


/**
 * @brief reads and returns all text from file
 * 
 * @param path path to file
 * @return text from file
 */
std::string readFile(fs::path&& path) noexcept
{
    std::ifstream f(path, std::ios::in | std::ios::binary);
    const auto sz = fs::file_size(path);
    std::string txt(sz, 0);
    f.read(txt.data(), sz);
    f.close();
    return txt;
}


int main(int argc, char* argv[])
{
    bpo::options_description desc("All options");

    desc.add_options()
        ("help,h", "produce help message")
        ("src,s", bpo::value<std::string>(), "source file.\n\t-s main.ira")
        ("out,o", bpo::value<std::string>(), "output file.\n\t-o program.ree");
    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
    bpo::notify(vm);

    if (vm.contains("help")) {
        std::cout << desc << '\n';
        return 0;
    }

    if (vm.contains("src")) {
        std::string filename = vm["src"].as<std::string>();
        std::string code = readFile(filename);
        std::string outputFilename = vm.contains("out") ? vm["out"].as<std::string>() : "out.ree";

        std::ofstream fout(outputFilename, std::ios::binary);
        Compiler compiler{std::move(code), fout};
        compiler.build();
    }

    return 0;
}