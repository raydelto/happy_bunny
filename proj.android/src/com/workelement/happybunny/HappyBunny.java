/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.workelement.happybunny;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup.LayoutParams;

import com.google.ads.AdRequest;
import com.google.ads.AdSize;
import com.google.ads.AdView;

public class HappyBunny extends Cocos2dxActivity{
	
	static AdView adView;
	static Activity me;
	//
	final String ADMOB_ID="ca-app-pub-7870675803288590/4907722461";

	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		me=this;
		try {
			LayoutParams adParams = new LayoutParams(LayoutParams.MATCH_PARENT,LayoutParams.MATCH_PARENT);
			
			adView = new AdView(this, AdSize.BANNER,
					ADMOB_ID);			
			AdRequest request = new AdRequest();
			request.addTestDevice("633BD471840312DA03E7CFD9297CF29F"); //Celular eburgos 
			request.addTestDevice("F5C597036DE61A84F051F81D73BECE53"); //Celular wanda 
			request.addTestDevice("E8B4B73DC4CAD78DFCB44AF69E7B9EC4"); //Celular Raydelto 
			request.addTestDevice("789A0D2D1D591F796179AA00D7148AD3"); //Celular Fernando

			adView.loadAd(request);
			adView.setGravity(Gravity.BOTTOM|Gravity.CENTER);
			// Adding full screen container
			addContentView(adView, adParams);
		} catch (Exception e) {
			Log.d("", "error: " + e);
		}
				
	}
	
	static void showAdmobJNI(){
		me.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				adView.setVisibility(View.VISIBLE);
			}
		});
	}
	
	static void hideAdmobJNI(){
		me.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				adView.setVisibility(View.INVISIBLE);
			}
		});
    }
    
	static void setAdmobVisibleJNI(final int number){
		me.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if(number==0){
		    		adView.setVisibility(View.INVISIBLE);
		    	} else {
		    		adView.setVisibility(View.VISIBLE);
		    	}
			}
		});
		
    }
    
	static void setVisibleAdmobJNI(final boolean visible){
		
		me.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if(visible){
		    		adView.setVisibility(View.VISIBLE);
		    	} else {
		    		adView.setVisibility(View.INVISIBLE);
		    	}
			}
		});
    }
    
    static void setAdmobVisibilityJNI(final String name){
    	me.runOnUiThread(new Runnable() {
			@Override
			public void run() {
		    	if(name.equals("show")||name=="show"){
		    		adView.setVisibility(View.VISIBLE);
		    	} else {
		    		adView.setVisibility(View.INVISIBLE);
		    	}
			}
		});
    }
	
    static {
         System.loadLibrary("cocos2dcpp");
    }
}
