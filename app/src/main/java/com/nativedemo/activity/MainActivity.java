package com.nativedemo.activity;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.nativedemo.JniLib.JniDemo;
import com.nativedemo.R;
import com.nativedemo.entity.NoiseInfo;

public class MainActivity extends AppCompatActivity {

    JniDemo mJniDemo;
    TextView tv;
    static int a[] = new int[] { 1, 2, 3, 4, 5 };
    static String str[] = new String[] { "we", "are", "friends" };
    private NoiseInfo[][] mNoiseInfos;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mJniDemo = new JniDemo();
        // Example of a call to a native method
        tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(mJniDemo.stringFromJNI());
        mNoiseInfos = new NoiseInfo[12][10];
        mJniDemo.getNoiseInfoJNI(mNoiseInfos);
        Log.i("aaaa","sum = " + mJniDemo.sum(a));
        Log.i("aaaa","sum = " + mJniDemo.sumStr(str));
        for (int i = 0; i < mNoiseInfos.length; i ++){
            for (int j = 0; j < 10; j ++){
                Log.i("aaaa", "onCreate: mNoiseInfo j = " + j + " i ="
                        + i + " = " + mNoiseInfos[i][j]);
            }
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }
}
