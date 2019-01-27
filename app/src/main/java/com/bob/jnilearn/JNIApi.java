package com.bob.jnilearn;

import android.app.Activity;
import android.content.Context;

/**
 * JNI 入口
 */

public class JNIApi {

    static {
        System.loadLibrary("demo");
    }

    // JNI调用 静态注册映射关系 常见
    public static native void test();

    public static native void toastInC(Context context, String str);

    public static native void getPkgName(Activity activity);

    // JNI调用 动态注册映射关系 高级
    public static native String getResult(int flag);

    public static native void showToastInvokeFromC(Context context, String str);
}
