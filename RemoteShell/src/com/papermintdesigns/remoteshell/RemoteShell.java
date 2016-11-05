package com.papermintdesigns.remoteshell;

import android.app.Activity;
import android.os.Bundle;

public class RemoteShell extends Activity
{
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
	runDaemon();
    }
   // This is the code you have to add
    public native void  runDaemon();
    static {
        System.loadLibrary("rs-jni");
    }
    // It ends here!
}
