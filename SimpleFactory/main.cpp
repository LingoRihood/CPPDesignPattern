#include <iostream>
#include <memory>
#include "SimpleFactory.h"

int main() {
    printf("简单工厂模式\n");
	
	//定义工厂类对象
    std::shared_ptr<Factory> fac = std::make_shared<Factory>();

    // std::shared_ptr<AbstractSportProduct> product = std::shared_ptr<AbstractSportProduct>(fac->getSportProduct("Basketball"));
    std::shared_ptr<AbstractSportProduct> product = fac->getSportProduct("Basketball");
    
    fac = std::make_shared<Factory>();
    product = fac->getSportProduct("Football");
    // product = std::shared_ptr<AbstractSportProduct>(fac->getSportProduct("Football"));

	fac = std::make_shared<Factory>();
	product = fac->getSportProduct("Volleyball");	
	// product = std::shared_ptr<AbstractSportProduct>(fac->getSportProduct("Volleyball"));	

// 这段代码仅在 Windows 平台下执行。在 Windows 环境中，system("pause") 会暂停程序的执行，并在控制台输出 "Press any key to continue..."，等待用户按任意键继续。这个代码片段在 Windows 下有用，但在其他操作系统中没有影响。
#ifdef win32
    system("pause");
#endif  
    return 0;
}