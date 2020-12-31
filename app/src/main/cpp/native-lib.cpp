#include <jni.h>
#include <string>
#include <android/log.h>


extern "C" JNIEXPORT jstring JNICALL
Java_com_saurabh_jni_example_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_saurabh_jni_example_MainActivity_sendYourName(JNIEnv *env, jobject thiz,
                                                       jstring first_name, jstring last_name) {
    char returnString[20];
    const char *fN = env->GetStringUTFChars(first_name, NULL);
    const char *lN = env->GetStringUTFChars(last_name, NULL);

    strcpy(returnString,fN); // copy string one into the result.
    strcat(returnString,lN); // append string two to the result.

    env->ReleaseStringUTFChars(first_name, fN);
    env->ReleaseStringUTFChars(last_name, lN);

    __android_log_write(ANDROID_LOG_DEBUG, "SKS_JNI_1", returnString);

    return env->NewStringUTF(returnString);
}

extern "C" JNIEXPORT jobjectArray JNICALL
Java_com_saurabh_jni_example_MainActivity_stringArrayFromJNI(JNIEnv *env, jobject thiz) {

    char *progrmLang[]={"Java",
                  "Android",
                  "Kotlin",
                  "Swift",
                  "Django",
                  "SQL",
                  "Springs"};

    jstring str;
    jobjectArray lang = 0;
    jsize len = 7;
    int i;

    lang = env->NewObjectArray(len,
            env->FindClass("java/lang/String"),0);

    for(i=0;i<7;i++)
    {
        str = env->NewStringUTF(progrmLang[i]);
        __android_log_write(ANDROID_LOG_DEBUG, "SKS_JNI_2", progrmLang[i]);
        env->SetObjectArrayElement(lang,i,str);
    }

    return lang;
}