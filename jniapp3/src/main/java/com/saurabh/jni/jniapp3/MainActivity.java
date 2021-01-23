package com.saurabh.jni.jniapp3;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private TextView exceptionDemo;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        exceptionDemo = findViewById(R.id.exception_demo_text);
        tv.setText(stringFromJNI());

        //handleExceptionFromNative();
       callExceptionDemo();
        //callFatalErrorDemo();

    }

    private void NPETest() throws NullPointerException {
        throw new NullPointerException("Exception test result: "+"thrown in CatchThrow.callback");
    }

    private void callExceptionDemo() {
        try {
            ExceptionDemo();
        } catch (RuntimeException e) {
            String msg = e.getMessage();
            exceptionDemo.setText("Exception test result: "+msg);
        }
    }

    private void callFatalErrorDemo() {
        FatalErrorDemo();
        exceptionDemo.setText("Exception test result: "+"after calling FatalErrorDemo");
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    private native void handleExceptionFromNative() throws IllegalArgumentException;
    private native void ExceptionDemo();
    private native void FatalErrorDemo();
}