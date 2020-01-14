# SrsQuic

This project use srs-librtmp exported from [srs project](https://github.com/ossrs/srs) to push rtmp stream over quic with [RawQuic library](https://github.com/sonysuqin/RawQuic). 

## Supported platform
Currently tested on Linux/Windows, other platforms like android/ios should also be all right.

## srs-librtmp
Base on srs 2.0release, exported as single file, added some platform specified adaption.
See
```
SrsQuic/trunk/out/srs_librtmp.h
SrsQuic/trunk/out/srs_librtmp.cpp
```

## Server
We provide [nginx-quic](https://github.com/evansun922/nginx-quic) with quic patched, rtmp module with quic also supported now.
Rtmp additional configure
```
rtmp {
    log_format rtmp_log    '$remote_addr [$time_local] $command "$app" "$name" "$args" '
                           '$bytes_received $bytes_sent $session_time '
                           '"$pageurl" "$tcurl" "$swfurl" "$flashver"';

    access_log             logs/rtmp.log rtmp_log;

    server {
        listen         1935 so_keepalive=on;
        listen         1935 quic;

        ssl_certificate     /etc/letsencrypt/live/roblin.cn/fullchain.pem; # managed by Certbot
        ssl_certificate_key /etc/letsencrypt/live/roblin.cn/privkey.pem; # managed by Certbot

        max_message 10M;
        publish_time_fix  on;
        chunk_size     4096;
        out_queue      17;

        application live {
            live on;
            idle_streams        off;
            drop_idle_publisher 1800s;
            sync                1s;
            wait_key            on;
            wait_video          off;
            notify_method       get;
        }
    }
}
```

## How to use

### Build RawQuic library
Under ubuntu 1604, a prebuilt RawQuic shared library librawquic.so provided under SrsQuic/lib/linux.
Custom build refer to [RawQuic library](https://github.com/sonysuqin/RawQuic).

### Integrate sources
Integrate files bellow to your project
```
SrsQuic/include/raw_quic_api.h
SrsQuic/include/raw_quic_define.h
SrsQuic/trunk/out/srs_librtmp.h
SrsQuic/trunk/out/srs_librtmp.cpp
librawquic.so
```

### Call api in srs_librtmp.h
For using rtmp over quic, you should call srs_rtmp_over_quic_create instead of srs_rtmp_create.

## Demo
### Build
```
cd SrsQuic/build
cmake .
make
```
This will build src/trunk/research/librtmp/srs_h264_raw_publish.c with srs-librtmp and RawQuic library, this demo can only push raw h264 stream.

### Prepare h264 raw file
```
ffmpeg -i 1.mp4 -c:v copy -bsf:v h264_mp4toannexb -an 1.h264
```

### Push stream
A test [server](https://github.com/evansun922/nginx-quic) is running on roblin.cn, you SHOULD setup your own, please refer to [nginx-quic](https://github.com/evansun922/nginx-quic).
```
cd SrsQuic/bin
./raw_h264_publisher 1.h264 rtmp://roblin.cn:1935/live/1 25
```

### Pull stream
You can pull with fflay or vlc.
```
ffplay 'rtmp://roblin.cn:1935/live/1'
```
