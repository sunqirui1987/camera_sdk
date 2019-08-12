package com.csimum.baixiniu.ui.camera;

import com.detu.module.net.player.FileInfo;

import java.util.ArrayList;

/**
 * Created by five on 2017/12/14.
 * <p>
 * F4 图片下载回调
 */

public interface DownloadPicCallback {
    /**
     * 下载成功
     */
    int STATE_SUCCESS = 1;
    /**
     * 下载失败
     */
    int STATE_FAULT = 0;

    /**
     * 文件下载完成
     *
     * @param downloadState 文件下载状态, IO异常/ 网络异常/ 引起
     * @param downloadPath  下载的文件
     */
    void onDownloadFinish(int downloadState, ArrayList<FileInfo> downloadPath);


}
