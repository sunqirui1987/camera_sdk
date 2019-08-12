package com.csimum.baixiniu.util;


import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.wifi.WifiManager;
import android.provider.Settings;

import com.detu.module.libs.NetworkUtil;

public final class NetworkUtils extends NetworkUtil {
    private final static String TAG = "NetworkUtils";

    /**
     * 开启wifi设置页面
     */
    public static void openWiFiSetting(Activity activity, int requestCode) {
        activity.startActivityForResult(new Intent(Settings.ACTION_WIFI_SETTINGS), requestCode);
    }

    /**
     * @return wifi 是否可以
     */
    public static boolean wifiEnable(Activity activity) {
        WifiManager wifiManager = (WifiManager) activity.getApplicationContext().getSystemService(Context.WIFI_SERVICE);
        return wifiManager != null && wifiManager.isWifiEnabled();
    }

    /**
     * 打开或关闭Wifi
     */
    public static void toggleWifiEnabled(Context activity, boolean open) {
        WifiManager wifiManager = (WifiManager) activity.getApplicationContext().getSystemService(Context.WIFI_SERVICE);
        if (wifiManager != null) {
            if (wifiManager.isWifiEnabled()) {
                if (!open) {
                    wifiManager.setWifiEnabled(false);
                }
            } else {
                if (open) {
                    wifiManager.setWifiEnabled(true);
                }
            }
        }
    }


}
