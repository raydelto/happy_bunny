#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Engine.h"
#include <string>
//typedef void (cocos2d::CCObject::*SEL_SCHEDULE)(float);
using namespace cocos2d;
class HelloWorld : public cocos2d::CCLayer
{
public:
	HelloWorld();
	~HelloWorld();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, 
    // instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static CCScene* scene();
	// a selector callback
	virtual void menuCloseCallback(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(HelloWorld);
	void spriteMoveFinished(CCNode* sender);
	void cloudMoveFinished(CCNode* sender);
	void gameLogic(float dt);
	void updateGame(float dt);
	void registerWithTouchDispatcher();
	virtual void ccTouchesMoved(CCSet* touches, CCEvent* event);
	virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
	virtual void ccTouchesBegan(CCSet* touches, CCEvent* event);
	virtual void didAccelerate(CCAcceleration* pAccelerationValue);

protected:
	CCSprite* _bg;
	CCSprite* _player;
	CCSprite* _idlePlayer;
	CCSprite* _leftPlayer;
	CCSprite* _rightPlayer;
	CCSprite* _eatingPlayer;
	CCSprite* _blackPlayer;
	CCSprite* _clouds;
	CCSprite* _sun;
	CCLabelTTF* _lblScore;
	CCSize _winSize;
	CCSize _visibleSize;
	CCArray* _carrots;
	CCArray* _bgArray;
	CCArray* _bombs;
	CCArray* _lifeBar;
	float _playerMiddlePoint;
	float _screenRatio;
	bool _move;
	ast::Engine* engine;
	int _score;
	int _innerScore; //Not displayed, is reseted everytime when a level is changed, is used to determine when to change level.
	int _currentLevel;
	int _maxLevel;
	int _maxCarrots;
	int _maxBombs;
	int segundos;
	int _maxSpeed;
	int _minSpeed;
	int _lives;
	std::string _levels[3];
	bool _gameOver;
	int pointsToWin;
	bool collisions(CCSprite* sprite, cocos2d::CCPoint* point);
	bool collisions(CCSprite* sprite1,	CCSprite* sprite2);
	void moveClouds();
	void addItems();
	void initItem(const char *fileName, int tag, cocos2d::CCArray* array);
	void checkIfBunnyEats();
	void makeBunnyEat(float dt);
	void changePlayerSprite(CCSprite* newSprite);
	void crashTest(cocos2d::CCArray* array, const char* soundFileName, SEL_SCHEDULE function, CCSprite* changedSprite);
	void keyBackClicked(void);
	void updateScore(int dt);
	void changeLevel();
	void showEndMessage(std::string message);
	void initLiveBar();
	void initScoreCounter();
	void initBackground();
	void changeBackground(int index);
	void substractLife();
};

#endif  // __HELLOWORLD_SCENE_H__
