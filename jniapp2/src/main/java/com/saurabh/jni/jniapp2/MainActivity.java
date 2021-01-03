package com.saurabh.jni.jniapp2;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private static final String LOG_TAGS = "Saurabh";
    public static StringBuffer resultTextBuffer;
    private TextView resultText;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    static int si = 10;
    String s = "Saurabh";
    private String instanceField = "Instance Field";
    private Dummy dummyF;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        resultTextBuffer = new StringBuffer("");
        dummyF = new Dummy(333);
        resultTextBuffer.append("Java POJO/Getter/Setter class from Native()\n" +
                "before native access Dummy Value is :"+dummyF.value+"\n\n");

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        resultText = findViewById(R.id.example_text);
        tv.setText(stringFromJNI());
    }


    public void callJavaMethodFromNative(View view) {
        getTheAnswer();
        callback();
        printSumOfArray();
        Log.d(LOG_TAGS, "Variable Value before Native Call Int: " + si+" String: "+s);
        resultTextBuffer.append("Static Variable(Int, String) Value before native access is :"
                +si+", "+s+"\n\n");
        accessJavaVariable();
        Log.d(LOG_TAGS, "Variable Value after Native Call Int: " + si+" String: "+s);
        resultTextBuffer.append("Static Variable(Int, String) Value after native access is :"
                +si+", "+s+"\n\n");

        Log.d(LOG_TAGS, "Variable Value before Native Call String instanceField: "
                +instanceField);
        resultTextBuffer.append("Instance Variable Value before native access is :"
                +instanceField+"\n\n");
        AccessJavaInstanceField();
        Log.d(LOG_TAGS, "Variable Value after Native Call String instanceField: "
                +instanceField);
        resultTextBuffer.append("Instance Variable Value after native access is :"
                +instanceField+"\n\n");
        resultTextBuffer.append("After native access POJO/Getter/Setter class Dummy Value is :"
                +dummyF.value+"\n\n");

        resultText.setText(resultTextBuffer);
    }


    public static int getNumberFromCPP(boolean bool) {
        int result = 0;
        if(bool)
        {
            result = 45;
        }else {
            result = 10;
        }
        resultTextBuffer.append("Accessing Java Static Method From Native " +
                "getNumberFromCPP(false) :o/p: " +result +"\n\n");
        return result;
    }

    public static void printNum(int i) {
        Log.d(LOG_TAGS, "Got int from C++: " + i);
        resultTextBuffer.append("java Method: static void printNum(int i) " +
                "accessed from Native: "+i+"\n\n");
    }

    public void printFloat(float i) {
        Log.d(LOG_TAGS, "Got float from C++: " + i);
        resultTextBuffer.append("java Method: void printFloat(float i) " +
                "accessed from Native: "+i+"\n\n");
    }

    public void printSumOfArray()
    {
        int arr[] = new int [11];
        for (int i = 0; i < 11; i++)
            arr[i] = i;
        int sum = sumArray(arr);
        resultTextBuffer.append("java Method: void printSumOfArray() " +
                "accessed from Native Array Sum value: "+sum+"\n\n");
        Log.d(LOG_TAGS, "Got Array Sum from C++: " + sum);
    }


    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native void getTheAnswer();
    public native void callback();
    private native int sumArray(int arr[]);
    private native void accessJavaVariable();
    private native void AccessJavaInstanceField();


}