#pragma once

#include <Ogre.h>
#include <OgreApplicationContext.h>

using namespace Ogre;

// ApplicationContext, -> Use inbuild simple gui system
// Inputlistener -> Handle inputs 

class MyTestApp
	: public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
	MyTestApp();
	~MyTestApp() {}
	void setup() override;
	bool keyPressed(OgreBites::KeyboardEvent const & evt) override;
};
