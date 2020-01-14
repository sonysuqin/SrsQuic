/**
 *  @file        raw_quic_define.h
 *  @brief       RawQuic api数据结构声明文件.
 *  @author      sonysuqin
 *  @copyright   sonysuqin
 *  @version     1.0.1
 */

#ifndef NET_QUIC_RAW_QUIC_RAW_QUIC_DEFINE_H_
#define NET_QUIC_RAW_QUIC_RAW_QUIC_DEFINE_H_

#ifdef WIN32
#ifdef RAW_QUIC_SHARED_LIBRARY
#ifdef RAW_QUIC_EXPORTS
#define RAW_QUIC_API __declspec(dllexport)
#else
#define RAW_QUIC_API __declspec(dllimport)
#endif
#else
#define RAW_QUIC_API
#endif
#define RAW_QUIC_CALL __cdecl
#define RAW_QUIC_CALLBACK __cdecl
#else
#ifdef RAW_QUIC_EXPORTS
#define RAW_QUIC_API __attribute__((visibility("default")))
#else
#define RAW_QUIC_API
#endif
#define RAW_QUIC_CALL
#define RAW_QUIC_CALLBACK
#endif

/// 需要支持C99.
#include <stdint.h>
#include <stdbool.h>

/// 错误码.
typedef enum RawQuicErrorCode {
  RAW_QUIC_ERROR_CODE_SUCCESS               = 0,    //!< 成功.
  RAW_QUIC_ERROR_CODE_INVALID_PARAM         = -1,   //!< 非法参数.
  RAW_QUIC_ERROR_CODE_INVALID_STATE         = -2,   //!< 非法状态.
  RAW_QUIC_ERROR_CODE_NULL_POINTER          = -3,   //!< 空指针.
  RAW_QUIC_ERROR_CODE_SOCKET_ERROR          = -4,   //!< Socket错误.
  RAW_QUIC_ERROR_CODE_RESOLVE_FAILED        = -5,   //!< 解析失败.
  RAW_QUIC_ERROR_CODE_BUFFER_OVERFLOWED     = -6,   //!< 缓冲区溢出.
  RAW_QUIC_ERROR_CODE_STREAM_FIN            = -7,   //!< 流被结束.
  RAW_QUIC_ERROR_CODE_STREAM_RESET          = -8,   //!< 流被重置.
  RAW_QUIC_ERROR_CODE_NET_ERROR             = -9,   //!< 网络错误.
  RAW_QUIC_ERROR_CODE_QUIC_ERROR            = -10,  //!< QUIC错误.
  RAW_QUIC_ERROR_CODE_TIMEOUT               = -11,  //!< 超时.
  RAW_QUIC_ERROR_CODE_UNKNOWN               = -12,  //!< 未知错误.
  RAW_QUIC_ERROR_CODE_INVALID_HANDLE        = -13,  //!< 非法句柄.
  RAW_QUIC_ERROR_CODE_EAGAIN                = -14,  //!< EAGAIN.
  RAW_QUIC_ERROR_CODE_COUNT
} RawQuicErrorCode;

/// 错误结构.
typedef struct RawQuicError {
  RawQuicErrorCode error;   //!< RawQuicErrorCode错误码.
  int32_t net_error;        //!< 网络错误码.
  int32_t quic_error;       //!< QUIC错误码.
} RawQuicError;

/// RawQuic句柄类型.
typedef void* RawQuicHandle;

/**
 *  @brief  连接结果回调，只有在timeout为0才回调.
 *  @param  handle      RawQuic句柄.
 *  @param  error       错误结构.
 *  @param  opaque      透传参数.
 */
typedef void(RAW_QUIC_CALLBACK* ConnectCallback)(RawQuicHandle handle,
                                                 RawQuicError* error,
                                                 void* opaque);

/**
 *  @brief  错误回调，发生错误时回调.
 *  @param  handle      RawQuic句柄.
 *  @param  error       错误结构.
 *  @param  opaque      透传参数.
 */
typedef void(RAW_QUIC_CALLBACK* ErrorCallback)(RawQuicHandle handle,
                                               RawQuicError* error,
                                               void* opaque);

/**
 *  @brief  可读回调.
 *  @param  handle      RawQuic句柄.
 *  @param  size        可读数据长度.
 *  @param  opaque      透传参数.
 */
typedef void(RAW_QUIC_CALLBACK* CanReadCallback)(RawQuicHandle handle,
                                                 uint32_t size,
                                                 void* opaque);

/// RawQuic回调结构.
typedef struct RawQuicCallbacks {
  ConnectCallback connect_callback;     //!< 连接结果回调.
  ErrorCallback error_callback;         //!< 错误回调.
  CanReadCallback can_read_callback;    //!< 可读回调.
} RawQuicCallbacks;

#endif  // NET_QUIC_RAW_QUIC_RAW_QUIC_DEFINE_H_
