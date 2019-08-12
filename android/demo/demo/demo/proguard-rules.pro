
-optimizationpasses 5
-dontusemixedcaseclassnames
-dontskipnonpubliclibraryclasses
-dontpreverify
-verbose
-optimizations !code/simplification/arithmetic,!field/*,!class/merging/*
#
-keep public class * extends android.app.Activity
-keep public class * extends android.app.Application
-keep public class * extends android.app.Service
-keep public class * extends android.content.BroadcastReceiver
-keep public class * extends android.content.ContentProvider
-keep public class * extends android.app.backup.BackupAgentHelper
-keep public class * extends android.preference.Preference
-keep public class com.android.vending.licensing.ILicensingService

-keepclasseswithmembernames class * {
    native <methods>;
}

-keepclasseswithmembers class * {
    public <init>(android.content.Context, android.util.AttributeSet);
}

-keepclasseswithmembers class * {
    public <init>(android.content.Context, android.util.AttributeSet, int);
}

-keepclassmembers class * extends android.app.Activity {
   public void *(android.view.View);
}

-keepclassmembers enum * {
    public static **[] values();
    public static ** valueOf(java.lang.String);
}

-keep class * implements android.os.Parcelable {
  public static final android.os.Parcelable$Creator *;
}

-dontwarn android.support.**
-keep class android.support.**{*;}

-dontwarn javax.**
-keep class javax.**{*;}

-dontwarn java.**
-keep class java.**{*;}

-dontwarn com.intellij.**
-keep class com.intellij.**{*;}




#得图播放器
-dontwarn com.google.**
-keep class com.google.**{*;}

-dontwarn tv.danmaku.ijk.media.player.**
-keep class tv.danmaku.ijk.media.player.**{*;}


-dontwarn com.player.**
-keep class com.player.**{*;}

-dontwarn com.detu.m1decoder.**
-keep class com.detu.m1decoder.**{*;}

-dontwarn com.detu.android_panoplayer.**
-keep class com.detu.android_panoplayer.**{*;}

-dontwarn com.detu.getmaskandweight.**
-keep class com.detu.getmaskandweight.**{*;}

-dontwarn com.detu.panoplayer.**
-keep class com.detu.panoplayer.**{*;}

-keep class org.simpleframework.** { *; }
-dontwarn org.simpleframework.**


#相机协议中的Json实体类
-keep class com.detu.f4_plus_sdk.enitity.**{*;}

-dontwarn com.detu.f4_plus_sdk.upgrade.**
-keep class com.detu.f4_plus_sdk.upgrade.**{*;}

-dontwarn com.detu.dispatch.**
-keep class com.detu.dispatch.**{*;}

-dontwarn com.detu.novatek.**
-keep class com.detu.novatek.**{*;}


-dontwarn com.detu.sp800.**
-keep class com.detu.sp800.**{*;}

-dontwarn org.jsoup.**
-keep class org.jsoup.**{*;}

-dontwarn com.detu.spatialmedia.**
-keep class com.detu.spatialmedia.**{*;}

-dontwarn org.codehaus.**
-keep class org.codehaus.**{*;}


-keepclassmembers class AppNetInfo{
    *;
}
#友盟需要start
-keepclassmembers class * {
   public <init> (org.json.JSONObject);
}
-keep public class com.detu.baixiniu.R$*{
public static final int *;
}



-keep class com.detu.module.** { *; }
-dontwarn com.detu.module.**

-keep class com.bumptech.glide.**{*;}
-dontwarn com.bumptech.glide.**

-keep class freemarker.**{*;}
-dontwarn freemarker.**

-keep class org.greenrobot.**{*;}
-dontwarn org.greenrobot.**

-keep class butterknife.**{*;}
-dontwarn butterknife.**
