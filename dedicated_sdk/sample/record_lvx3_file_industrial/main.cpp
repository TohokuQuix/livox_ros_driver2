//
// The MIT License (MIT)
//
// Copyright (c) 2021 Livox. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "livox_sdk_common.h"
#include "livox_def_common.h"
#include "livox_sdk.h"

#include "PPTAPI.h"

#include <atomic>
#include <chrono>
#include <ctime>
#include <iostream>
#include <map>
#include <mutex>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <thread>
#include <vector>

constexpr int kSupportedLidarNumber = 1;
constexpr int kWriteBufferLength =  1024 * 1024;
constexpr int kRecordingTime = 8; // seconds

std::atomic<bool> is_sampling{false};

typedef enum {
  kDeviceStateDisconnect = 0,
  kDeviceStateConnect = 1,
  kDeviceStateSampling = 2,
} DeviceState;

typedef struct {
  uint8_t handle;
  DeviceState device_state;
  DeviceInfo info;
} DeviceItem;

DeviceItem devices[kMaxLidarCount];
uint32_t data_recveive_count[kMaxLidarCount];

/** Connect all the broadcast device. */
int lidar_count = 0;
char broadcast_code_list[kMaxLidarCount][kBroadcastCodeSize];

/** Receiving error message from Livox Lidar. */
void OnLidarErrorStatusCallback(livox_status status, uint8_t handle, ErrorMessage *message) {
  static uint32_t error_message_count = 0;
  if (message != NULL) {
    ++error_message_count;
    if (0 == (error_message_count % 100)) {
      printf("handle: %u\n", handle);
      printf("temp_status : %u\n", message->lidar_error_code.temp_status);
      printf("volt_status : %u\n", message->lidar_error_code.volt_status);
      printf("motor_status : %u\n", message->lidar_error_code.motor_status);
      printf("dirty_warn : %u\n", message->lidar_error_code.dirty_warn);
      printf("firmware_err : %u\n", message->lidar_error_code.firmware_err);
      printf("pps_status : %u\n", message->lidar_error_code.device_status);
      printf("fan_status : %u\n", message->lidar_error_code.fan_status);
      printf("self_heating : %u\n", message->lidar_error_code.self_heating);
      printf("ptp_status : %u\n", message->lidar_error_code.ptp_status);
      printf("time_sync_status : %u\n", message->lidar_error_code.time_sync_status);
      printf("system_status : %u\n", message->lidar_error_code.system_status);
    }
  }
}

/** Receiving point cloud data from Livox LiDAR. */
void GetLidarData(uint8_t handle, LivoxEthPacket *data, uint32_t data_num, void *client_data) {
  static uint32_t point_count = 0;
  if (!data) {
    // printf("Get empty data.");
    return;
  }
  if (++point_count % 2000 == 0) {
    printf("Get Data, handle: %d, data_num: %d, data_type: %d\n",
      handle, data_num, data->data_type);
    std::chrono::time_point<std::chrono::system_clock> time_point;
    time_point = std::chrono::system_clock::now();
    std::time_t ttp = std::chrono::system_clock::to_time_t(time_point);
    std::cout << "time: " << std::ctime(&ttp);
  }

  if (data) {
    data_recveive_count[handle] ++ ;
    if (data_recveive_count[handle] % 100 == 0) {
      /** Parsing the timestamp and the point cloud data. */
      uint64_t cur_timestamp = *((uint64_t *)(data->timestamp));
      if(data ->data_type == kCartesian) {
        LivoxRawPoint *p_point_data = (LivoxRawPoint *)data->data;
      }else if ( data ->data_type == kSpherical) {
        LivoxSpherPoint *p_point_data = (LivoxSpherPoint *)data->data;
      }else if ( data ->data_type == kExtendCartesian) {
        LivoxExtendRawPoint *p_point_data = (LivoxExtendRawPoint *)data->data;
      }else if ( data ->data_type == kExtendSpherical) {
        LivoxExtendSpherPoint *p_point_data = (LivoxExtendSpherPoint *)data->data;
      }else if ( data ->data_type == kDualExtendCartesian) {
        LivoxDualExtendRawPoint *p_point_data = (LivoxDualExtendRawPoint *)data->data;
      }else if ( data ->data_type == kDualExtendSpherical) {
        LivoxDualExtendSpherPoint *p_point_data = (LivoxDualExtendSpherPoint *)data->data;
      }else if ( data ->data_type == kImu) {
        LivoxImuPoint *p_point_data = (LivoxImuPoint *)data->data;
      }else if ( data ->data_type == kTripleExtendCartesian) {
        LivoxTripleExtendRawPoint *p_point_data = (LivoxTripleExtendRawPoint *)data->data;
      }else if ( data ->data_type == kTripleExtendSpherical) {
        LivoxTripleExtendSpherPoint *p_point_data = (LivoxTripleExtendSpherPoint *)data->data;
      }
    }
  }
  printf("data_type %d packet num %d\n", data->data_type, data_recveive_count[handle]);
}

