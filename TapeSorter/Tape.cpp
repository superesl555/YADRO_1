#include "Tape.h"
#include <iostream>

Tape::Tape(const std::string& fileName, const TapeConfig& config, bool createNew, size_t initialElements)
    : filename(fileName), config(config), position(0), totalElements(initialElements) {
    if (createNew) {
        std::ofstream out(fileName, std::ios::binary | std::ios::trunc);
        int zero = 0;
        for (size_t i = 0; i < initialElements; ++i)
            out.write(reinterpret_cast<const char*>(&zero), sizeof(int));
        out.close();
    }

    file.open(fileName, std::ios::in | std::ios::out | std::ios::binary);
    if (!file)
        throw std::runtime_error("Failed to open tape file: " + fileName);
}

Tape::~Tape() {
    close();
}

void Tape::close() {
    if (file.is_open())
        file.close();
}

void Tape::delay(int ms) const {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int Tape::read() {
    delay(config.readDelayMs);
    file.seekg(position * sizeof(int), std::ios::beg);
    int value;
    file.read(reinterpret_cast<char*>(&value), sizeof(int));
    return value;
}

void Tape::write(int value) {
    delay(config.writeDelayMs);
    file.seekp(position * sizeof(int), std::ios::beg);
    file.write(reinterpret_cast<const char*>(&value), sizeof(int));
    file.flush();
}

void Tape::moveLeft() {
    if (position > 0) {
        --position;
        delay(config.moveDelayMs);
    }
}

void Tape::moveRight() {
    if (position + 1 < totalElements) {
        ++position;
        delay(config.moveDelayMs);
    }
}

void Tape::rewindToStart() {
    position = 0;
    delay(config.moveDelayMs * position);
}

bool Tape::isEnd() const {
    return position >= totalElements - 1;
}

bool Tape::isBeginning() const {
    return position == 0;
}
