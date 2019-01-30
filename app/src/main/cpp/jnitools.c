#include <jni.h>
#include <android/log.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef LOG_TAG
#define LOG_TAG "JNI"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG ,__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG ,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOG_TAG ,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG ,__VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,LOG_TAG ,__VA_ARGS__)
#endif

// JNI层 静态注册函数声明
JNIEXPORT void JNICALL
Java_com_bob_jnilearn_JNIApi_test(JNIEnv *env, jclass clazz) {

    // TODO JNI Layer invoke Java Layer method.

    // 查找Java层的类
    jclass clz = (*env)->FindClass(env, "com/bob/jnilearn/JNICallback");

    // 获取Java层静态方法ID
    // (env, java层的类, 方法名称, 方法签名)
    jmethodID processInJAVA = (*env)->GetStaticMethodID(env, clz, "processInJAVA",
                                                        "(Ljava/lang/String;)Ljava/lang/String;");

    jstring arg = (*env)->NewStringUTF(env, "invoke_from_C_FUCK_FUCK");

    // JNI层调用Java层的静态方法 有一个参数的静态方法
    // return val from java layer method return val
    jstring res = (*env)->CallStaticObjectMethod(env, clz, processInJAVA, arg);

    // jstring convert char*
    // Log无法直接输出jstring格式
    const char *nativeString = (*env)->GetStringUTFChars(env, res, 0);
    LOGD("jni receive native string is %s", nativeString);
}

JNIEXPORT void JNICALL
Java_com_bob_jnilearn_JNIApi_toastInC(JNIEnv *env, jclass clazz, jobject context, jstring str) {
    LOGD("JNI enter into toastInC method");

    // Toast.makeText(this, "xxx", Toast.LENGTH_SHORT).show();

    // C层反调Android直接Toast
    jclass targetClz = (*env)->FindClass(env, "android/widget/Toast");
    jmethodID makeTextMid = (*env)->GetStaticMethodID(env, targetClz, "makeText",
                                                      "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;");
    jmethodID showMid = (*env)->GetMethodID(env, targetClz, "show", "()V");

    jobject toastObj = (*env)->CallStaticObjectMethod(env, targetClz, makeTextMid, context, str, 0);
    (*env)->CallVoidMethod(env, toastObj, showMid);
}

JNIEXPORT void JNICALL
Java_com_bob_jnilearn_JNIApi_getPkgName(JNIEnv *env, jclass clazz, jobject activity){
    LOGD("JNI enter into getPkgName method");

    // Get java context class
    jclass activity_java_clz = (*env)->GetObjectClass(env, activity);

    jmethodID get_pkg_name_mid = (*env)->GetMethodID(env, activity_java_clz, "getPackageName", "()Ljava/lang/String;");

    jstring pkg_name = (*env)->CallObjectMethod(env, activity, get_pkg_name_mid);

    const char *nativeString = (*env)->GetStringUTFChars(env, pkg_name, 0);
    LOGD("jni get application package name is: %s", nativeString);
}

// JNI层 使用动态注册函数声明
jstring say_hello(JNIEnv *env, jclass clazz, jint flag) {
    LOGD("enter into JNI method: say_hello");

    jstring ret = NULL;
    if (flag > 0) {
        ret = (*env)->NewStringUTF(env, "大于零");
    } else {
        ret = (*env)->NewStringUTF(env, "小于零");
    }

    return ret;
}

void callback_android_toast(JNIEnv *env, jclass clazz, jobject context, jstring str) {
    LOGD("enter into JNI method: callback_android_toast");

    jclass clz = (*env)->FindClass(env, "com/bob/jnilearn/JNICallback");
    jmethodID showToastMid = (*env)->GetStaticMethodID(env, clz, "showToast",
                                                       "(Landroid/content/Context;Ljava/lang/String;)V");

    (*env)->CallStaticVoidMethod(env, clz, showToastMid, context, str);
}


// JNI 初始化函数
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGD("enter jni_onload");

    JNIEnv *env = NULL;
    jint result = -1;

    // JNI 版本判定 执行环境是否符合初始化条件
    if ((*vm)->GetEnv(vm, (void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return result;
    }

    // 函数映射表
    const JNINativeMethod method[] = {
            {"getResult",            "(I)Ljava/lang/String;",                          (void *) say_hello},

            {"showToastInvokeFromC", "(Landroid/content/Context;Ljava/lang/String;)V", (void *) callback_android_toast}
            // java方法名, java层方法签名, jni层函数名称
    };

    // 查找java层的类
    jclass jClassName = (*env)->FindClass(env, "com/bob/jnilearn/JNIApi");
    // JNI层注册java层方法与JNI中方法的映射关系
    jint ret = (*env)->RegisterNatives(env, jClassName, method, 2);
    // 参数说明: evn, java层方法所在的类, 映射表, 方法数量

    if (ret != JNI_OK) {
        LOGD("jni_register Error");
        return -1;
    }

    return JNI_VERSION_1_6; // 使用该JNI版本特性, 标准初始化流程需生命使用的JNI版本
}





