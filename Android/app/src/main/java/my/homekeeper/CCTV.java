package my.homekeeper;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.support.design.widget.BottomNavigationView;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.widget.TextView;
import android.widget.Toast;

public class CCTV extends Fragment {
    final String TAG = "TAG+CCTVFragment";
    WebView webView;
    WebSettings webSettings;
    TextView callText;
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_cctv, container, false);
        Log.d(TAG,"Create CCTV Fragment");

        webView = (WebView) view.findViewById(R.id.cctvWeb);
        callText = (TextView) view.findViewById(R.id.callText);

        webSettings = webView.getSettings();
        webSettings.setJavaScriptEnabled(true);

        webView.loadData("<html><head><style type='text/css'>body{margin:auto auto;text-align:center;} " +
                        "img{width:100%25;} div{overflow: hidden;} </style></head>" +
                        "<body><div><img src='http://121.153.150.157:8082/'/></div></body></html>",
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
        }); // WebView 터치 시 새로고침

        callText.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                AlertDialog.Builder alert = new AlertDialog.Builder(getContext());
                alert.setTitle("신고");
                alert.setMessage("신고하시겠습니까?");
                alert.setPositiveButton("Yes", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Intent intent = new Intent(Intent.ACTION_DIAL, Uri.parse("tel:112"));
                        startActivity(intent);
                    }
                });
                alert.setNegativeButton("No", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {

                    }
                });
                AlertDialog alertDialog = alert.create();
                alertDialog.show();
            }
        });
        return view;
    }

}
