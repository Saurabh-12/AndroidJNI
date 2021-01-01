#include <jni.h>
#include <string>
#include <android/log.h>
#define APPNAME "JniApp2"

extern "C" JNIEXPORT jstring JNICALL
Java_com_saurabh_jni_jniapp3_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "Saurabh Sharma");
    return env->NewStringUTF(hello.c_str());
}
