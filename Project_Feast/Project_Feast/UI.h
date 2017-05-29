#pragma once
#include <SdkTrays.h>
#include "Player.h"


class UI : OgreBites::SdkTrayListener
{
public:
	UI();
	~UI();
	void Init();
	void ShowHud(Player player);

	OgreBites::InputContext mInputContext;
	OgreBites::SdkTrayManager* mTrayMgr;
	OgreBites::ParamsPanel* mDetailsPanel;    // sample details panel
	OgreBites::Label* mLabel;    // sample details panel
	
	
};

