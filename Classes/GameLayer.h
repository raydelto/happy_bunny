#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "SimpleAudioEngine.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace CocosDenshion;

enum {
    kSpriteBomb,
    kSpriteShockwave,
    kSpriteMeteor,
    kSpriteHealth,
    kSpriteHalo,
    kSpriteSparkle
};

enum {
    kBackground,
    kMiddleground,
    kForeground
};


class GameLayer : public CCLayer
{
private:

	CCArray * _meteorPool;
    int _meteorPoolIndex;
    
    CCArray * _healthPool;
    int _healthPoolIndex;
    
    
	CCArray * _fallingObjects;
    CCArray * _clouds;

    CCSpriteBatchNode * _gameBatchNode;
    CCSprite * _bomb;
    CCSprite * _shockWave;
    
    CCSprite * _introMessage;
    CCSprite * _gameOverMessage;
    
    CCLabelBMFont * _energyDisplay;
    CCLabelBMFont * _scoreDisplay;
    
    CCAction * _growBomb;
    CCAction * _rotateSprite;
    CCAction * _shockwaveSequence;
    CCAction * _swingHealth;

    CCAction * _groundHit;
    CCAction * _explosion;
    
    
    CCSize _screenSize;
	
	float _meteorInterval;
	float _meteorTimer;
	float _meteorSpeed;
    float _healthInterval;
    float _healthTimer;
    float _healthSpeed;
    float _difficultyInterval;
    float _difficultyTimer;

	int _energy;
    int _score;
    int _shockwaveHits;
    bool _running;
    
	void resetMeteor(void);
    void resetHealth(void);
    void resetGame(void);
    void stopGame(void);
    void increaseDifficulty(void);
    
    void createGameScreen (void);
    void createPools(void);
    void createActions(void);
protected:
    void keyBackClicked(void);
public:
    
    ~GameLayer(void);
    
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameLayer);
    
    void fallingObjectDone(CCNode* pSender);
    void animationDone(CCNode* pSender);
    void shockwaveDone();
    
    virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
   
    virtual void update (float dt);
};

#endif // __GAMELAYER_H__
