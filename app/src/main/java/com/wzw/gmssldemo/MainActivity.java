package com.wzw.gmssldemo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.util.Base64;
import android.widget.TextView;

import com.wzw.gmssldemo.databinding.ActivityMainBinding;

import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'gmssldemo' library on application startup.
    static {
        System.loadLibrary("gmssl");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
//        byte[] data = Util.hex2byte("123456");
//        tv.setText(stringFromJNI(data,data.length));


        new Thread(()->{

    {
//                byte[] data = Util.hex2byte("313233343536");
//            byte[] data = Util.hex2byte("3DE741F445DD357BEA4E6C3FE6437036F62B5E3EC0F00D62796EDB4305ED627F");
//                byte[] pubKey = Util.hex2byte("4C8E402D8826CB8EEB947328E0D7A7A4E23D96090BCF02D58473159A8C26F831C0140B6A1A3741AB012D9FB0500C370B203CF617EAB882F12241FAC14A989DFE");
               byte[] pubKey = Util.hex2byte("B5084C6C18A8D4239412AD07968B406CEA7B1B205CBD7C3F6AF4C29052E31EE290E61F6294D25266A00275D63FE03AAEE76316AD957F9BB637EEE83A479FEC60");
                byte[] r = Util.hex2byte("65115556D4CE26E9249A2DC003DD7462AC2D57807502576C8136CC0578B68565");
                byte[] s = Util.hex2byte("B68C7566A6B6E888D58FA8AD116C892015DFC629C40401D9CC4AD8C07A8D24D8");
                int ret = sm2test(
                        data,data.length,
                        pubKey,pubKey.length,
                        r,r.length,
                        s,s.length
                );
            }


            /*SM4加密*/
            {
                byte[] data2 = Util.hex2byte( "31323334353637383132333435363738");
                byte[] sm4Key = Util.hex2byte("31323334313233343132333431323334");
                sm4Test(data2,data2.length,sm4Key,sm4Key.length);
            }

            /*SM2 证书解析*/
            byte[] cert_der = Util.hex2byte("308201E230820188020900CF9C372153F612D3300A06082A811CCF550183753079310B300906035504061302436E310E300C06035504080C054875626569310E300C06035504070C05577568616E310B3009060355040A0C026B6B310C300A060355040B0C036B6B6B310F300D06035504030C06746573746361311E301C06092A864886F70D010901160F6B68616F73694073696E612E636F6D301E170D3231303730393131333035335A170D3232303730393131333035335A3079310B300906035504061302436E310E300C06035504080C054875626569310E300C06035504070C05577568616E310B3009060355040A0C026B6B310C300A060355040B0C036B6B6B310F300D06035504030C06746573746361311E301C06092A864886F70D010901160F6B68616F73694073696E612E636F6D3059301306072A8648CE3D020106082A811CCF5501822D03420004204513F91E42C2268A8E01ED15F7A3E241A3D041BD15F7A7E8FEEE39B7340EB574DCE5B79D5879D497983C8CC940101EF5CFFDB698BAEA9222DB87D261466E69300A06082A811CCF55018375034800304502204DFFDE6146C6DBCBB772445E8BBF3302B41BD656E1AAFBA1B48CB454092EFB4E0221009BC8445EA994E8F77BB93E2931FD5D48D54B27CE73F7AEEDBDD7C0CBC61350F5");
            sm2ParseCert(cert_der,cert_der.length);


            /*SM9 测试*/
            sm9test( );

            /*ZUC 测试*/

            zuctest();

        }).start();
    }

    public native int sm2test(
            byte[] data, int  dataLen,
            byte[] pubKey, int pubKeyLen,
            byte[] r, int  rLen,
            byte[] s, int  sLen
                                );
    public native int sm4Test(
            byte[] data, int dataLen,
            byte[] sm4Key, int sm4KeyLen
                                );
    public native int sm2ParseCert(
            byte[] data, int dataLen
                                );

    public native int sm9test( );

    public native int zuctest( );
}