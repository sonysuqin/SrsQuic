/**
 *  @file        raw_quic_api.h
 *  @brief       RawQuic api声明文件.
 *  @author      sonysuqin
 *  @copyright   sonysuqin
 *  @version     1.0.1
 */

#ifndef NET_QUIC_RAW_QUIC_RAW_QUIC_API_H_
#define NET_QUIC_RAW_QUIC_RAW_QUIC_API_H_

#include "raw_quic_define.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @brief  创建一个RawQuic句柄.
 *  @param  callback        异步回调.
 *  @param  opaque          上层传递的参数，将在回调中作为参数回传.
 *  @param  verify          是否校验证书.
 *  @return RawQuic句柄.
 */
RAW_QUIC_API RawQuicHandle RAW_QUIC_CALL RawQuicOpen(RawQuicCallbacks callback,
                                                     void* opaque,
                                                     bool verify);

/**
 *  @brief  关闭一个RawQuic句柄.
 *  @param  handle          RawQuic句柄.
 *  @return 错误码.
 */
RAW_QUIC_API int32_t RAW_QUIC_CALL RawQuicClose(RawQuicHandle handle);

/**
 *  @brief  使用RawQuic句柄连接一个服务.
 *  @param  handle          RawQuic句柄.
 *  @param  host            服务端域名，注意QUIC必须加密，所以必须有域名及证书.
 *  @param  port            服务端端口.
 *  @param  port            服务端路径.
 *  @param  timeout         超时时间，ms.
 *  @note   timeout非0时，为同步方法，会阻塞直到连接成功、失败、或者超时，
 *          当timeout为0时，为异步方法，connect_callback将被回调.
 *  @return 错误码.
 */
RAW_QUIC_API int32_t RAW_QUIC_CALL RawQuicConnect(RawQuicHandle handle,
                                                  const char* host,
                                                  uint16_t port,
                                                  const char* path,
                                                  int32_t timeout);

/**
 *  @brief  使用RawQuic句柄发送一段数据.
 *  @param  handle          RawQuic句柄.
 *  @param  data            数据缓存地址.
 *  @param  size            数据长度.
 *  @note   只是放到发送缓冲区.
 *  @return 发送的字节数或者错误码.
 */
RAW_QUIC_API int32_t RAW_QUIC_CALL RawQuicSend(RawQuicHandle handle,
                                               uint8_t* data,
                                               uint32_t size);

/**
 *  @brief  使用RawQuic句柄接收一段数据.
 *  @param  handle          RawQuic句柄.
 *  @param  data            数据缓存地址.
 *  @param  size            数据缓存长度.
 *  @param  timeout         超时时间，ms.
 *  @note   timeout非0时，将等待直到有数据、失败、或者超时,
 *          timeout为0时，只是尝试检查接收缓冲区是否有数据，
 *          有则返回数据，否则返回EAGAIN. can_read_callback
 *          回调将会通知有数据可读(边缘触发).
 *  @return 接收的字节数或者错误码.
 */
RAW_QUIC_API int32_t RAW_QUIC_CALL RawQuicRecv(RawQuicHandle handle,
                                               uint8_t* data,
                                               uint32_t size,
                                               int32_t timeout);

#ifdef __cplusplus
}
#endif

#endif  // NET_QUIC_RAW_QUIC_RAW_QUIC_API_H_
