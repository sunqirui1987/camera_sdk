package com.csimum.baixiniu.app;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.res.Configuration;
import android.content.res.Resources;

import com.detu.dispatch.dispatcher.MainDispatcher;
import com.detu.module.Config;
import com.detu.module.DtModule;
import com.detu.module.app.AppSettingInfo;
import com.detu.module.app.DTBaseApplication;
import com.detu.module.app.update.AppUpdateManager;
import com.detu.module.app.update.DetuAppUpdate;
import com.detu.module.libs.FileUtil;
import com.detu.module.libs.LogUtil;

import java.util.HashSet;
import java.util.List;
import java.util.Locale;


import static android.content.Intent.FLAG_ACTIVITY_NEW_TASK;

/**
 * Created by five on 2018/3/27.
 */

public class App extends DTBaseApplication {
    //正式站/测试站切换
    public static boolean DEBUG = false;
    //是否是个人版
    public static boolean PersonalVersion = false;
    //是否输出日志信息
    public static boolean LOG_ENABLE = true;

    @Override
    public void init() {

        //设置APP默认语言选项
        updateResourcesLocale(this, Locale.CHINESE);
        AppSettingInfo.setDefaultLanguage(Locale.CHINESE);
        FileUtil.init(this);
        //测试站
        Config.DEBUG = DEBUG;
        LogUtil.setLogEnable(LOG_ENABLE);
        MainDispatcher.getInstance().init(this);

    }

    /**
     * 设置APP语言环境
     *
     * @param context 上下文
     * @param locale  语言
     */
    public static void updateResourcesLocale(Context context, Locale locale) {
        Locale.setDefault(locale);
        Resources res = context.getResources();
        Configuration config = new Configuration(res.getConfiguration());
        config.locale = locale;
        res.updateConfiguration(config, res.getDisplayMetrics());
    }

    @Override
    public boolean isDebugMode() {
        return DEBUG;
    }



}
