package com.imooic.openglnativedemo;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.imooic.opengl.NativeOpengl;
import com.imooic.opengl.WlSurfaceView;
import com.imooic.openglnativedemo.databinding.ActivityMainBinding;

import java.nio.ByteBuffer;

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

        final Bitmap bitmap = BitmapFactory.decodeResource(getResources(),R.drawable.mingren);
        ByteBuffer fcbuffer = ByteBuffer.allocate(bitmap.getHeight()*bitmap.getWidth()*4);
        bitmap.copyPixelsToBuffer(fcbuffer);
        fcbuffer.flip();
        byte[] pixels = fcbuffer.array();
        nativeOpengl.imgData(bitmap.getWidth(),bitmap.getHeight(),pixels.length,pixels);
    }


}