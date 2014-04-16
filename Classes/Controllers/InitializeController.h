#ifndef CCGE_CONTROLLERS_InitializeController_H_
#define CCGE_CONTROLLERS_InitializeController_H_

#include "BaseController.h"

NS_CC_GE_BEGIN

class InitializeController:public BaseController
{
public:
	InitializeController(void);
	~InitializeController(void);

	void viewDidLoad();

    void initGameData();

private:

};

NS_CC_GE_END

#endif //CCGE_CONTROLLERS_InitializeController_H_
