#ifndef __PROTOTYPE_PATTERN__
#define __PROTOTYPE_PATTERN__

#include <iostream>
#include <string.h>
using namespace std;

// work model类
// 作为复杂的成员对象，供ConcreteWork引用。
class WorkModel {
public:
    std::string modelName;
    WorkModel() : modelName("") {}
    WorkModel(const std::string& iName) : modelName(iName) {}
    void setWorkModelName(const std::string& iName) {
        this->modelName = iName;
    }

    std::string getWorkModelName() const {
        return modelName;
    }

    // 深拷贝构造函数
    // 深拷贝构造函数防止多个对象共享同一个内存（避免浅拷贝问题）。
    // std::string 本身已经重载了拷贝构造函数和赋值运算符，实现了深拷贝的语义。
    WorkModel(const WorkModel& other) : modelName(other.modelName) {}
};  

// 抽象原型类PrototypeWork
// 定义抽象接口clone()，具体原型类必须实现该方法。
class PrototypeWork {
public:
    PrototypeWork() {}
    virtual ~PrototypeWork() {}
    virtual PrototypeWork* clone() = 0;
    virtual void printWorkInfo() const = 0;
};

// 具体原型类PrototypeWork
class ConcreteWork: public PrototypeWork {
public:
    ConcreteWork(const string& iName, int iIdNum, const string& modelName)
        : name(iName), idNum(iIdNum), workModel(new WorkModel(modelName)) {}

    // 深拷贝构造函数
    ConcreteWork(const ConcreteWork& other)
        : name(other.name), idNum(other.idNum), workModel(new WorkModel(*other.workModel)) {}

    // 深拷贝赋值运算符
    // ConcreteWork& operator=(const ConcreteWork& other) {
    //     if (this != &other) {
    //         name = other.name;
    //         idNum = other.idNum;
    //         delete workModel;
    //         workModel = new WorkModel(*other.workModel);
    //     }
    //     return *this;
    // }

    // 克隆接口实现（返回深拷贝）
    PrototypeWork* clone() override {
        return new ConcreteWork(*this);
    }

    ~ConcreteWork() {
        delete workModel;
    }

    // 打印work信息
	void printWorkInfo() const override {
        std::cout << "Name: " << name << std::endl;
        std::cout << "IdNum: " << idNum << std::endl;
        std::cout << "ModelName: " << workModel->getWorkModelName() << std::endl;
    }

    // 新增set方法
    void setName(const std::string& newName) {
        name = newName;
    }

    void setIdNum(int newIdNum) {
        idNum = newIdNum;
    }

    void setModel(WorkModel* newModel) {
        if (workModel != nullptr) {
            delete workModel;
        }
        workModel = newModel;
    }

    // 新增get方法
    std::string getName() const {
        return name;
    }

    int getIdNum() const {
        return idNum;
    }

    WorkModel* getModel() const {
        return workModel;
    }

private:
    string name;
    int idNum;
    WorkModel* workModel;
};

#endif //__PROTOTYPE_PATTERN__