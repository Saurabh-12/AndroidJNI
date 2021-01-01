#include <jni.h>
#include <string>
#include <android/log.h>

#define APPNAME "JniApp3"

extern "C" JNIEXPORT jstring JNICALL
Java_com_saurabh_jni_jniapp3_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "Saurabh Sharma");
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT void JNICALL
Java_com_saurabh_jni_jniapp3_MainActivity_handleExceptionFromNative(JNIEnv *env, jobject obj)
{
    jclass cls = env->GetObjectClass(obj);
    jmethodID mid = env->GetMethodID(cls, "NPETest", "()V");
    jthrowable exc;
    if (mid == 0) {
        return;
    }
    env->CallVoidMethod(obj, mid);
    exc = env->ExceptionOccurred();
    if (exc) {
        /* We don't do much with the exception, except that we print a
           debug message using ExceptionDescribe, clear it, and throw
           a new exception. */
        jclass newExcCls;

        env->ExceptionDescribe();
        env->ExceptionClear();

        newExcCls = env->FindClass( "java/lang/IllegalArgumentException");
        if (newExcCls == 0) { /* Unable to find the new exception class, give up. */
            return;
        }
        env->ThrowNew(newExcCls, "thrown from C code");
    }
}
