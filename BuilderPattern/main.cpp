#include "BuilderPattern.h"

int main() {
    // 抽象建造者
    AbstractBuilder* builder = nullptr;
    // 指挥者 (生命周期在main中)
    Director director;  

    // 指定具体建造者A
    builder = new ConcreteBuilderA();
    director.setBuilder(builder);

    // house的所有权转移给调用方
    std::unique_ptr<House> houseA = director.construct();
    houseA->printfHouseInfo();
    
    // 注意：house内存已被外部接管，不应由builder释放
    delete builder;  // 此时builder的析构函数应避免删除house
    // delete houseA;   // 由调用方手动释放house内存

    // 指定具体建造者B (这里应改成ConcreteBuilderB)
    builder = new ConcreteBuilderB();
    director.setBuilder(builder);

    std::unique_ptr<House> houseB = director.construct();
    houseB->printfHouseInfo();

    delete builder;  // 同上
    // delete houseB;   // 调用方负责释放内存

    return 0;
}