package com.saurabh.jni.example;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    Button btnJNI, btnJNIStringArray;
    EditText FirstName_et,LastName_et;
    ListView listView;
    ArrayAdapter adapter;
    String FirstName = "Saurabh";
    String LastName = "Sharma";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        btnJNI = findViewById(R.id.btnJni);
        FirstName_et = findViewById(R.id.first_name_et);
        LastName_et = findViewById(R.id.last_name_et);
        listView = (ListView) findViewById(R.id.my_list_view);

        btnJNIStringArray = findViewById(R.id.btnJniStringArray);
        btnJNI.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                FirstName = FirstName_et.getText().toString().trim();
                LastName = LastName_et.getText().toString().trim();
                if (FirstName.isEmpty() || LastName.isEmpty()) {
                    FirstName = "Saurabh ";
                    LastName = "Sharma";
                }
                String result = sendYourName(FirstName, LastName);
                Toast.makeText(getApplicationContext(), "Result from JNI is "
                        + result, Toast.LENGTH_LONG).show();
            }
        });


        btnJNIStringArray.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String[] strings = stringArrayFromJNI();
                adapter= new ArrayAdapter<String>(MainActivity.this,
                        R.layout.activity_listview, strings);
                listView.setAdapter(adapter);
                Toast.makeText(getApplicationContext(), "First element is "+strings[0],
                        Toast.LENGTH_LONG).show();

            }
        });

    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native String sendYourName(String firstName, String lastName);
    public native String[] stringArrayFromJNI();
}