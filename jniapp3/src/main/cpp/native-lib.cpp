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

        env->ExceptionDescribe(); //this does not clear the exception
        jthrowable exce = env->ExceptionOccurred();
        __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "Exception from C: %s",exce);
        env->ExceptionClear(); //clear the exception, so we can proceed

        newExcCls = env->FindClass( "java/lang/IllegalArgumentException");
        if (newExcCls == 0) { /* Unable to find the new exception class, give up. */
            return;
        }
        env->ThrowNew(newExcCls, "thrown from C code");
    }

}

extern "C" JNIEXPORT void JNICALL
Java_com_saurabh_jni_jniapp3_MainActivity_ExceptionDemo(JNIEnv *env, jobject pObj) {
//	jboolean ExceptionCheck(JNIEnv *env);
//	jthrowable ExceptionOccurred(JNIEnv *env);
    //if no exception pending
    jboolean ifExceptionPending = env ->ExceptionCheck();
    __android_log_print(ANDROID_LOG_INFO, "ExceptionCheckDemo",
            "ExceptionCheck: %d", ifExceptionPending);
    jthrowable exception = env->ExceptionOccurred();
    __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "API_2: Exception from C: %s",exception);
    __android_log_print(ANDROID_LOG_INFO, "ExceptionCheckDemo",
                        "ExceptionOccurred returned NULL? : %d",
                        env->IsSameObject(exception, NULL));

    //search for a class which are not available, which will cause an exception
    env->FindClass("java/lang/XXYY");
    //use ExceptionCheck to check
    ifExceptionPending = env->ExceptionCheck();
    __android_log_print(ANDROID_LOG_INFO, "ExceptionCheckDemo",
            "ExceptionCheck after finding non-existing class: %d", ifExceptionPending);

    env->ExceptionClear();	//clear the exception, so we can proceed
    ifExceptionPending =env->ExceptionCheck();
    __android_log_print(ANDROID_LOG_INFO, "ExceptionCheckDemo",
            "ExceptionCheck after clear: %d", ifExceptionPending);

    //throw a java.lang.NullPointerException using ThrowNew
    jclass cls = env->FindClass( "java/lang/NullPointerException");
    jint st = env->ThrowNew(cls, "throw null pointer exception");
    if (st == 0) {
        __android_log_print(ANDROID_LOG_INFO, "ExceptionCheckDemo",
                "null pointer exception thrown using ThrowNew");
        env->DeleteLocalRef(cls);
    }

    //use ExceptionOccurred to check
    jthrowable exObj = env->ExceptionOccurred();
    if (exObj == NULL) {
        __android_log_print(ANDROID_LOG_INFO, "ExceptionCheckDemo", "no exception");
    } else {
        __android_log_print(ANDROID_LOG_INFO, "ExceptionCheckDemo",
                "there's pending exception, call ExceptionDescribe");
        env->ExceptionDescribe();	//this does not clear the exception
        ifExceptionPending = env->ExceptionCheck();
        __android_log_print(ANDROID_LOG_INFO, "ExceptionCheckDemo",
                "ExceptionCheck after ExceptionDescribe: %d", ifExceptionPending);
        env->ExceptionClear();		//clear the exception, so we can proceed
        ifExceptionPending =env->ExceptionCheck();
        __android_log_print(ANDROID_LOG_INFO, "ExceptionCheckDemo",
                "ExceptionCheck after clear: %d", ifExceptionPending);
        env->DeleteLocalRef(exObj);
    }

    //throw a java.lang.RuntimeException using Throw
    cls = env->FindClass("java/lang/RuntimeException");
    jmethodID exConstructor = env->GetMethodID(cls, "<init>","(Ljava/lang/String;)V");
    //passing UTF-8 string directly to exConstructor won't work because it expects jstring
    //jthrowable rtExObj = (*pEnv)->NewObject(pEnv, reCls, exConstructor, "throw runtime exception");
    jstring msg = env->NewStringUTF("throw runtime exception");
    exObj = static_cast<jthrowable>(env->NewObject(cls, exConstructor, msg));
    env->DeleteLocalRef(msg);
    if (exObj == NULL) {
        __android_log_print(ANDROID_LOG_INFO, "ExceptionCheckDemo",
                "create RuntimeException failed");
    } else {
        jint st = env->Throw(exObj);
        if (st == 0) {
            __android_log_print(ANDROID_LOG_INFO, "ExceptionCheckDemo",
                    "exception thrown using Throw");
            env->DeleteLocalRef(cls);
            env->DeleteLocalRef(exObj);
        }
        //do not clear the exception, let the caller handle it
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_saurabh_jni_jniapp3_MainActivity_FatalErrorDemo(JNIEnv *env, jobject pObj) {
    env->FatalError("fatal error");
    __android_log_print(ANDROID_LOG_INFO, "FatalErrorDemo","after calling FatalError");
}

//jboolean ExceptionCheck(JNIEnv *env);
//Determines if an exception has been thrown. The exception stays thrown until either the
//native code calls ExceptionClear, or the caller of the native method handles the exception.
//Returns the JNI_TRUE if there is a pending exception, or
//JNI_FALSE if there is no pending exception.

//void ExceptionClear(JNIEnv *env);
//Clears any pending exception that is currently being thrown in the current thread.
//If no exception is currently being thrown, this function has no effect.
//This function has no effect on exceptions pending on other threads.

//void ExceptionDescribe(JNIEnv *env);
//Prints the pending exception and a backtrace of the stack to the system error-reporting
//channel System.out.err. This is a convenience routine provided for debugging.

//jthrowable ExceptionOccurred(JNIEnv *env);
//Determines if an exception is pending in the current thread. The exception stays pending until either
//the native code calls ExceptionClear, or the caller of the native method handles the exception.

//void FatalError(JNIEnv *env, const char *msg);
//Raises a fatal error and does not expect the virtual machine implementation to recover.
//Prints the message in a system debugging channel, such as stderr, and terminates
//the virtual machine instance. This function does not return.

//jint Throw(JNIEnv *env, jthrowable obj);
//Causes a java.lang.Throwable object to be thrown. A thrown exception will be pending in the current thread,
//but does not immediately disrupt native code execution.
//Returns zero on success; otherwise, returns a negative value
//if the specified exception cannot be thrown.

//jint ThrowNew(JNIEnv *env, jclass clazz, const char *message);
//Constructs an exception object from the specified class with the message specified by message
//and causes that exception to be thrown.
