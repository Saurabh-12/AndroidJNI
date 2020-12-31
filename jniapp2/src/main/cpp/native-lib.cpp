#include <jni.h>
#include <string>
#include <android/log.h>


extern "C" JNIEXPORT jstring JNICALL
Java_com_saurabh_jni_jniapp2_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jint JNICALL
Java_com_saurabh_jni_jniapp2_MainActivity_getTheAnswer(JNIEnv *env, jobject thiz,jboolean bools)
{
    // Find the Java class - provide package ('.' replaced to '/') and class name
    jclass jniTestClass = env->FindClass("com/saurabh/jni/jniapp2/MainActivity");

    // Find the Java method - provide parameters inside () and return value (see table below for an explanation of how to encode them)
    jmethodID getAnswerMethod = env->GetStaticMethodID(jniTestClass, "getNumberFromCPP", "(Z)I");

    // Calling the method
    return (int)env->CallStaticIntMethod(jniTestClass, getAnswerMethod, (jboolean)bools);
}

extern "C" JNIEXPORT void JNICALL
Java_com_saurabh_jni_jniapp2_MainActivity_callback(JNIEnv *env, jobject jthis) {
    jclass thisClass = env->GetObjectClass(jthis);

    jmethodID printFloat = env->GetMethodID(thisClass, "printFloat", "(F)V");
    if (NULL == printFloat)
        return;
    env->CallVoidMethod(jthis, printFloat, 5.221);

    jmethodID staticPrintInt = env->GetStaticMethodID(thisClass, "printNum", "(I)V");
    if (NULL == staticPrintInt)
        return;
    env->CallStaticVoidMethod(jthis, staticPrintInt, 17);
}
