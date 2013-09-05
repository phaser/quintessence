/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package ro.qui.apps;

import android.app.Activity;
import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import ro.qui.apps.LoadLibraries;
import ro.qui.apps.JNIGameInterface;
import android.view.WindowManager;
import android.view.MotionEvent;

public class QUIGameEntry extends Activity {

    private GLSurfaceView mGLView;
    private LoadLibraries loader;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS
                           , WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS);
        loader = new LoadLibraries();
        loader.dummy();
        // Create a GLSurfaceView instance and set it
        // as the ContentView for this Activity
        mGLView = new MyGLSurfaceView(this);
        setContentView(mGLView);
    }

    @Override
    protected void onPause() {
        super.onPause();
        // The following call pauses the rendering thread.
        // If your OpenGL application is memory intensive,
        // you should consider de-allocating objects that
        // consume significant memory here.
        mGLView.onPause();
    }
    
    @Override
    protected void onResume() {
        super.onResume();
        // The following call resumes a paused rendering thread.
        // If you de-allocated graphic objects for onPause()
        // this is a good place to re-allocate them.
        mGLView.onResume();
    }
}

class MyGLSurfaceView extends GLSurfaceView {
    private static String LOGLEVEL = "MyGLSurfaceView";

    public MyGLSurfaceView(Context context) {
        super(context);

        ApplicationInfo appInfo = null;
        PackageManager pm = context.getPackageManager();
        try {
            appInfo = pm.getApplicationInfo("ro.qui.apps", 0); 
        } catch (NameNotFoundException e) {
            e.printStackTrace();
            throw new RuntimeException("Unable to get ApplicationInfo object!");
        } catch (Exception e) {
            e.printStackTrace();
        }

        // Create an OpenGL ES 2.0 context.
        setEGLContextClientVersion(2);

        // Set the Renderer for drawing on the GLSurfaceView
        setRenderer(new MyGLRenderer());

        // Render the view only when there is a change in the drawing data
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
        
        JNIGameInterface.init(appInfo.sourceDir);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event)
    {
        final int x = (int) event.getX();
        final int y = (int) event.getY();
        final int pointerCount = event.getPointerCount();
        final int historySize = event.getHistorySize();
        
        int type = 0;
        if (event.getAction() == MotionEvent.ACTION_DOWN)
        {
            type = 1;
        }
        else if (event.getAction() == MotionEvent.ACTION_UP)
        {
            type = 2;
        }
        else if (event.getAction() == MotionEvent.ACTION_MOVE)
        {
            type = 3;
        }

        for (int h = 0; h < historySize; h++) {
            for (int p = 0; p < pointerCount; p++) {
                int hx = (int) event.getHistoricalX(p, h);
                int hy = (int) event.getHistoricalY(p, h);
                JNIGameInterface.onTouchEvent(event.getPointerId(p), type, hx, hy);
            }
        }

        for (int i = 0; i < pointerCount; i++)
        {
            JNIGameInterface.onTouchEvent(event.getPointerId(i), type, x, y);
        }
        return true;
    }
}
