package com.imooic.openglnativedemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.imooic.opengl.NativeOpengl;
import com.imooic.opengl.WlSurfaceView;
import com.imooic.openglnativedemo.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

private ActivityMainBinding binding;

    private WlSurfaceView wlSurfaceView;
    private NativeOpengl nativeOpengl;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

     binding = ActivityMainBinding.inflate(getLayoutInflater());
     setContentView(binding.getRoot());
        binding.wlsurfaceview.setNativeOpengl(nativeOpengl = new NativeOpengl());
    }


}