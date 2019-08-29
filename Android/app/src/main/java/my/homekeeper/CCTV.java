package my.homekeeper;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.widget.Toast;

public class CCTV extends Fragment {
    WebView webView;
    WebSettings webSettings;
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_cctv, container, false);

        webView = (WebView) view.findViewById(R.id.cctvWeb);
        webSettings = webView.getSettings();
        webSettings.setJavaScriptEnabled(true);

        webView.loadData("<html><head><style type='text/css'>body{margin:auto auto;text-align:center;} " +
                        "img{width:100%25;} div{overflow: hidden;} </style></head>" +
                        "<body><div><img src='http://121.153.150.18:8080/'/></div></body></html>",
                "text/html", "UTF-8");

        webView.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()) {
                    case MotionEvent.ACTION_DOWN : {
                        Toast.makeText(getContext(), "Touch", Toast.LENGTH_LONG).show();
                        webView.reload();
                        break;
                    }
                }
                return true;
            }
        });
        return view;
    }

}
