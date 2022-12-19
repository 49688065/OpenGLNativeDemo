package com.imooic.openglnativedemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;
import com.imooic.openglnativedemo.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

     binding = ActivityMainBinding.inflate(getLayoutInflater());
     setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI());
    }

    /**
     * A native method that is implemented by the 'openglnativedemo' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    // Used to load the 'openglnativedemo' library on application startup.
    static {
        System.loadLibrary("openglnativedemo");
    }
}