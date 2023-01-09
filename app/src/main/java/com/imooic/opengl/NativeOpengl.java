package com.imooic.opengl;

import android.view.Surface;

public class NativeOpengl {

    static {
        System.loadLibrary("openglnativedemo");
    }

    public native void surfaceCreate(Surface surface);

    public native void surfaceChange(int width,int height);

    public native void imgData(int w,int h,int length,byte[] data);

    public native void surfaceDestroy();
}
