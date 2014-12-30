/*
 * AndroidJni.cpp
 *
 *  Created on: Aug 14, 2014
 *      Author: Raydelto
 */

#include "AndroidJni.h"
//#include "../../cocos2dx/platform/android/jni/JniHelper.h"
#include "platform/android/jni/JniHelper.h"

#include <jni.h>

using namespace cocos2d;

extern "C"
{
    void showAdmobJNI(){
    	JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t, "com.ray.androidtest/AndroidTest"
						,"showAdmobJNI"
						,"()V"))
		{
			t.env->CallStaticVoidMethod(t.classID,t.methodID);
		}
    }
    void hideAdmobJNI(){
    	JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t, "com.ray.androidtest/AndroidTest"
						,"hideAdmobJNI"
						,"()V"))
		{
			t.env->CallStaticVoidMethod(t.classID,t.methodID);
		}
    }
    void setAdmobVisibleJNI(int number){
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t, "com.ray.androidtest/AndroidTest"
						,"setAdmobVisibleJNI"
						,"(I)V"))
		{
			t.env->CallStaticVoidMethod(t.classID,t.methodID,number);
		}
    }
    void setVisibleAdmobJNI(bool visible){
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t, "com.ray.androidtest/AndroidTest"
						,"setVisibleAdmobJNI"
						,"(Z)V"))
		{
			t.env->CallStaticVoidMethod(t.classID,t.methodID,visible);
		}
    }
    void setAdmobVisibilityJNI(const char* name){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, "com.ray.androidtest/AndroidTest"
                        ,"setAdmobVisibilityJNI"
                        ,"(Ljava/lang/String;)V"))
        {
            jstring StringArg1 = t.env->NewStringUTF(name);
            t.env->CallStaticVoidMethod(t.classID,t.methodID, StringArg1);
        }
    }
}
