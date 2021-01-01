package com.saurabh.jni.jniapp2;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private static final String LOG_TAGS = "Saurabh";

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    static int si = 10;
    String s = "Saurabh";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());
    }


    public void callJavaMethodFromNative(View view) {
        int ii = getNumberFromCPP(false);
        callback();
        Toast.makeText(this, "Received From Native: "+ii, Toast.LENGTH_SHORT).show();
        printSumOfArray();
        Log.d(LOG_TAGS, "Variable Value before Native Call Int: " + si+" String: "+s);
        accessJavaVariable();
        Log.d(LOG_TAGS, "Variable Value after Native Call Int: " + si+" String: "+s);
    }


    public static int getNumberFromCPP(boolean bool) {
        if(bool)
        {
            return 45;
        }
        return 10;
    }

    public static void printNum(int i) {
        Log.d(LOG_TAGS, "Got int from C++: " + i);
    }

    public void printFloat(float i) {
        Log.d(LOG_TAGS, "Got float from C++: " + i);
    }

    public void printSumOfArray()
    {
        int arr[] = new int [11];
        for (int i = 0; i < 11; i++)
            arr[i] = i;
        int sum = sumArray(arr);
        Log.d(LOG_TAGS, "Got Array Sum from C++: " + sum);
    }


    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native void callback();
    private native int sumArray(int arr[]);
    private native void accessJavaVariable();


}