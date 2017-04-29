#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "GameControl.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::CCLayer
{
private:

	GameControl GameControler;

public:
    static cocos2d::Scene* createScene();
	Node * Menunode;
	Sprite* pWinSprite;
	Sprite* pLoseSprite;

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
 	void menuReplayCallback(cocos2d::Ref* pSender);   
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	// TouchesPerformTest1
	void registerTouchDispatcher();
	bool onTouchBegan(Touch *touch, Event* event); 
	void onTouchMoved(Touch *touch, Event* event); 
	void onTouchEnded(Touch *touch, Event* event); 
	void onTouchCancelled(Touch *touch, Event* event);


	// SpriteBatchNode1
	void HelloWorld::SpriteBatchNodeInit();
	void HelloWorld::addNewSpriteWithCoords(Point p);

	// CommonFunction
	bool PointToSite(Point * thePoint,POINT targetPoint);
	bool SetPointToScreen(POINT targetPoint);
};

#endif // __HELLOWORLD_SCENE_H__
