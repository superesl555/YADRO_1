#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Tape.h"
#include "nlohmann/json.hpp"

// nlohmann/json: https://github.com/nlohmann/json

TapeConfig readConfig(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) throw std::runtime_error("Failed to open config file");

    nlohmann::json j;
    in >> j;

    return TapeConfig{
        j["readDelayMs"],
        j["writeDelayMs"],
        j["moveDelayMs"]
    };
}

int main() {
    try {
        TapeConfig config = readConfig("config.json");

        std::vector<int> data = {42, 13, 99, 1, 8};

        {
            Tape inputTape("input.tape", config, true, data.size());
            for (int value : data) {
                inputTape.write(value);
                inputTape.moveRight();
            }
        }

        std::vector<int> buffer;

        Tape input("input.tape", config, false, data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            buffer.push_back(input.read());
            input.moveRight();
        }

        std::sort(buffer.begin(), buffer.end());

        Tape output("output.tape", config, true, buffer.size());
        for (int value : buffer) {
            output.write(value);
            output.moveRight();
        }

        std::cout << "Сортировка завершена. Проверь output.tape\n";
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
    }

    return 0;
}
