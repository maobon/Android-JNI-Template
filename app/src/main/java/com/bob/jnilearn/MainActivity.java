package com.bob.jnilearn;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

//        final TextView tv = findViewById(R.id.sample_text);
//        tv.setText(JNIApi.getResult(-1));
//
//        JNIApi.test();
//        JNIApi.showToastInvokeFromC(this, "Hello CALLBACK");
//        JNIApi.toastInC(this, "HELLO");

        JNIApi.getPkgName(this);
    }
}
