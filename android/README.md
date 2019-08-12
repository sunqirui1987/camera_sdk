##得图相机SDK使用说明##
#### 介绍
得图相机SDK 集成了相机命令控制器
++注意：==只能支持真机调试==++

***
##### 初始化
``` 
 MainDispatcher.getInstance().registerHandler(cameraInfoHandler);
 //判断相机是否连接
  if (!MainDispatcher.getInstance().isCameraConnected()) {
            LogUtil.i(TAG, "initCameraSocket()--> 相机未连接");
            return;
        }
```
##### 准备阶段
``` 
 MainDispatcher.getInstance().prepare(new OnPreparedListener() {
            @Override
            public void onPrepared() {
                LogUtil.i(TAG, "onPrepared() ");
             }

            @Override
            public void onPrepareFailed(DispatcherException dispatcherException) {
                LogUtil.i(TAG, "onPrepareFailed() ");
                cameraSocketInit = false;
                tryConnectCamera(dispatcherException);
            }
    });
```

#### 进入预览。
```
MainDispatcher.getInstance().previewWillAppear().doOnSuccess(new Consumer<BaseEntity>() {
                    @Override
                    public void accept(BaseEntity baseEntity) throws Exception {
                        LogUtil.i(TAG, "previewWillAppear()-->doOnSuccess() ");
                       


                    }
                }).doOnError(new RequestBuilder.ErrorCallback() {
                    @Override
                    public void onError(DispatcherException dispatcherException) {
                        LogUtil.i(TAG, "previewWillAppear()-->onError() ");
                    }
                }).submit();
```

#### 获取标定
```
                        MainDispatcher.getInstance().getCalibration().doFinally(new Action() {
                            @Override
                            public void run() throws Exception {
                                 //进入播放
                            }
                        }).submit().previewWillAppear().submit();
```

#### 播放器播放
```
      PlaySourceInfo playSourceInfo = new PlaySourceInfo();
                playSourceInfo.setSource(PlayerData.DataSource.Camera);
                playSourceInfo.setXmlContent(xml);
                LogUtil.i(TAG, "playPreview - xml :" + xml);
                playerListenerImpl.setGestureEnable(true);
                playerListenerImpl.startPlayWork(playSourceInfo);
                //新添加
                PanoPlayerOption optionTransPort = new PanoPlayerOption(PanoPlayerOptionType.OPT_CATEGORY_FORMAT, PanoOptionKey.RTSP_TRANSPORT, "tcp");
                playerListenerImpl.addOptionValue(optionTransPort);
```

###拍照片
```
  showProgress("正在拍摄中，请勿移动相机");
        btnCapture.setEnabled(false);
        MainDispatcher.getInstance().getMachineVersion().doOnSuccess(new Consumer<BaseEntity>() {
            @Override
            public void accept(BaseEntity baseEntity) throws Exception {
                LogUtil.i(TAG, "相机信息获取成功");
                CameraInfo cameraInfo = MainDispatcher.getInstance().getCameraInfo();
                if (cameraInfo != null) {
                    LogUtil.i(TAG, "相机序列号:" + cameraInfo.getMachineId());
                }
            }
        }).doOnError(new RequestBuilder.ErrorCallback() {
            @Override
            public void onError(DispatcherException e) {
                LogUtil.i(TAG, "相机信息获取失败 !!!");
                toast("相机编号获取失败");
            }
        }).successThen().takePhoto().doOnSuccess(new Consumer<BaseEntity>() {
            @Override
            public void accept(@NonNull BaseEntity baseEntity) throws Exception {
                LogUtil.i(TAG, "拍照成功");
                
                MainDispatcher.getInstance().getFreeSpace().submit();

            }
        }).doOnError(new RequestBuilder.ErrorCallback() {
            @Override
            public void onError(DispatcherException dispatcherException) {
                LogUtil.i(TAG, "拍照失败:");
                onCaptureError(dispatcherException);
            }
        }).submit();
```

#### 拍成功后进行下载

```
 String photoPathJson = MainDispatcher.getInstance().getCameraInfo().getPhotoPath();
        try {
            JsonReader reader = new JsonReader(new StringReader(photoPathJson));
            List<String> paths = new ArrayList<>();
            reader.beginArray();
            while (reader.hasNext()) {
                paths.add(reader.nextString());
            }
            reader.endArray();
            String photoDownloadUrl = paths.get(0);
            String savePath = generateSavePathDownload(photoDownloadUrl);
            FileInfo fileInfo = new FileInfo();
            fileInfo.setFilePath(savePath);
            Bundle bundle = new Bundle();
            bundle.putString("downloadUrl", photoDownloadUrl);
            fileInfo.setBundle(bundle);
            showProgress(R.string.downloading);
            new DownloadPicTask().setDownloadF4PicCallback(this).execute(fileInfo);
        } catch (IOException e) {
            e.printStackTrace();
            btnCapture.setEnabled(true);
        }
```

####转码
```
   ConvertPhoto convertPhoto = new ConvertPhoto(null);
        convertPhoto.setVideoStitchListener(listener);
        convertPhoto.start(srcPath, destPath, width, height, deviceType);
        
```
