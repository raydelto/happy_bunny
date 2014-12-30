/*
 * AndroidJni.h
 *
 *  Created on: Aug 14, 2014
 *      Author: Raydelto
 */

#ifndef __ANDROID_URL_JNI_H__
#define __ANDROID_URL_JNI_H__

extern "C"
{
    extern void showAdmobJNI();
    extern void hideAdmobJNI();
    extern void setAdmobVisibleJNI(int number);
    extern void setVisibleAdmobJNI(bool visible);
    extern void setAdmobVisibilityJNI(const char* name);

}
#endif
