package my.homekeeper;


import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.widget.ImageView;
import android.widget.ViewFlipper;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;

public class CCTV extends Fragment {
    ImageView imageView;
    WebView webView;
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_cctv, container, false);
        imageView = (ImageView) view.findViewById(R.id.cctvsrc);
        //webView = (WebView) view.findViewById(R.id.cctvweb);

        try{
            URL url = new URL("https://upload.wikimedia.org/wikipedia/commons/thumb/d/d2/IU_at_Melon_Music_Awards%2C_13_November_2014_01.jpg/180px-IU_at_Melon_Music_Awards%2C_13_November_2014_01.jpg");
            URLConnection connection = url.openConnection();
            connection.connect();
            BufferedInputStream bis = new BufferedInputStream(connection.getInputStream());
            Bitmap bm = BitmapFactory.decodeStream(bis); bis.close();
            imageView.setImageBitmap(bm);

        } catch (Exception e) {

        }

        /*WebSettings webSettings = webView.getSettings();
        webSettings.setJavaScriptEnabled(true);
        webView.loadUrl("http://192.168.0.71:8082/");
*/
        return view;
    }

}