/** Callback function of starting sampling. */
void OnSampleCallback(livox_status status, uint8_t handle, uint8_t response, void *data) {
  printf("OnSampleCallback statue %d handle %d response %d \n", status, handle, response);
  if (status == kStatusSuccess) {
    is_sampling.store(true);
    if (response != 0) {
      devices[handle].device_state = kDeviceStateConnect;
    }
  } else if (status == kStatusTimeout) {
    devices[handle].device_state = kDeviceStateConnect;
  }
}

/** Callback function of stopping sampling. */
void OnStopSampleCallback(livox_status status, uint8_t handle, uint8_t response, void *data) {
  is_sampling.store(false);
}

/** Query the firmware version of Livox LiDAR. */
void OnDeviceInformation(livox_status status, uint8_t handle, DeviceInformationResponse *ack, void *data) {
  if (status != kStatusSuccess) {
    printf("Device Query Informations Failed %d\n", status);
  }
  if (ack) {
    printf("firm ver: %d.%d.%d.%d\n",
           ack->firmware_version[0],
           ack->firmware_version[1],
           ack->firmware_version[2],
           ack->firmware_version[3]);
  }
}

void LidarConnect(const DeviceInfo *info) {
  uint8_t handle = info->handle;
  QueryDeviceInformation(handle, OnDeviceInformation, NULL);
  if (devices[handle].device_state == kDeviceStateDisconnect) {
    devices[handle].device_state = kDeviceStateConnect;
    devices[handle].info = *info;
  }
}

void LidarDisConnect(const DeviceInfo *info) {
  uint8_t handle = info->handle;
  devices[handle].device_state = kDeviceStateDisconnect;
}

void LidarStateChange(const DeviceInfo *info) {
  uint8_t handle = info->handle;
  devices[handle].info = *info;
}

/** Callback function of changing of device state. */
void OnDeviceInfoChange(const DeviceInfo *info, DeviceEvent type) {
  if (info == NULL) {
    return;
  }

  uint8_t handle = info->handle;
  if (handle >= kMaxLidarCount) {
    return;
  }

  if (type == kEventConnect) {
    LidarConnect(info);
    printf("[WARNING] Lidar sn: [%s] Connect!!!\n", info->broadcast_code);
  } else if (type == kEventDisconnect) {
    LidarDisConnect(info);
    printf("[WARNING] Lidar sn: [%s] Disconnect!!!\n", info->broadcast_code);
  } else if (type == kEventStateChange) {
    LidarStateChange(info);
    printf("[WARNING] Lidar sn: [%s] StateChange!!!\n", info->broadcast_code);
  }

  if (devices[handle].device_state == kDeviceStateConnect) {
    printf("Device Working State %d\n", devices[handle].info.state);
    if (devices[handle].info.state == kLidarStateInit) {
      printf("Device State Change Progress %u\n", devices[handle].info.status.progress);
    } else {
      printf("Device State Error Code 0X%08x\n", devices[handle].info.status.status_code.error_code);
    }
    printf("Device feature %d\n", devices[handle].info.feature);
    SetErrorMessageCallback(handle, OnLidarErrorStatusCallback);
    if (devices[handle].info.state == kLidarStateNormal) {
      LidarStartSampling(handle, OnSampleCallback, NULL);
      devices[handle].device_state = kDeviceStateSampling;
    }
  }
}

