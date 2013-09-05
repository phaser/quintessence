package ro.qui.apps;

public class JNIGameInterface
{
    public native static void init(String apkPath);
    public native static void onSurfaceCreated();
	public native static void onDrawFrame();
	public native static void onSurfaceChanged(int width, int height);
	public native static void onTouchEvent(int pointerId, int type, int x, int y);
}
