package com.csimum.baixiniu.ui.camera;

import android.content.Intent;
import android.graphics.Color;
import android.graphics.Typeface;
import android.os.Bundle;
import android.provider.Settings;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.csimum.baixiniu.R;
import com.csimum.baixiniu.app.App;
import com.detu.dispatch.camera.CameraManager;
import com.detu.dispatch.camera.ICamera;
import com.detu.dispatch.camera.RICOHThetaCamera;
import com.detu.dispatch.camera.Twins360_ACamera;
import com.detu.dispatch.dispatcher.MainDispatcher;
import com.detu.dispatch.network.NetControl;
import com.detu.module.app.ActivityWithOneActiveFragment;
import com.detu.module.app.statusbar.UltimateBar;
import com.detu.module.ui.common.FragmentWebView;
import com.detu.module.widget.DTMenuItem;

import static com.detu.dispatch.dispatcher.entity.CameraTypeEnum.DispatchMachine_TwinA;

/**
 * Created by five on 2018/3/30.
 */

public class ActivityCameraConnectWebHelp extends ActivityWithOneActiveFragment {
    private static final String URL_APP_USAGE = "file:///android_asset/app_usage.html";
//private static final String URL_APP_USAGE = "http://oss-static.detu.com/application/views/csimum/app_usage.html";

    FragmentWebView fragmentWebView;

    @Override
    public View getViewContent(LayoutInflater layoutInflater, ViewGroup viewGroup, boolean b) {
        return layoutInflater.inflate(R.layout.activity_web_help, viewGroup, b);
    }

    @Override
    public void initViews() {
        setTitle(R.string.project_help_title);
        toggleBottomLineVisible(false);
        getTitleMenuItem().getLabelView().setTypeface(Typeface.DEFAULT_BOLD);
        setTitleTextColor(Color.parseColor("#FFFFFF"));
        setImmerseStatusBarBackgroundColor(Color.parseColor("#25263A"));
        UltimateBar.newColorBuilder()
                .statusColor(Color.parseColor("#25263A"))        // 状态栏颜色
                .applyNav(true)                 // 是否应用到导航栏
                .navColor(Color.parseColor("#25263A"))          // 导航栏颜色
                .applyDarkStateMode(false)
                .build(this)
                .apply();

        fragmentWebView = new FragmentWebView();
        Bundle bundle = new Bundle();
        bundle.putString("Url", URL_APP_USAGE);
        bundle.putBoolean(FragmentWebView.KEY_SHOW_PROGRESS, true);
        fragmentWebView.setArguments(bundle);
        replaceFragment(fragmentWebView, R.id.webFrame);
    }

    @Override
    protected boolean configIsShowBackArrow(DTMenuItem dtmiBack) {
        dtmiBack.setImageResource(R.mipmap.public_back_white);
        return true;
    }

    @Override
    protected boolean configIsShowRightMemuItem(DTMenuItem dtmiRight) {
        dtmiRight.setText(R.string.project_help_to_setting);
        dtmiRight.setTextColor(Color.parseColor("#00E2C8"));
        dtmiRight.setTextSize(14);
        return true;
    }

    @Override
    protected void onRightMenuItemClicked(DTMenuItem dtmiRight) {
        super.onRightMenuItemClicked(dtmiRight);
        startActivityForResult(new Intent(Settings.ACTION_WIFI_SETTINGS), 100);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (MainDispatcher.getInstance().isCameraConnected()) {
//            if(!Twins360_ACamera.get().isCameraDeviceBySsid(NetControl.getInstance().getSSID())){
//                toast("暂不支持此相机");
//                return;
//            }
            setResult(RESULT_OK);
            finish();
        }
    }

    @Override
    protected void onDestroy() {
        fragmentWebView.clearCache(true);
        super.onDestroy();
    }
}