/** Callback function when broadcast message received.
 * You need to add listening device broadcast code and set the point cloud data callback in this function.
 */
void OnDeviceBroadcast(const BroadcastDeviceInfo *info) {
  static bool is_initialized = false;
  static std::mutex mtx;

  {
    std::lock_guard<std::mutex> guard(mtx);
    if (is_initialized) {
      // printf("Found another Lidar(%s), but support only one... \n", info->broadcast_code);
      return;
    }

    if (info == NULL || info->dev_type == kDeviceTypeHub) {
      // printf("Invalid broadcast info.");
      return;
    }
    printf("Receive Broadcast Code: %s\n", info->broadcast_code);

    /* connect specific lidar, if specified. */
    if (lidar_count > 0) {
      bool found = false;
      int i = 0;
      for (i = 0; i < lidar_count; ++i) {
        if (strncmp(info->broadcast_code, broadcast_code_list[i], kBroadcastCodeSize) == 0) {
          found = true;
          break;
        }
      }
      if (!found) {
        return;
      }
    }

    bool result = false;
    uint8_t handle = 0;
    result = AddLidarToConnect(info->broadcast_code, &handle);
    if (result == kStatusSuccess) {
      /** Set the point cloud data for a specific Livox LiDAR. */
      // SetDataCallback(handle, GetLidarData, NULL);
      devices[handle].handle = handle;
      devices[handle].device_state = kDeviceStateDisconnect;
    }
    is_initialized = true;

    /* Fill up LvxDeviceInfo */
    LvxDeviceInfo lvx_info;
    memcpy(lvx_info.lidar_broadcast_code, info->broadcast_code, 16);
    lvx_info.device_type = 3; // Horizon
    lvx_info.lidar_id = handle;
    lvx_info.extrinsic_enable = 1; //enable extrinsic calculate
    lvx_info.roll = 0.0;
    lvx_info.pitch = 0.0;
    lvx_info.yaw = 0.0;
    lvx_info.x = 0.0;
    lvx_info.y = 0.0;
    lvx_info.z = 0.0;
    AddDeviceInfo(&lvx_info, kSupportedLidarNumber);
  }

}

std::vector<std::vector<std::vector<PACKAGE_POINT>>> input_vectors;
std::vector<std::vector<uint64_t>> time_stamp_vectors;

int main(int argc, const char *argv[]) {
  printf("Livox SDK (industrial) is initializing... \n ");
  /* Initialize Livox-SDK */
  if (!Init()) {
    printf("Failed to initialize Livox SDK.");
    return -1;
  }
  printf("Successfully initialize Livox SDK.");

  SetLvxRecordDir("./");
  /** Set the callback function receiving broadcast message from Livox LiDAR. */
  SetBroadcastCallback(OnDeviceBroadcast);
  /** Set the callback function called when device state change,
   * which means connection/disconnection and changing of LiDAR state.
   */
  SetDeviceStateUpdateCallback(OnDeviceInfoChange);

  /** Start the device discovering routine. */
  if (!Start()) {
    Uninit();
    return -1;
  }

  //* waiting for the sampling ready
  while (!is_sampling.load()) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  printf("Start to record file. \n");
  StartRecordFile(LIVOX_FILE_LVX3_PPT);
  std::this_thread::sleep_for(std::chrono::seconds(kRecordingTime));
  StopRecordLvxFile();
  printf("Stoped recording file. \n");

  for (uint32_t i = 0; i < kMaxLidarCount; ++i) {
    if (devices[i].device_state == kDeviceStateSampling) {
      /** Stop the sampling of Livox LiDAR. */
      LidarStopSampling(devices[i].handle, OnStopSampleCallback, NULL);
    }
  }

  /** Uninitialize Livox-SDK. */
  Uninit();
  printf("Livox Lvx File Demo End!\n");
  return 0;
}
