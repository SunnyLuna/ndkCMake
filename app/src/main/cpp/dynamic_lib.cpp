// jni头文件 
#include <jni.h>

#include <cassert>
#include <cstdlib>
#include <iostream>

using namespace std;

JavaVM *javaVm;

//native 方法实现
jint get_random_num() {
    return rand();
}

jstring say_hello() {
    std::string hello = "嗯 动态注册";
    if (javaVm == NULL) {
        return NULL;
    }
    int status;
    JNIEnv *env = NULL;
    bool isAttach = false;
    status = javaVm->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (status != JNI_OK) {
        status = javaVm->AttachCurrentThread(&env, NULL);
        if (status < 0) {
            return NULL;
        }
        isAttach = true;
    }
    if (isAttach) {
        javaVm->DetachCurrentThread();
    }
    return env->NewStringUTF(hello.c_str());
}

/*需要注册的函数列表，放在JNINativeMethod 类型的数组中，
以后如果需要增加函数，只需在这里添加就行了
参数：
1.java中用native关键字声明的函数名
2.签名（传进来参数类型和返回值类型的说明） 
3.C/C++中对应函数的函数名（地址）
*/
static JNINativeMethod getMethods[] = {
        {"getRandomNum", "()I", (void *) get_random_num},
        {"sayHello",     "()Ljava/lang/String;", (void *) say_hello},
};

//此函数通过调用RegisterNatives方法来注册我们的函数
static int registerNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *getMethods,
                                 int methodsNum) {
    jclass clazz;
    //找到声明native方法的类
    clazz = env->FindClass(className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    //注册函数 参数：java类 所要注册的函数数组 注册函数的个数
    if (env->RegisterNatives(clazz, getMethods, methodsNum) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

static int registerNatives(JNIEnv *env) {
    //指定类的路径，通过FindClass 方法来找到对应的类
    const char *className = "com/decard/myndkcmake/ndkPackage/NativeMethod1$Companion";
    return registerNativeMethods(env, className, getMethods,
                                 sizeof(getMethods) / sizeof(getMethods[0]));
}


//回调函数
JNIEXPORT

jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    javaVm = vm;
    JNIEnv *env = NULL;
    //获取JNIEnv
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    assert(env != NULL);
    //注册函数 registerNatives ->registerNativeMethods ->env->RegisterNatives
    if (!registerNatives(env)) {
        return -1;
    }
    //返回jni 的版本 
    return JNI_VERSION_1_6;
}