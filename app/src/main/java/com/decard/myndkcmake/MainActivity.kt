package com.decard.myndkcmake

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.decard.myndkcmake.ndkPackage.NativeMethod1
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
//        sample_text.text = NdkMethod.stringFromJNI()
        sample_text.text = NativeMethod1.sayHello()
    }

}
