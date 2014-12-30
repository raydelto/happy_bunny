#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "cocos2d.h"

USING_NS_CC;
namespace ast{
	class Engine
	{
	public:
		~Engine();
		Engine();
		bool collisions(CCSprite* sprite, CCPoint* point);
		bool collisions(CCSprite* sprite1,	CCSprite* sprite2);		

	};
}

#endif  // __ENGINE_H__
