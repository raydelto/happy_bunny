#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include <iostream>
using namespace cocos2d;
using namespace std;
using namespace ast;

HelloWorld::~HelloWorld() {
	CCLog("Releasing resources...");
	/*CC_SAFE_RELEASE_NULL(_idlePlayer);
	CC_SAFE_RELEASE_NULL(_leftPlayer);
	CC_SAFE_RELEASE_NULL(_rightPlayer);
	CC_SAFE_RELEASE_NULL(_eatingPlayer);;
	CC_SAFE_RELEASE_NULL(_carrots);
	_player = NULL;*/
	CCLog("Resources released, ready to exit");
}

HelloWorld::HelloWorld() :	_bg(NULL),_player(NULL),
					_idlePlayer(NULL), _leftPlayer(NULL), _rightPlayer(NULL),_eatingPlayer(NULL), _blackPlayer(NULL),_clouds(NULL),_sun(NULL),_lblScore(NULL), _playerMiddlePoint(0.0f),
					_screenRatio(0.0f),	_move(false), _carrots(NULL), _bombs(NULL), _score(0),_innerScore(0), _gameOver(false),
					_currentLevel(0) , _maxLevel(2), _maxCarrots(4), _maxBombs(3), pointsToWin(15),_maxSpeed(8),_minSpeed(1), _lives(5) {
}

