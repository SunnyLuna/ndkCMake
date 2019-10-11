package com.decard.myndkcmake.ndkPackage

class NativeMethod1 {

    companion object {
        init {
            System.loadLibrary("dynamic_lib")
        }

        external fun getRandomNum(): Int
        external fun sayHello(): String
    }


}