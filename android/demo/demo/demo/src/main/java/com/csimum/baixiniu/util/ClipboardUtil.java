package com.csimum.baixiniu.util;

import android.app.Activity;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.net.Uri;

import static android.content.Context.CLIPBOARD_SERVICE;

public class ClipboardUtil {

    public static void copyToClipboard(Activity activity, String url) {
        if (activity != null) {
            ClipboardManager mClipboardManager = (ClipboardManager) activity.getSystemService(CLIPBOARD_SERVICE);
            if (mClipboardManager != null) {
                ClipData mClipData = ClipData.newUri(activity.getContentResolver(), "text", Uri.parse(url));
                mClipboardManager.setPrimaryClip(mClipData);
            }
        }
    }

}
