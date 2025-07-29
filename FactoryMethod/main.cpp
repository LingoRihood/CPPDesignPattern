#include <iostream>
#include "FactoryMethod.h"
#include <memory>

int main() {
    printf("工厂方法模式\n");
	
	// 定义工厂类对象和产品类对象
    std::shared_ptr<AbstractFactory> fac = make_shared<BasketballFactory>();
    // getSportProduct() 返回的是一个 std::shared_ptr<AbstractSportProduct> 类型的对象
    std::shared_ptr<AbstractSportProduct> product = std::shared_ptr<AbstractSportProduct>(fac->getSportProduct());

    fac = make_shared<FootballFactory>();
    product = std::shared_ptr<AbstractSportProduct>(fac->getSportProduct());

    fac = make_shared<VolleyballFactory>();
    product = std::shared_ptr<AbstractSportProduct>(fac->getSportProduct());

    // 这段代码仅在 Windows 平台下执行。在 Windows 环境中，system("pause") 会暂停程序的执行，并在控制台输出 "Press any key to continue..."，等待用户按任意键继续。这个代码片段在 Windows 下有用，但在其他操作系统中没有影响。
#ifdef win32
    system("pause");
#endif  
    return 0;
}