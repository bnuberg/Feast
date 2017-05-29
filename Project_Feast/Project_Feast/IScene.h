#pragma once
namespace Ogre {
	class SceneManager;
	class RenderWindow;
}

namespace OgreBites {
	class SdkCameraMan;
}

class IScene
{
public:
	IScene();
	~IScene();

	virtual void CreateScene(Ogre::SceneManager* sceneManager, Ogre::RenderWindow* mWindow) = 0;
};

