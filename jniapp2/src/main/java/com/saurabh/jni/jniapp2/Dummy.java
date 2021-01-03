package com.saurabh.jni.jniapp2;

import android.util.Log;

public class Dummy {
    public int value;
    public static int value2 = 100;
    public Dummy(int pValue) {
        value = pValue;
        Log.d("Saurabh", "Dummy Value: "+value);
    }
}
