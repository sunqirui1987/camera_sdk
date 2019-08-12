package com.csimum.baixiniu.app;

import android.text.TextUtils;
import android.widget.Toast;

import com.csimum.baixiniu.R;

import com.detu.dispatch.dispatcher.MainDispatcher;
import com.detu.module.libs.NetworkUtil;

import java.util.Locale;

public class BxnConst {
    //广播: 网络数据变更
    public static final String BROADCAST_PROJECT_STATE_CHANGE = "PROJECT_STATE_CHANGE";
    //广播: 项目已被删除
    public static final String BROADCAST_PROJECT_DEL = "PROJECT_DEL";
    //接收到系统消息
    public static final String BROADCAST_MESSAGE_RECEIVED = "MESSAGE_RECEIVED";

    public static final String KEY_ID = "ID";

    public static final int PROJECT_NAME_MAX_LENGTH = 20;
    //楼层名称最大长度
    public static final int FLOOR_NAME_MAX_LENGTH = 3;

    /**
     * 验证手机号码
     * <p>
     * 移动号码段:139、138、137、136、135、134、150、151、152、157、158、159、182、183、187、188、147,17..
     * 联通号码段:130、131、132、136、185、186、145
     * 电信号码段:133、153、180、189
     */
    public static String getPhoneRegex() {
        return "^(13[0-9]|14[5679]|15[0-3,5-9]|16[6]|17[0-9]|18[0-9]|19[89])\\d{8}$";
    }

    /**
     * @return 密码最短多少位
     */
    public static int getMinPasswordLength() {
        return 8;
    }

    private static final String[] ARRAY_SUFFIX = new String[]{
            "省", "自治区", "自治州", "地区", "盟", "特别行政区",
            "市", "县", "自治县", "旗", "自治旗", "特区", "林区",
            "区", "镇", "乡", "村", "街道"};

    public static String filterCitySuffix(String name) {
        if (!TextUtils.isEmpty(name)) {
            for (String suffix : ARRAY_SUFFIX) {
                if (name.endsWith(suffix)) {
                    name = name.replace(suffix, "");
                    break;
                }
            }
        }
        return name;
    }

    private static final String[] ARRAY_ZXS = new String[]{
            "北京市", "天津市", "上海市", "重庆市",
            "内蒙古自治区", "新疆维吾尔自治区", "广西壮族自治区", "宁夏回族自治区", "西藏自治区",
            "香港特别行政区", "澳门特别行政区"};

    /**
     * 判断给定名称是否是直辖市
     */
    public static boolean isLikeZXS(String name) {
        if (!TextUtils.isEmpty(name)) {
            for (String zxs : ARRAY_ZXS) {
                if (name.equals(zxs)) {
                    return true;
                }
            }
        }
        return false;
    }



    /**
     * @return 白犀牛帮助中心页面地址
     */
    public static String getHelpCenterUrl() {
        return "http://help.csimum.com";
    }


}
