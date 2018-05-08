package com.nativedemo.JniLib;

import com.nativedemo.entity.NoiseInfo;

public class JniDemo {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native int sum(int[] num);
    public native int sumStr(String[] num);

    public native void getNoiseInfoJNI(NoiseInfo[][] mNoiseInfos);
}
