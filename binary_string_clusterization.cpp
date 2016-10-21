#include <iostream>
#include <string>
#include <set>
#include <map>
#include <fstream>


char ChageToOpposite(char &a) {
    if (a == '0') {
        a = '1';
    } else {
        a = '0';
    }
    return a;
}


size_t ClusterBinaryStrings(std::set<std::string> objects) {
    size_t cluster_number = 0;
    size_t current_number;
    std::map<std::string, size_t> clusters;
    for (const auto v : objects) {
        if (clusters[v] >  0) {
            current_number = clusters[v];
        } else {
            current_number = ++cluster_number;
            clusters[v] = current_number;
        }
        std::string neighbour = v;
        for (size_t i = 0; i != v.size() - 1; ++i) {
            neighbour[i] = ChageToOpposite(neighbour[i]);
            if (objects.find(neighbour) != objects.end()) {
                clusters[neighbour] = current_number;
            }
            for (size_t j = i + 1; j != v.size(); ++j) {
                neighbour[j] = ChageToOpposite(neighbour[j]);
                if (objects.find(neighbour) != objects.end()) {
                    clusters[neighbour] = current_number;
                }
                neighbour[j] = ChageToOpposite(neighbour[j]);
            }
            neighbour[i] = ChageToOpposite(neighbour[i]);
        }
    }

    return cluster_number;
}

int main()
{
    std::ifstream fin("/home/natalia/Documents/Algo2/binary_strings_clusterization/example.txt");
    size_t number_of_elements, string_size;
    fin >> number_of_elements >> string_size;
    std::set<std::string> objects;
    std::string binary_string;
    for (size_t i = 0; i < number_of_elements; ++i) {
        fin >> binary_string;
        objects.insert(binary_string);
    }
    fin.close();
    size_t cluster_number = ClusterBinaryStrings(objects);

    std::cout << cluster_number << std::endl;
    return 0;
}
