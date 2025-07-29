#ifndef __BUILDER_PATTERN__
#define __BUILDER_PATTERN__

#include <iostream>
#include <string.h>
#include <memory>  // 加入智能指针头文件
using namespace std;

/*
产品类 (House)
代表了需要创建的复杂对象（房子）。包含了三个核心部件：
1、地板 (floor)
2、墙 (wall)
3、屋顶 (roof)
*/
class House {
public:
    House() {}
    void setFloor(string iFloor) {
        this->floor = iFloor;
    }

    void setWall(string iWall) {
        this->wall = iWall;
    }

    void setRoof(string iRoof) {
        this->roof = iRoof;
    }

    // 打印House信息
	void printfHouseInfo() {
        // this->floor 是一个 std::string 类型，而C语言函数 printf 无法直接输出 std::string 类型。
        // 使用 .c_str() 就能将 std::string 转换为一个 const char*（C风格字符串） ，供 printf 使用。
		printf("Floor:%s\t\n", this->floor.c_str());
		printf("Wall:%s\t\n", this->wall.c_str());
		printf("Roof:%s\t\n", this->roof.c_str());
	}

private:
    string floor;
    string wall;
    string roof;
};

// 抽象建造者AbstractBuilder
class AbstractBuilder {
public:
    AbstractBuilder() : house(std::make_unique<House>()) {}
    virtual ~AbstractBuilder() = default;  // 使用默认析构函数即可

    AbstractBuilder(const AbstractBuilder&) = delete;
    AbstractBuilder& operator=(const AbstractBuilder&) = delete;

    virtual void buildFloor() = 0;
    virtual void buildWall() = 0;
    virtual void buildRoof() = 0;

    virtual std::unique_ptr<House> getHouse() {
        return std::move(house);  // 转移所有权
    }

protected:
    std::unique_ptr<House> house;
};

// 具体建造者ConcreteBuilderA
// 子类无需再定义getHouse()和析构函数，因为基类已经完成这些任务。
class ConcreteBuilderA: public AbstractBuilder {
public:
    ConcreteBuilderA() { printf("ConcreteBuilderA\n"); }
    void buildFloor() override { house->setFloor("Floor_A"); }
    void buildWall() override { house->setWall("Wall_A"); }
    void buildRoof() override { house->setRoof("Roof_A"); }
};

// 具体建造者ConcreteBuilderB
class ConcreteBuilderB: public AbstractBuilder {
public:
    ConcreteBuilderB() { printf("ConcreteBuilderB\n"); }
    void buildFloor() override { house->setFloor("Floor_B"); }
    void buildWall() override { house->setWall("Wall_B"); }
    void buildRoof() override { house->setRoof("Roof_B"); }
};

// 指挥者Director
class Director {
public:
    Director(): builder(nullptr) {}
    // Builder的生命周期应由调用方自己管理，不能由Director删除，否则可能造成未知问题。
    ~Director() = default;  

    Director(const Director&) = delete;
    Director& operator=(const Director&) = delete;

    void setBuilder(AbstractBuilder* iBuilder) {
        this->builder = iBuilder;
    }

    std::unique_ptr<House> construct() {
        builder->buildFloor();
        builder->buildWall();
        builder->buildRoof();
        return builder->getHouse();  // 返回智能指针
    }

private:
    AbstractBuilder* builder;
};

#endif //__BUILDER_PATTERN__