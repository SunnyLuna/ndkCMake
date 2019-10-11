#include <jni.h>
#include <string>

#define ZJFUN(name)Java_com_decard_myndkcmake_ndkPackage_##name

extern "C" JNIEXPORT jstring JNICALL
ZJFUN(NdkMethod_00024Companion_stringFromJNI)(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
