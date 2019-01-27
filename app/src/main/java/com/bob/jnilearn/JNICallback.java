package com.bob.jnilearn;

import android.content.Context;
import android.util.Log;
import android.widget.Toast;

/**
 * JNI Callback 反向调用Android层代码
 */

public class JNICallback {

    private static final String TAG = "JNICallback";

    public static String processInJAVA(String arg) {
        Log.wtf(TAG, "JNICallback into processInJAVA....");
        return String.format("Java layer add some little process with: %s", arg);
    }

    public static void showToast(Context context, String str){
        Log.wtf(TAG, "JNICallback into showToast....");
        Toast.makeText(context, str, Toast.LENGTH_SHORT).show();
    }
}
