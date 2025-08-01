#include "PrototypePattern.h"

int main() {
#if 0
// 下面的代码将不会被编译，也不会执行
	ConcreteWork *singleWork = new ConcreteWork("Single",1001,"Single_Model");
	printf("\nSingle的作业：\n");
	singleWork->printWorkInfo();
	
	printf("\njungle直接抄作业……\n");
	ConcreteWork *jungleWork = singleWork;
	printf("\nJungle的作业：\n");
	jungleWork->printWorkInfo();

	// 抄完改名字和学号，否则会被老师查出来
	printf("\njungle抄完改名字和学号，否则会被老师查出来……\n");
	jungleWork->setName("jungle");
	jungleWork->setIdNum(1002);
	WorkModel *jungleModel = new WorkModel();
	jungleModel->setWorkModelName("Jungle_Model");
	jungleWork->setModel(jungleModel);
	
	// 检查下是否改对了
	printf("\nSingle的作业：\n");
	singleWork->printWorkInfo();
	printf("\nJungle的作业：\n");
	jungleWork->printWorkInfo();
#endif 
// #if 0
// 下面的代码将不会被编译，也不会执行
	ConcreteWork *singleWork = new ConcreteWork("Single", 1001, "Single_Model");
	printf("\nSingle的作业：\n");
    singleWork->printWorkInfo();

	// clone() 返回 PrototypeWork*，需类型转换
	printf("\njungle直接抄作业……\n");
    ConcreteWork* jungleWork = dynamic_cast<ConcreteWork*>(singleWork->clone());
    printf("\nJungle的作业：\n");
	jungleWork->printWorkInfo();

	// 抄完改名字和学号，否则会被老师查出来
	printf("\njungle抄完改名字和学号，否则会被老师查出来……\n");
	jungleWork->setName("jungle");
	jungleWork->setIdNum(1002);
	WorkModel *jungleModel = new WorkModel();
	jungleModel->setWorkModelName("Jungle_Model");
	jungleWork->setModel(jungleModel);

	// 检查下是否改对了
	printf("\nSingle的作业：\n");
	singleWork->printWorkInfo();
	printf("\nJungle的作业：\n");
	jungleWork->printWorkInfo();

	delete singleWork;
	delete jungleWork;
// #endif 
	return 0;
}