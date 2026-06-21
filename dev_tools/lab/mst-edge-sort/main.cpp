#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
    const std::string probe = "mst-edge-sort";
    const std::vector<std::string> subtests = {
        "sort_order",
        "sort_preserves_edges",
        "min_edge_first",
    };

    std::string dir = ".";
    if (argc > 0) {
        std::string path = argv[0];
        auto pos = path.find_last_of("/\\");
        if (pos != std::string::npos)
            dir = path.substr(0, pos);
    }

    int failed = 0;
    for (const auto &sub : subtests) {
        const std::string exe = dir + "/" + probe + "_" + sub;
        std::cout << "==> running " << sub << std::endl;
        const int rc = std::system(exe.c_str());
        if (rc != 0) {
            std::cerr << "[FAIL] " << sub << " returned " << rc << std::endl;
            ++failed;
        } else {
            std::cout << "[PASS] " << sub << std::endl;
        }
    }

    std::cout << "\nSummary: " << (subtests.size() - failed) << "/"
              << subtests.size() << " passed" << std::endl;
    return failed == 0 ? 0 : 1;
}
