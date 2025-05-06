#pragma once

class ITape {
public:
    virtual int read() = 0;
    virtual void write(int value) = 0;
    virtual void moveLeft() = 0;
    virtual void moveRight() = 0;
    virtual void rewindToStart() = 0;

    virtual bool isEnd() const = 0;
    virtual bool isBeginning() const = 0;

    virtual ~ITape() = default;
};
