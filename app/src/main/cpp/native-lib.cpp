#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_terrence_heartndk_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_terrence_heartndk_MainActivity_pathFromJNI(
        JNIEnv* env,
        jobject, /* this */
        jstring path
        ) {
        //const char* string = path;
        const char *name = env->GetStringUTFChars(path, 0);
        std::string str = name;
    //std::string hello = "Hello from C++";
    return env->NewStringUTF(str.c_str());
}