CCScene* HelloWorld::scene() {
	CCScene * scene = NULL;
	do {
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(!scene);

		// 'layer' is an autorelease object
		HelloWorld *layer = HelloWorld::create();
		CC_BREAK_IF(!layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}





void HelloWorld::cloudMoveFinished(cocos2d::CCNode* sender) {
	CCLog("Cloud move finished");
}

void HelloWorld::keyBackClicked(void) {
    CCLog("\nKeyBack pressed\n");
	CCDirector::sharedDirector()->end();

    exit(0);
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
	bool bRet = false;
	//////////////////////////////////////////////////////////////////////////
	// super init first
	//////////////////////////////////////////////////////////////////////////

	CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
	CCLog("Height %f" ,screenSize.height);
	_screenRatio = screenSize.width / screenSize.height;
	CCLog("_screenRatio %f" ,_screenRatio);

	_visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	_winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCLog("About to initialize Player Sprite");

	_idlePlayer = CCSprite::create("bunny_idle.png");
	_leftPlayer = CCSprite::create("bunny_left.png");
	_rightPlayer = CCSprite::create("bunny_right.png");
	_eatingPlayer = CCSprite::create("bunny_eating.png");
	_blackPlayer = CCSprite::create("bunny_black.png");
	_clouds = CCSprite::create("clouds.png");
	_sun = CCSprite::create("sun.png");


	_player = _idlePlayer;
	_playerMiddlePoint = _player->getContentSize().width / 2;

	_idlePlayer -> setAnchorPoint(ccp(0,0));
	_leftPlayer -> setAnchorPoint(ccp(0,0));
	_rightPlayer -> setAnchorPoint(ccp(0,0));
	_eatingPlayer -> setAnchorPoint(ccp(0,0));
	_blackPlayer -> setAnchorPoint(ccp(0,0));
	_clouds -> setAnchorPoint(ccp(0,0));

	_player->setPosition(ccp((_winSize.width / 2) - _playerMiddlePoint , _winSize.height *.13 ));
	CCLog("Player Sprite initialized");
	this->schedule(schedule_selector(HelloWorld::gameLogic), 0.5);
	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);
	this->setAccelerometerEnabled(true);
	this->schedule(schedule_selector(HelloWorld::updateGame));
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bg.mp3", true);
	_sun->setPosition(ccp(_sun->getContentSize().width + (_winSize.width * 0.2), _winSize.height * 0.75));
	_clouds->setPosition(ccp(0 - _clouds->getContentSize().width, _winSize.height * 0.6));
	
	/*_bg = CCSprite::create("bunny_bg.png");
	_bg->setPosition(ccp(_winSize.width * 0.5, _winSize.height * 0.5));	
	this->addChild(_bg,0);*/
	initBackground();
	this->addChild(_sun,1);
	this->addChild(_clouds,2);
	

	this->addChild(_idlePlayer,4);
	_leftPlayer->setVisible(false);
	this->addChild(_leftPlayer,4);
	_rightPlayer->setVisible(false);
	this->addChild(_rightPlayer,4);
	_eatingPlayer->setVisible(false);
	this->addChild(_eatingPlayer,4);
	_blackPlayer->setVisible(false);
	this->addChild(_blackPlayer,4);
	
	bRet = true;
	_carrots = new CCArray();
	_bombs = new CCArray();
	_lifeBar = new CCArray();
	initLiveBar();
	initScoreCounter();
	moveClouds();
	CCLog("Hello World init complete");

	return bRet;
}

void HelloWorld::changeBackground(int index){
	for(int i = 0 ; i <= _maxLevel ; i++){
		CCSprite* bg = dynamic_cast<CCSprite*>(_bgArray->objectAtIndex(i));
		bg->setVisible(i == index);
	}


}

void HelloWorld::initBackground() {
	_bgArray = new CCArray();
	_levels[0] ="bunny_bg.png";
	_levels[1] ="candy_bg.png";
	_levels[2] ="bosque_bg.png";

	for(int i = 0 ; i <= _maxLevel ; i++){
		CCSprite* bg = CCSprite::create(_levels[i].c_str());
		bg->setAnchorPoint(CCPointZero);
		bg->setPosition(CCPointZero);
		this->addChild(bg,0);
		bg->setVisible(i == 0);
		_bgArray -> addObject(bg);		
	}

}

void HelloWorld::initScoreCounter() {
	_lblScore = CCLabelTTF::create("0", "Felt", 32);
	_lblScore ->setColor(ccc3(255, 255, 255));
	_lblScore ->setString("0");
	_lblScore->setVisible(true);
	
	CCSprite* counter = CCSprite::create("carrot_counter.png");
	counter->setAnchorPoint(CCPointZero);
	counter -> setPositionY(_winSize.height - counter->getContentSize().height);
	counter -> setPositionX(_winSize.width - (counter->getContentSize().width *7));
	//_lblScore->setPosition(ccp(_winSize.width * 0.8, _winSize.height * 0.93));
	_lblScore->setAnchorPoint(CCPointZero);
	_lblScore->setPositionY(counter->getPositionY());
	_lblScore->setPositionX(_winSize.width - (counter->getContentSize().width *6));
	this->addChild(_lblScore, 6);
	this->addChild(counter, 5);
}


void HelloWorld::initLiveBar() {
	CCSprite* life = NULL;	
	for(int i = 1 ; i <= _lives ; i++){
		life = CCSprite::create("life.png");
		life->setAnchorPoint(CCPointZero);
		life -> setPositionY(_winSize.height - life->getContentSize().height);
		life -> setPositionX(life->getContentSize().width * i);
		
		this->addChild(life,5);
		_lifeBar ->addObject(life);
	}

}

void HelloWorld::menuCloseCallback(CCObject* pSender) {
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();

}

void HelloWorld::gameLogic(float dt) {
	if(_gameOver){

		return;
	}
	this -> addItems();

}



void HelloWorld::ccTouchesMoved(CCSet* touches, CCEvent* event) {
	if(_gameOver){
		return;
	}
	static int lastX;
	CCTouch* touch = (CCTouch*) (touches->anyObject());
	CCPoint location = touch->getLocation();
	if(collisions(_player,&location)){
		float ratio = location.x/_winSize.height;
		int actualX = location.x - _playerMiddlePoint;
		if(_player != _eatingPlayer && _player != _blackPlayer){
			if(actualX >= lastX){
						changePlayerSprite(_rightPlayer);
			}else{
					changePlayerSprite(_leftPlayer);
			}
		}
		lastX = actualX;
		if(actualX >= 0 && (actualX <= (_winSize.width - _player->getContentSize().width))){
			_player->setPosition(ccp(actualX, _player->getPositionY()));

		}

	}else{
		if(_player != _eatingPlayer && _player != _blackPlayer){
			changePlayerSprite(_idlePlayer);
		}
	}

}

void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event) {
	if(_gameOver){
		return;
	}

	_move = false;
	if(_player != _eatingPlayer && _player != _blackPlayer){
		changePlayerSprite(_idlePlayer);
	}
}

