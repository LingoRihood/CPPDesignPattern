#include <iostream>
#include <memory>
#include "CommandPattern.h"

int main() {
    // 实例化调用者：按钮
	std::unique_ptr<Button> button = std::make_unique<Button>();
	std::unique_ptr<Command> lampCmd = std::make_unique<LampCommand>();
    std::unique_ptr<Command> fanCmd = std::make_unique<FanCommand>();

	// 按钮控制电灯
    // get() 是为了获取智能指针管理的原始指针（裸指针）。
	button->setCommand(lampCmd.get());
	button->touch();
	button->touch();
	button->touch();

	printf("\n\n");

	// 按钮控制风扇
	button->setCommand(fanCmd.get());
	button->touch();
	button->touch();
	button->touch();

#ifdef COMMAND_QUEUE

	printf("\n\n***********************************\n");
	// Button2 *button2 = new Button2();
    std::unique_ptr<Button2> button2 = std::make_unique<Button2>();
	// Command *lampCmd2, *fanCmd2;
	// CommandQueue *cmdQueue = new CommandQueue();

    std::unique_ptr<Command> lampCmd2 = std::make_unique<LampCommand>();
    std::unique_ptr<Command> fanCmd2 = std::make_unique<FanCommand>();
    std::unique_ptr<CommandQueue> cmdQueue = std::make_unique<CommandQueue>();

	// lampCmd2 = new LampCommand();
	cmdQueue->addCommand(lampCmd2.get());

	// fanCmd2 = new FanCommand();
	cmdQueue->addCommand(fanCmd2.get());

	button2->setCommandQueue(cmdQueue.get());
	button2->touch();

#endif

	printf("\n\n");

	// delete button;
	// delete lampCmd;
	// delete fanCmd;
	// delete button2;
	// delete lampCmd2;
	// delete fanCmd2;

	// system("pause");
	return 0;
}