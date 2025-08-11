#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include <cstdio>     // 用了 printf
#include <utility>    // std::move
#include "common.h"

class AllyCenter;     // 前向声明

class Observer {
public:
    virtual ~Observer() = default;
    virtual void call(INFO_TYPE, AllyCenter* ac) = 0;

    const std::string& getName() const { return name; }
    void setName(std::string n){ name = std::move(n); }

protected:
    std::string name{"none"};
};

// final: Player 不能再有子类
class Player final : public Observer {
public:
    Player() = default;
    explicit Player(std::string n) { setName(std::move(n)); }

    void call(INFO_TYPE, AllyCenter* ac) override; // 这里只声明
    void help() const;
    void come() const;
};

#endif