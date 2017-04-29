#include "HelloWorldScene.h"


enum 
{
	kTagSpriteBatchNode_Black = 1,
	kTagSpriteBatchNode_White = 2
};
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
//
	setTouchEnabled(true);
	registerTouchDispatcher();	
	do 
	{
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
		//图片
		auto pBackGroundSprite = Sprite::create("Square.png");
		CC_BREAK_IF(! pBackGroundSprite);
		pBackGroundSprite->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
		this->addChild(pBackGroundSprite, 0);
		
		pWinSprite = Sprite::create("Win+.png");
		CC_BREAK_IF(! pWinSprite);
		pWinSprite->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
		this->addChild(pWinSprite, 0);
		pWinSprite->setScale(0.5);
		pWinSprite->setVisible(false);

		pLoseSprite = Sprite::create("Lose+.png");
		CC_BREAK_IF(! pLoseSprite);
		pLoseSprite->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
		this->addChild(pLoseSprite, 0);
		pLoseSprite->setScale(0.5);
		pLoseSprite->setVisible(false);
		
		//按钮
		Menunode = Node::create();
		this->addChild(Menunode ,0 );

		auto pCloseItem = MenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
		CC_BREAK_IF(! pCloseItem);
		pCloseItem->setPosition(ccp(visibleSize.width / 2 + 62, visibleSize.height / 2));
		auto pCloseMenu = Menu::create(pCloseItem, NULL);
		pCloseMenu->setPosition(Point::ZERO);
		CC_BREAK_IF(! pCloseMenu);
		Menunode->addChild(pCloseMenu, 1);

		auto pReplayItem = MenuItemImage::create(
			"ReplayNormal.png",
			"ReplaySelected.png",
			CC_CALLBACK_1(HelloWorld::menuReplayCallback,this));
		CC_BREAK_IF(! pReplayItem);
		pReplayItem->setPosition(ccp(visibleSize.width / 2 - 62 , visibleSize.height / 2));
		auto pReplayMenu = Menu::create(pReplayItem, NULL);
		pReplayMenu->setPosition(Point::ZERO);
		CC_BREAK_IF(! pReplayMenu);

		Menunode->addChild(pReplayMenu, 1);
		Menunode->setPosition(ccp(0 , 0));
		Menunode->setScale(0.5);
		Menunode->setVisible(false); 
	} while (0);

	SpriteBatchNodeInit();

/*
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
 */   
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
void HelloWorld::menuReplayCallback(Ref* pSender)
{
	auto BatchNode = (SpriteBatchNode*) getChildByTag(kTagSpriteBatchNode_Black);
	BatchNode->removeAllChildrenWithCleanup(true);

	BatchNode = (SpriteBatchNode*) getChildByTag(kTagSpriteBatchNode_White);
	BatchNode->removeAllChildrenWithCleanup(true);

	GameControler.InitGame();

	Menunode->setVisible(false);
	pWinSprite->setVisible(false);
	pLoseSprite->setVisible(false);
}


////////////////////////////////////////////////////////
//
// TouchesPerformTest1
//
////////////////////////////////////////////////////////

void HelloWorld::registerTouchDispatcher()
{
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	//获取精灵对象并取得精灵的矩阵  
	auto sprite = static_cast<Sprite*>(event->getCurrentTarget());
	Rect rect = sprite->getBoundingBox();
	//获取触摸点的坐标  
	Point point = touch->getLocation();
	//判断触摸点是否在精灵的矩阵范围内  
	if (rect.containsPoint(point))
	{
		return true;
	}
	return false;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
	//获取精灵对象  
	auto sprite = static_cast<Sprite*>(event->getCurrentTarget());
	//改变精灵的位置  
	sprite->setPosition(sprite->getPosition() + touch->getDelta());
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	if(GameControler.IsGameEnable())
	{
		auto location = touch->getLocationInView();
		POINT theSite = {(int)location.x / 40,(int)location.y / 40};
		
		if(SetPointToScreen(theSite) && GameControler.IsGameEnable())
		{
			//AI落子
			//if(!(GameControler.AI_Sample(&theSite) && SetPointToScreen(theSite)))	//测试用：随机落子
			if(!(GameControler.AI_Level_1(&theSite) && SetPointToScreen(theSite)))	//初级AI：
			{
				GameControler.MakeGameDisable();
			}
			//AI落子结束
		}
	}
	else
	{
		Sprite* targetSprite=NULL;
		(GameControler.GetGameResult() == PLAYER_WIN) ? targetSprite = pWinSprite : targetSprite = pLoseSprite;
		(Menunode->isVisible() && targetSprite) ? (Menunode->setVisible(false),targetSprite->setVisible(false)) : (Menunode->setVisible(true),targetSprite->setVisible(true));
	}
}

bool HelloWorld::SetPointToScreen(POINT theSite)
{
	Point location;
	if(PointToSite(&location,theSite))
	{
		if(GameControler.SetChessPoint(theSite))
		{
			#ifdef OUTPUT_DEBUG_STRING
			char tempCh[512] = "";
			sprintf(tempCh,"GameControler.GetChessPlayer() = %d\ntheSite.x = %d ; theSite.y = %d",GameControler.GetChessPlayer(),theSite.x,theSite.y);
			printf("%s\n",tempCh);
			CString wStr = tempCh;
			OutputDebugString(wStr);
			#endif

			location = Director::getInstance()->convertToGL (location);
			addNewSpriteWithCoords(location);

			GameControler.SetGameResult();
			if(GameControler.CheckGameState())
			{
				GameControler.MakeGameDisable();			//使游戏停止响应
				Menunode->setVisible(true);
				this->reorderChild(Menunode,0);

				(GameControler.GetGameResult() == PLAYER_WIN) ? pWinSprite->setVisible(true) : pLoseSprite->setVisible(true);
			}
			return true;
		}
	}
	return false;
}

void HelloWorld::onTouchCancelled(Touch* touch, Event* event)
{
}


////////////////////////////////////////////////////////
//
// SpriteBatchNode
//
////////////////////////////////////////////////////////

void HelloWorld::SpriteBatchNodeInit()
{
	auto BatchNode_Black = SpriteBatchNode::create("Black.png", 50);
	this->addChild(BatchNode_Black, 0, kTagSpriteBatchNode_Black);
	auto BatchNode_White = SpriteBatchNode::create("White.png", 50);
	this->addChild(BatchNode_White, 0, kTagSpriteBatchNode_White);
}

void HelloWorld::addNewSpriteWithCoords(Point p)
{
	int addTag = 0;
	(GameControler.GetChessPlayer() == PLAYER_WHITE) ? (addTag = kTagSpriteBatchNode_White) : (addTag = kTagSpriteBatchNode_Black);
	auto BatchNode = (SpriteBatchNode*) getChildByTag(addTag);

	auto newPoint = Sprite::createWithTexture(BatchNode->getTexture());
	newPoint->setScale(1.5);
	BatchNode->addChild(newPoint);
	newPoint->setPosition(ccp( p.x, p.y));
}


////////////////////////////////////////////////////////
//
// CommonFunction
//
////////////////////////////////////////////////////////

bool HelloWorld::PointToSite(Point * thePoint,POINT targetPoint)
{
	thePoint->x = targetPoint.x * 40 + 20;
	thePoint->y = targetPoint.y * 40 + 20;
	return true;
}