void HelloWorld::ccTouchesBegan(CCSet* touches, CCEvent* event) {
	if(_gameOver){
		return;
	}

	CCTouch* touch = (CCTouch*) (touches->anyObject());
	CCPoint location = touch->getLocation();

	CCObject* it = NULL;
	CCARRAY_FOREACH(_bombs, it) {
		CCSprite *bomb = dynamic_cast<CCSprite*>(it);
		if(collisions(bomb,&location)){
			bomb->setVisible(false);
			_bombs->removeObject(bomb);
			CCParticleFire* fire = CCParticleFire::createWithTotalParticles(100);
			fire->setPosition(bomb->getPositionX(), bomb->getPositionY());
			fire->setScaleX(0.5f);
			fire->setScaleY(0.5f);
			fire->setDuration(0.5);
			fire->setAutoRemoveOnFinish(true);
			this->addChild(fire);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("shot.wav");
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("uh.wav");
			substractLife();
			this->scheduleOnce(schedule_selector(HelloWorld::makeBunnyEat) , 0.5);			
			changePlayerSprite(_blackPlayer);

		}
	}


}

void HelloWorld::substractLife(){		
	CCSprite* life = dynamic_cast<CCSprite*>(_lifeBar->objectAtIndex(_lives-1));
	life->setVisible(false);
	_lives--;
	if(_lives == 0){
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		GameOverScene *gameOverScene = GameOverScene::create();			
		CCDirector::sharedDirector()->replaceScene(gameOverScene);
	}

}

void HelloWorld::updateGame(float dt) {
	if(_gameOver){
		return;
	}
	_player -> update(dt);
	checkIfBunnyEats();
	crashTest(_bombs,"shot.wav", schedule_selector(HelloWorld::makeBunnyEat) , _blackPlayer);
}

