package com.imooic.openglnativedemo;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

import com.imooic.opengl.NativeOpengl;
import com.imooic.opengl.WlSurfaceView;

import java.io.File;
import java.io.FileInputStream;

public class YUVplayer extends AppCompatActivity {

    private WlSurfaceView wlSurfaceView;
    private NativeOpengl nativeOpengl;

    private FileInputStream fis;

    private boolean isExit = true;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_yuvplayer);
        wlSurfaceView = findViewById(R.id.wlsurfaceview);
        nativeOpengl = new NativeOpengl();
        wlSurfaceView.setNativeOpengl(nativeOpengl);
        if (!checkPermissions(new String[]{Manifest.permission.READ_EXTERNAL_STORAGE})){
            requestPermission(new String[]{Manifest.permission.READ_EXTERNAL_STORAGE,Manifest.permission.WRITE_EXTERNAL_STORAGE},33);
        }
    }
    protected boolean checkPermissions(String[] permissions) {
        if (Build.VERSION.SDK_INT > Build.VERSION_CODES.M) {
            for (int i = 0; i < permissions.length; i++) {
                if (checkSelfPermission(permissions[i]) == PackageManager.PERMISSION_DENIED) {
                    return false;
                }
            }
        }
        return true;
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

    }

    //动态权限
    protected void requestPermission(String[] permissions, int requestCode) {
        if (Build.VERSION.SDK_INT > Build.VERSION_CODES.M) {
            requestPermissions(permissions, requestCode);
        }
    }


    public void play(View view){
        if(isExit){
            isExit = false;
            new Thread(new Runnable() {
                @Override
                public void run() {
                    int w = 176;
                    int h = 144;
                    try{
                        fis = new FileInputStream(new File("/mnt/sdcard/Movies/blr.yuv"));
                        byte []y = new byte[w *h];
                        byte []u = new byte[w * h /4];
                        byte []v = new byte[w*h/4];
                        while (true){
                            if (isExit){
                                break;
                            }

                            int ysize = fis.read(y);
                            int usize = fis.read(u);
                            int vsize = fis.read(v);

                            if (ysize >0 && usize >0 && vsize>0){
                                nativeOpengl.setYuvData(y,u,v,w,h);
                                Thread.sleep(10);
                            }else {
                                isExit =true;
                            }
                        }
                    }catch (Exception e){
                     e.printStackTrace();
                    }
                }
            }){}.start();
        }
    }

    public void stop(View view){
        isExit = true;
    }
}
