#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;


AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    //CCSize designSize = CCSizeMake(480, 320);
    CCSize designSize = CCSizeMake(768, 1280);
    std::vector<std::string> searchPaths;

    
    CCLog("Screen height %f \n", screenSize.height);
    
    if(screenSize.height > 800){
    	//High Resolution
    	searchPaths.push_back("hd");
    	pDirector -> setContentScaleFactor(1280.0f / designSize.height);

    }else if(screenSize.height > 600){
    	//Mid resolution
    	searchPaths.push_back("md");
    	pDirector -> setContentScaleFactor(800.0f / designSize.height);

    }else{
    	//Low resolution
    	searchPaths.push_back("sd");
    	pDirector -> setContentScaleFactor(320.0f / designSize.height);

    }
    //pDirector -> setContentScaleFactor(designSize.height / screenSize.height);
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionNoBorder);


    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    // run
    pDirector->runWithScene(pScene);
    CCLog("Finished launching...");
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
