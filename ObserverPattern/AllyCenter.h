#ifndef __ALLYCENTER_H__
#define __ALLYCENTER_H__

#include "common.h"
#include <vector>
#include <string>

// 前向声明
// 不做前向声明时，两边的头文件往往互相 #include，形成“包含环”。 由于编译是单向读取的
class Observer;
// class Player;

// 抽象目标：联盟中心
class AllyCenter {
public:
	AllyCenter();
	virtual ~AllyCenter() {}
	// 声明通知方法
	virtual void notify(INFO_TYPE infoType, const std::string& name) = 0;
	// 加入玩家
	void join(Observer *player);
	// 移除玩家
	void remove(Observer *player);

protected:
	// 玩家列表
	std::vector<Observer*> playerList;
};

// 具体目标
class AllyCenterController : public AllyCenter {
public:
	AllyCenterController();
	// 实现通知方法
	void notify(INFO_TYPE infoType, const std::string& name) override;
};

#endif //__ALLYCENTER_H__