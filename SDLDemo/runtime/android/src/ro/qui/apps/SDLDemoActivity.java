package ro.qui.apps;

import android.app.Activity;
import android.os.Bundle;
import org.libsdl.app.SDLActivity;
import org.libsdl.app.R;

public class SDLDemoActivity extends SDLActivity
{
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
    }
}
