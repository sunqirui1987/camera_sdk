package com.csimum.baixiniu.ui.camera;

import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.AsyncTask;

import com.detu.downloadconvertmetadata.convertmedia.ConvertPhoto;
import com.detu.module.libs.LogUtil;
import com.detu.module.net.player.FileInfo;
import com.detu.remux.DeviceId;
import com.detu.remux.IVideoStitchListener;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.net.URLConnection;
import java.util.ArrayList;

import okhttp3.Call;
import okhttp3.HttpUrl;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;
import okhttp3.ResponseBody;

/**
 * Created by five on 2017/12/14.
 * 文件下载任务
 */

public class DownloadPicTask extends AsyncTask<FileInfo, Integer, ArrayList<FileInfo>> {

    private static final int RETRY_TIME_MAX = 3;
    private DownloadPicCallback downloadF4PicCallback;

    public DownloadPicTask setDownloadF4PicCallback(DownloadPicCallback downloadF4PicCallback) {
        this.downloadF4PicCallback = downloadF4PicCallback;
        return this;
    }

    @Override
    protected void onPostExecute(ArrayList<FileInfo> panoramicFiles) {
        super.onPostExecute(panoramicFiles);
        if (downloadF4PicCallback != null) {
            int downloadState;
            if (panoramicFiles != null) {
                downloadState = DownloadPicCallback.STATE_SUCCESS;
            } else {
                downloadState = DownloadPicCallback.STATE_FAULT;
            }
            downloadF4PicCallback.onDownloadFinish(downloadState, panoramicFiles);
        }
    }

    @Override
    protected ArrayList<FileInfo> doInBackground(FileInfo... downloadFiles) {
        ArrayList<FileInfo> downloadSavePathArray = new ArrayList<>();
        for (FileInfo itemDownloadFile : downloadFiles) {
            int retryTime = 1;
            boolean downLoaded = false;
            while (retryTime <= RETRY_TIME_MAX) {
                String savePathSrc = itemDownloadFile.getFilePath();
                String downloadUrl = itemDownloadFile.getBundle().getString("downloadUrl");
                LogUtil.i(this, "第 %d 次下载 %s 文件", retryTime, downloadUrl);
                //下载完成
                downloadFile(downloadUrl, savePathSrc);
                File fileDownloadSrc = new File(savePathSrc);
                if (fileDownloadSrc.exists() && fileDownloadSrc.length() > 0) {
                    LogUtil.i(this, "文件下载完成 !!!");
                    downloadSavePathArray.add(itemDownloadFile);
                    downLoaded = true;
                    break;
                } else {
                    retryTime++;
                }
            }
            if (!downLoaded) {
                LogUtil.e(this, "文件下载失败 !!!");
                return null;
            }
        }
        return downloadSavePathArray;
    }

    /**
     * 开始下载文件
     *
     * @param url      文件下载地址
     * @param savePath 文件保存地址
     */
    private void downloadFile(String url, String savePath) {
        HttpUrl httpUrl = HttpUrl.parse(url);
        if (httpUrl == null) {
            return;
        }
        File fileSaveFolder = new File(savePath).getParentFile();
        if(!fileSaveFolder.exists() || fileSaveFolder.isDirectory()){
            fileSaveFolder.mkdirs();
        }

        File fileSaved = null;
        FileOutputStream fileOutputStream = null;
        InputStream inputStream = null;
        try {
            URL urlDownload =  new URL(url);
            URLConnection urlConnection = urlDownload.openConnection();
            inputStream  =  urlConnection.getInputStream();

            byte[] buf = new byte[2048];
            if (inputStream != null) {
                long total = inputStream.available();
                fileSaved = new File(savePath);
                fileOutputStream = new FileOutputStream(fileSaved);
                long sum = 0L;
                int len = 0;
                while ((len = inputStream.read(buf)) != -1) {
                    fileOutputStream.write(buf, 0, len);
                    sum += (long) len;
                    int progress = (int) ((float) sum * 1.0F / (float) total * 100.0F);
                    LogUtil.i(this, "%s 下载进度 %d", url, progress);
                }
                fileOutputStream.flush();
                LogUtil.i(this, "文件下载成功 url= %s , \n savePath= %s", url, savePath);
            }
        } catch (IOException e) {
            LogUtil.e(this, e);
            if (fileSaved != null && fileSaved.exists()) {
                boolean delSuccess = fileSaved.delete();
                if (!delSuccess) LogUtil.e(this, "文件下载失败, 删除失败 !!!" + fileSaved.getAbsolutePath());
            }
        } finally {
            try {
                if (fileOutputStream != null) {
                    fileOutputStream.close();
                }
                if (inputStream != null) {
                    inputStream.close();
                }
            } catch (IOException e) {
                LogUtil.e(this, e);
            }
        }

    }

    public static void covertPhoto(String srcPath, String destPath, DeviceId deviceType, IVideoStitchListener listener) {
        BitmapFactory.Options opts = new BitmapFactory.Options();
        opts.inSampleSize = 1;
        opts.inJustDecodeBounds = true;
        BitmapFactory.decodeFile(srcPath, opts);
        int width = opts.outWidth;
        int height = opts.outHeight;
        ConvertPhoto convertPhoto = new ConvertPhoto(null);
        convertPhoto.setVideoStitchListener(listener);
        convertPhoto.start(srcPath, destPath, width, height, deviceType);
    }
}
