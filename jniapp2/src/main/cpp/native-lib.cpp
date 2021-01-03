#include <jni.h>
#include <string>
#include <android/log.h>
#define APPNAME "JniApp2"

extern "C" JNIEXPORT jstring JNICALL
Java_com_saurabh_jni_jniapp2_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "Saurabh Sharma");
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT void JNICALL
Java_com_saurabh_jni_jniapp2_MainActivity_getTheAnswer(JNIEnv *env, jobject thiz)
{
    jboolean localBool = JNI_TRUE;
    // Find the Java class - provide package ('.' replaced to '/') and class name
    jclass jniTestClass = env->FindClass("com/saurabh/jni/jniapp2/MainActivity");

    // Find the Java method - provide parameters inside () and return value (see table below for an explanation of how to encode them)
    jmethodID getAnswerMethod = env->GetStaticMethodID(jniTestClass, "getNumberFromCPP", "(Z)I");
    // Calling the method
    env->CallStaticIntMethod(jniTestClass, getAnswerMethod, (jboolean)localBool);
}

extern "C" JNIEXPORT void JNICALL
Java_com_saurabh_jni_jniapp2_MainActivity_callback(JNIEnv *env, jobject jthis) {
    jclass thisClass = env->GetObjectClass(jthis);

    jmethodID printFloat = env->GetMethodID(thisClass, "printFloat", "(F)V");
    if (NULL == printFloat)
        return;
    env->CallVoidMethod(jthis, printFloat, 5.22f);

    jmethodID staticPrintInt = env->GetStaticMethodID(thisClass, "printNum", "(I)V");
    if (NULL == staticPrintInt)
        return;
    env->CallStaticVoidMethod(thisClass,staticPrintInt, 17);
}

extern "C" JNIEXPORT jint JNICALL
Java_com_saurabh_jni_jniapp2_MainActivity_sumArray(JNIEnv *env, jobject obj, jintArray arr)
{
    jsize len = env->GetArrayLength(arr);
    int i, sum = 0;
    jint *body = env->GetIntArrayElements(arr, 0);
    for (i=0; i<len; i++) {
        sum += body[i];
    }
    env->ReleaseIntArrayElements(arr, body, 0);
    __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "Array Sum value: %d",sum);
    return sum;
}

extern "C" JNIEXPORT void JNICALL
Java_com_saurabh_jni_jniapp2_MainActivity_accessJavaVariable(JNIEnv *env, jobject obj)
{
    jclass cls = env->GetObjectClass(obj);
    jfieldID fid;
    jstring jstr;
    const char *str;
    jint si;
    printf("In C:\n");

    fid = env->GetStaticFieldID(cls, "si", "I");
    if (fid == 0) {
        return;
    }
    si = env->GetStaticIntField(cls, fid);
    //printf("  FieldAccess.Integer = %d\n", si);
    __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "FieldAccess.Integer: %d",si);
    env->SetStaticIntField(cls, fid, 200);

    fid = env->GetFieldID(cls, "s", "Ljava/lang/String;");
    if (fid == 0) {
        return;
    }
    jstr = static_cast<jstring>(env->GetObjectField(obj, fid));
    str = env->GetStringUTFChars(jstr, 0);
    //printf("  FieldAccess.String = \"%s\"\n", str);
    __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "FieldAccess.String: %s",str);
    env->ReleaseStringUTFChars(jstr, str);

    jstr = env->NewStringUTF("SaurabhSharma123K");
    env->SetObjectField(obj, fid, jstr);
}
extern "C" JNIEXPORT void JNICALL
Java_com_saurabh_jni_jniapp2_MainActivity_AccessJavaInstanceField(JNIEnv *env, jobject obj)
{
    jfieldID intFID, strFID, intArrFID, dummyFID;
    jclass cls = env->GetObjectClass(obj);

    strFID = env->GetFieldID(cls, "instanceField", "Ljava/lang/String;");
    //get the string field and read the content
    jobject astr = env->GetObjectField(obj, strFID);
    const char* str = env->GetStringUTFChars(static_cast<jstring>(astr), NULL);
    if (str == NULL) {
        __android_log_print(ANDROID_LOG_INFO, APPNAME, "failed GetStringUTFChars");
    }
    __android_log_print(ANDROID_LOG_INFO, APPNAME, "strF: %s", str);
    env->ReleaseStringUTFChars(static_cast<jstring>(astr), str);
    //set the string field to a new string
    jstring newStr = env->NewStringUTF("hello from native 2");
    env->SetObjectField(obj, strFID, newStr);

    dummyFID = env->GetFieldID(cls, "dummyF", "Lcom/saurabh/jni/jniapp2/Dummy;");
    //get the Dummy object field
    jobject adummy = env->GetObjectField(obj, dummyFID);
    jclass dummyCls = env->FindClass("com/saurabh/jni/jniapp2/Dummy");
    __android_log_print(ANDROID_LOG_INFO, APPNAME, "dummyF is instance of dummyCls: %d",
            env->IsInstanceOf(adummy, dummyCls));
    jfieldID dummyValueFID = env->GetFieldID(dummyCls, "value", "I");
    jint dummyValue = env->GetIntField(adummy, dummyValueFID);
    __android_log_print(ANDROID_LOG_INFO, APPNAME, "dummyF value: %d", dummyValue);
    //set the Dummy object field to a newly created one
    jmethodID dummyConstructor = env->GetMethodID(dummyCls, "<init>","(I)V");
    jobject newDummy = env->NewObject(dummyCls, dummyConstructor, 200);
    env->SetObjectField(obj, dummyFID, newDummy);

}
