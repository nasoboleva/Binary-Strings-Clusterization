#include <iostream>
#include <string>
#include <set>
#include <map>
#include <fstream>
#include <time.h>
#include <algorithm>


char ChageToOpposite(char &symbol) {
    if (symbol == '0') {
        symbol = '1';
    } else {
        symbol = '0';
    }
    return symbol;
}


std::set<std::string> FindNeighbours (std::string &current_string) {
    std::set<std::string> neighbours;
    std::string neighbour = current_string;
    for (size_t i = 0; i != current_string.size(); ++i) {
        neighbour[i] = ChageToOpposite(neighbour[i]);
        neighbours.insert(neighbour);
        for (size_t j = i + 1; j != neighbour.size(); ++j) {
            neighbour[j] = ChageToOpposite(neighbour[j]);
            neighbours.insert(neighbour);
            neighbour[j] = ChageToOpposite(neighbour[j]);
        }
        neighbour[i] = ChageToOpposite(neighbour[i]);
    }
    return neighbours;
}

size_t cluster_number;

bool ClusterMaking (std::string current_string, std::map<std::string, size_t> &clusters) {
    size_t current_number = cluster_number;
    bool new_cluster = true;
    std::set<std::string> neighbours = FindNeighbours(current_string);
    for (const auto & neighbour : neighbours) {
        if (clusters.find(neighbour) != clusters.end()) {
            if (clusters[neighbour] != -1) {
                current_number = clusters[neighbour];
                new_cluster = false;
            }
        } else {
            neighbours.erase(neighbours.find(neighbour));

        }
    }
    for (const auto & neighbour : neighbours) {
        clusters[neighbour] = current_number;
    }
    return new_cluster;
}

void ClusterBinaryStrings(std::map<std::string, size_t> &clusters) {
    std::string current_string;
    cluster_number = 1;
    for (const  auto & key: clusters) {
        current_string = key.first;
        if (clusters[current_string] == -1) {
            if (ClusterMaking(current_string, clusters)) {
                ++cluster_number;
            }
        }
    }
}

int main()
{
    clock_t time;
    std::ifstream fin("example.txt");
    size_t number_of_elements, string_size;
    fin >> number_of_elements >> string_size;
    std::map<std::string, size_t> clusters;
    std::string binary_string;
    for (size_t i = 0; i < number_of_elements; ++i) {
        fin >> binary_string;
        clusters[binary_string] = -1;
    }
    fin.close();


    time = clock();
    ClusterBinaryStrings(clusters);

    std::cout << cluster_number - 1 << std::endl;

    time = clock() - time;
    return 0;
}