void HelloWorld::registerWithTouchDispatcher() {
	CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

bool HelloWorld::collisions(cocos2d::CCSprite* sprite,	cocos2d::CCPoint* point) {
	CCPoint position = sprite -> getPosition();
	CCSize size = sprite->getContentSize();
	CCRect spriteRect = CCRectMake(

		position.x,
		position.y,
		size.width,
		size.height
	);
	return spriteRect.containsPoint(*point);
}

void HelloWorld::didAccelerate(cocos2d::CCAcceleration* pAccelerationValue) {
	float x = pAccelerationValue->x * 30;                //horizontal acceleration
	float y = pAccelerationValue->y;
	float newX = _player->getPositionX() + x;
	if( newX > ( _player->getContentSize().width * -1) && newX < (_winSize.width + _player->getContentSize().width))
	{
		_player->setPositionX(newX);
	}
}

bool HelloWorld::collisions(cocos2d::CCSprite* sprite1,	cocos2d::CCSprite* sprite2) {
	CCPoint position1 = sprite1 -> getPosition();
	CCSize size1 = sprite1->getContentSize();
	CCRect spriteRect1 = CCRectMake(
		position1.x,
		position1.y,
		size1.width,
		size1.height
	);

	CCPoint position2 = sprite2 -> getPosition();
	CCSize size2 = sprite2->getContentSize();
	CCRect spriteRect2 = CCRectMake(
		position2.x,
		position2.y,
		size2.width,
		size2.height
	);
	return spriteRect1.intersectsRect(spriteRect2);
}

void HelloWorld::spriteMoveFinished(cocos2d::CCNode* sender) {
	CCSprite* sprite = (CCSprite*) sender;
	switch(sender->getTag()){
	case 1:
		_carrots->removeObject(sprite);
		break;
	case 2:
		_bombs->removeObject(sprite);
		break;
	}
	this->removeChild(sprite,true);
}

void HelloWorld::addItems() {
	if( _carrots -> count() >= _maxCarrots ){
		if(_bombs -> count() < _maxBombs){
			initItem("bomb.png",2, _bombs);
		}
	}else{
		initItem("carrot_left.png",1, _carrots);
	}
}

void HelloWorld::checkIfBunnyEats() {
	crashTest(_carrots,"nau.wav", schedule_selector(HelloWorld::makeBunnyEat) , _eatingPlayer);
}

void HelloWorld::crashTest(cocos2d::CCArray* array, const char* soundFileName, SEL_SCHEDULE function, cocos2d::CCSprite* changedSprite){
	CCArray* toDelete = new CCArray();
	CCObject* iterator = NULL;
	CCARRAY_FOREACH(array, iterator){
		CCSprite* sprite = dynamic_cast<CCSprite*>(iterator);
		if(collisions(sprite,_player)){
			string sound = soundFileName;
			if(sound ==  "nau.wav"){
				updateScore(1);
			}else{				
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("uh.wav");
				substractLife();
			}
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(soundFileName);
			this->scheduleOnce(function , 0.5);			
			changePlayerSprite(changedSprite);
			toDelete->addObject(sprite);
		}
	}

	CCARRAY_FOREACH(toDelete, iterator){
		CCSprite* sprite = dynamic_cast<CCSprite*>(iterator);
		this->removeChild(sprite,true);
		array->removeObject(sprite);
	}
	toDelete->removeAllObjects();
	CC_SAFE_DELETE(toDelete);

}

void HelloWorld::makeBunnyEat(float dt) {
	changePlayerSprite(_idlePlayer);

}

void HelloWorld::moveClouds() {

	CCFiniteTimeAction* actionMove = CCMoveTo::create(50.0f, ccp(_winSize.width , _winSize.height * 0.6));
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(this,callfuncN_selector(HelloWorld::cloudMoveFinished));
	_clouds -> runAction(CCSequence::create(actionMove,actionMoveDone,NULL));
}

void HelloWorld::initItem(const char* fileName, int tag,cocos2d::CCArray* array) {
	CCSprite* sprite = CCSprite::create(fileName);
	sprite->setAnchorPoint(ccp(0,0));
	//Determine random x location of the carrot
	int max = _visibleSize.width - (sprite->getContentSize().width);
	int min = 0;
	int range = max - min;
	int x = (rand() % range) + min;

	std::string file = fileName;
	if(file == "carrot_left.png"){
		if(x> _visibleSize.width*0.7){
			sprite = CCSprite::create("carrot_right.png");
		}else if(x> _visibleSize.width*0.45){
			sprite = CCSprite::create("carrot_center.png");
		}
		//Default Image is carrot_left
	}


	sprite->setPosition(ccp(x , _winSize.height));

	//Determine random carrot speed
	int rangeSpeed = _maxSpeed - _minSpeed;
	int speed = (rand() % rangeSpeed) + _minSpeed;
	float fSpeed = (float) speed ;
	CCFiniteTimeAction* actionMove = CCMoveTo::create(fSpeed, ccp(x,0));
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(this,callfuncN_selector(HelloWorld::spriteMoveFinished));
	sprite->runAction(CCSequence::create(actionMove,actionMoveDone,NULL));
	sprite->setTag(tag);
	this->addChild(sprite,3);
	array -> addObject(sprite);
}

void HelloWorld::changePlayerSprite(cocos2d::CCSprite* newSprite) {
	 newSprite->setPosition(ccp(_player->getPositionX(), _player->getPositionY()));
	_player->setVisible(false);
	_player = newSprite;
	_player->setVisible(true);
}

void HelloWorld::updateScore(int dt){
		_score += dt;
		_innerScore += dt;
		char scoreText[32];
		sprintf(scoreText, "%d", _score);
		_lblScore->setString(scoreText);

		if(_innerScore > 0 && _innerScore >= pointsToWin){
			CCLog("About to change Level");
			changeLevel();
			_innerScore = 0;
			pointsToWin += 5;
		}
}

void HelloWorld::changeLevel(){
	_currentLevel++;

	if(_currentLevel > _maxLevel){
		_currentLevel = 0;
		_sun->setVisible(true);
	}else{
		_sun->setVisible(false);
	}
	this -> removeChild(_bg,true);
	/*_bg = CCSprite::create(_levels[_currentLevel].c_str());
	_bg->setAnchorPoint(CCPointZero);
	_bg->setPosition(CCPointZero);
	this->addChild(_bg,0);*/
	changeBackground(_currentLevel);
	if(_maxCarrots > 1){
		_maxCarrots--;
	}
	if(_maxSpeed > 2){
		_maxSpeed--;
	}
	_maxBombs++;	
	
}


void HelloWorld::showEndMessage(string message){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
	_player->setVisible(false);
	this->unschedule(schedule_selector(HelloWorld::updateGame));
	this->unschedule(schedule_selector(HelloWorld::gameLogic));
	_lblScore->setPosition(ccp(_winSize.width/2, _winSize.height/2));
	_lblScore->setString(message.c_str());
	_idlePlayer->setVisible(false);
	_leftPlayer->setVisible(false);
	_rightPlayer->setVisible(false);
	_blackPlayer->setVisible(false);
	_eatingPlayer->setVisible(false);
	_gameOver = true;

}

