#pragma once
#include "ITape.h"
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>

struct TapeConfig {
    int readDelayMs;
    int writeDelayMs;
    int moveDelayMs;
};

class Tape : public ITape {
private:
    std::fstream file;
    std::string filename;
    TapeConfig config;
    size_t position;
    size_t totalElements;

    void delay(int ms) const;

public:
    Tape(const std::string& fileName, const TapeConfig& config, bool createNew = false, size_t initialElements = 0);
    ~Tape();

    int read() override;
    void write(int value) override;
    void moveLeft() override;
    void moveRight() override;
    void rewindToStart() override;

    bool isEnd() const override;
    bool isBeginning() const override;

    void close();
};
