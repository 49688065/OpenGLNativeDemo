package com.imooic.openglnativedemo;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import com.imooic.opengl.NativeOpengl;
import com.imooic.opengl.WlSurfaceView;
import com.imooic.openglnativedemo.databinding.ActivityMainBinding;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    private ActivityMainBinding binding;

    private WlSurfaceView wlSurfaceView;
    private NativeOpengl nativeOpengl;

    private List<Integer> imgs = new ArrayList<>();
    private int index =-1;
    byte[] pixels;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

     binding = ActivityMainBinding.inflate(getLayoutInflater());
     setContentView(binding.getRoot());
        binding.wlsurfaceview.setNativeOpengl(nativeOpengl = new NativeOpengl());

        imgs.add(R.drawable.mingren);
        imgs.add(R.drawable.img_1);
        imgs.add(R.drawable.img_2);
        imgs.add(R.drawable.img_3);

        binding.wlsurfaceview.setOnSurfaceListener(new WlSurfaceView.OnSurfaceListener() {
            @Override
            public void init() {
                final Bitmap bitmap = BitmapFactory.decodeResource(getResources(),R.drawable.mingren);
                ByteBuffer fcbuffer = ByteBuffer.allocate(bitmap.getHeight()*bitmap.getWidth()*4);
                bitmap.copyPixelsToBuffer(fcbuffer);
                fcbuffer.flip();
                byte[] pixels = fcbuffer.array();
                nativeOpengl.imgData(bitmap.getWidth(),bitmap.getHeight(),pixels.length,pixels);

            }
        });
      }

    public  void  changeTexture(View view){
        readPliex();
    }

    private void readPliex() {
        final Bitmap bitmap = BitmapFactory.decodeResource(getResources(),getImgeIds());
        ByteBuffer fcbuffer = ByteBuffer.allocate(bitmap.getHeight()*bitmap.getWidth()*4);
        bitmap.copyPixelsToBuffer(fcbuffer);
        fcbuffer.flip();
        pixels =fcbuffer.array();
        nativeOpengl.imgData(bitmap.getWidth(),bitmap.getHeight(),pixels.length,pixels);
    }

    public void changeFilter(View view) {
        if (nativeOpengl != null){
            nativeOpengl.surfaceChangeFilter();
        }
    }

    public int getImgeIds() {
        index ++;
        if (index>imgs.size()-1){
            index = 0;
        }
        return imgs.get(index);
    }
}