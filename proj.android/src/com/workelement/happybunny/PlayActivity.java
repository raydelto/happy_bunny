package com.workelement.happybunny;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ImageButton;

import com.google.ads.Ad;
import com.google.ads.AdListener;
import com.google.ads.AdRequest;
import com.google.ads.AdRequest.ErrorCode;
import com.google.ads.InterstitialAd;

public class PlayActivity extends Activity {
	private ImageButton b;
	private InterstitialAd interstitial;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.play_activity);

		// Create the interstitial.
		interstitial = new InterstitialAd(this, getResources().getString(
				R.string.interstitialAdId));
		// interstitial.setAdUnitId(getResources().getString(R.string.interstitialAdId));

		// Create ad request.
		AdRequest adRequest = new AdRequest();/*
											 * new AdRequest.Builder()
											 * .addTestDevice
											 * ("633BD471840312DA03E7CFD9297CF29F"
											 * ) //Celular eburgos
											 * .addTestDevice
											 * ("F5C597036DE61A84F051F81D73BECE53"
											 * ) //Celular wanda .build();
											 */

		adRequest.addTestDevice("633BD471840312DA03E7CFD9297CF29F"); //Celular eburgos 
        adRequest.addTestDevice("F5C597036DE61A84F051F81D73BECE53"); //Celular wanda 
        adRequest.addTestDevice("E8B4B73DC4CAD78DFCB44AF69E7B9EC4"); //Celular Raydelto 
        adRequest.addTestDevice("789A0D2D1D591F796179AA00D7148AD3"); //Celular Fernando
		b = (ImageButton) findViewById(R.id.btnPlay);
		b.setVisibility(View.INVISIBLE);
		b.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				startActivity(new Intent(PlayActivity.this, HappyBunny.class));

			}
		});
		
		
		
        // Set the AdListener.
        interstitial.setAdListener(new AdListener() {
            /*@Override
            public void onAdLoaded() {
                displayInterstitial();
                b.setVisibility(View.VISIBLE);
            }

            @Override
            public void onAdFailedToLoad(int errorCode) {
                b.setVisibility(View.VISIBLE);
            }*/

			@Override
			public void onDismissScreen(Ad arg0) {
				b.setVisibility(View.VISIBLE);
				
			}

			@Override
			public void onFailedToReceiveAd(Ad arg0, ErrorCode arg1) {
				b.setVisibility(View.VISIBLE);
				
			}

			@Override
			public void onLeaveApplication(Ad arg0) {				
				
			}

			@Override
			public void onPresentScreen(Ad arg0) {
                displayInterstitial();
                b.setVisibility(View.VISIBLE);

				
			}

			@Override
			public void onReceiveAd(Ad arg0) {
				// TODO Auto-generated method stub
				displayInterstitial();
			}
        });


        interstitial.loadAd(adRequest);
		b.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				startActivity(new Intent(PlayActivity.this, HappyBunny.class));

			}
		});

	}


    public void displayInterstitial() {
        if (interstitial.isReady()) {
            interstitial.show();
        }
    }
}
