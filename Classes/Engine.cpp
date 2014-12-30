#include "Engine.h"
using namespace ast;



Engine::Engine(){

}


Engine::~Engine(){
}


bool Engine::collisions(CCSprite* sprite, CCPoint* point) {
	CCPoint position = sprite->getPosition();
	CCSize size = sprite->getContentSize();
	CCRect spriteRect = CCRectMake(position.x, position.y, size.width,
			size.height);
	return spriteRect.containsPoint(*point);
}

bool Engine::collisions(CCSprite* sprite1, CCSprite* sprite2) {
	CCPoint position1 = sprite1->getPosition();
	CCSize size1 = sprite1->getContentSize();
	CCRect spriteRect1 = CCRectMake(position1.x, position1.y, size1.width,
			size1.height);

	CCPoint position2 = sprite2->getPosition();
	CCSize size2 = sprite2->getContentSize();
	CCRect spriteRect2 = CCRectMake(position2.x, position2.y, size2.width,
			size2.height);
	return spriteRect1.intersectsRect(spriteRect2);
}
