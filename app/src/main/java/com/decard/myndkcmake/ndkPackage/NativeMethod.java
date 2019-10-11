package com.decard.myndkcmake.ndkPackage;

public class NativeMethod {

    static {
        System.loadLibrary("dynamic_lib");
    }

    public native static int getRandomNum();
}
