**Wi-Fi APIs**
================

:link_to_translation:`en:[English]`

.. important::

   The WiFi API v2.0 is the lastest stable WiFi APIs, it's used to deprecate the WiFi API v1.0. All new applications should use WiFi API v2.0.

**Wi-Fi Interface**
--------------------------

The BK WiFi Driver supports following logical WiFi interfaces:

 - BK STA interface
 - BK AP interface
 - BK Monitor interface
 - BK RLK(Raw Link) interface

Each interface can be operated independently, so theretically all interfaces can be started independently. However because of performance and interference consideration, we limit the coexisting of some interfaces.

E.g. if the monitor interface is started, the starting of STA interface will fail, refer to API for detailed limitation of interface coexisting.

**Wi-Fi API Categories**
----------------------------

Most of WiFi APIs can be categoried as:

 - Common APIs

   The common APIs are prefixed with bk_wifi, the APIs may be common for all interfaces or some interfaces, e.g. bk_wifi_init() etc.
 - Interface specific APIs.

   The API name are prefixed with bk_wifi_interface, the interface can be sta, ap or monitor. e.g. bk_wifi_sta_start() etc.
 - Module specific APIs

   The API name are prefixed with bk_wifi_module, the module can be scan or filter etc, e.g. bk_wifi_scan_start() etc. The API has no direct relationship with the interface, or the API caller don't nedto care about on which interface the API is operated. E.g. the scan API can be based on STA interface, it can also based on AP interface, but the caller don't care about it.
 - BK-RLK APIs

   The BK-RLK APIs are prefixed with bk_rlk, the APIs is only common for BK-RLK functional modules. bk_rlk_init() etc.

Common WiFi APIs:
 - :cpp:func:`bk_wifi_init` - init WiFi
 - :cpp:func:`bk_wifi_deinit` - deinit WiFi
 - :cpp:func:`bk_wifi_set_country` - set country code
 - :cpp:func:`bk_wifi_get_country` - get country code
 - :cpp:func:`bk_wifi_send_raw` - send raw 802.11 frame

Interface specific WiFi APIs:
 - :cpp:func:`bk_wifi_sta_start` - start BK STA
 - :cpp:func:`bk_wifi_sta_stop` - stop BK STA
 - :cpp:func:`bk_wifi_sta_set_config` - set **basic** configurations BK STA, such as SSID etc
 - :cpp:func:`bk_wifi_sta_get_config` - get basic configuration of BK STA
 - :cpp:func:`bk_wifi_sta_get_linkstate_with_reason` - get actual link status of BK STA and reason code
 - :cpp:func:`bk_wifi_sta_get_link_status` - get link status of BK STA
 - :cpp:func:`bk_wifi_sta_connect` - connect the BK STA to AP
 - :cpp:func:`bk_wifi_sta_disconnect` - disconnect the Wi-Fi connection
 - :cpp:func:`bk_wifi_sta_pm_enable` - enable STA power management
 - :cpp:func:`bk_wifi_sta_pm_disable` - disable STA power management
 - :cpp:func:`bk_wifi_get_channel` - get current channel ID
 - :cpp:func:`bk_wifi_set_mac_address` - set Wi-Fi MAC address
 - :cpp:func:`bk_wifi_manual_cal_rfcali_status` - get Wi-Fi Calibration status
 - :cpp:func:`bk_wifi_ap_start` - start BK AP
 - :cpp:func:`bk_wifi_ap_stop` - stop BK AP
 - :cpp:func:`bk_wifi_ap_set_config` - set the **basic** configuration of BK AP, such as SSID etc
 - :cpp:func:`bk_wifi_ap_get_config` - get the basic configuration of BK AP
 - :cpp:func:`bk_wifi_ap_get_sta_list` - get the STAs connected to BK AP
 - :cpp:func:`bk_wifi_sta_get_mac` - get STA MAC address
 - :cpp:func:`bk_wifi_ap_get_mac` - get AP MAC address
 - :cpp:func:`bk_wifi_monitor_start` - start the monitor
 - :cpp:func:`bk_wifi_monitor_stop` - stop the monitor
 - :cpp:func:`bk_wifi_monitor_set_config` - set **basic** configuration of the monitor
 - :cpp:func:`bk_wifi_monitor_get_config` - get basic configuration of the monitor
 - :cpp:func:`bk_wifi_monitor_register_cb` - register monitor callback function
 - :cpp:func:`bk_wifi_monitor_set_channel` - set the channel of monitor
 - :cpp:func:`bk_wifi_send_listen_interval_req` - set the listen interval

Module Specific WiFi APIs:
 - :cpp:func:`bk_wifi_scan_start` - start the scan
 - :cpp:func:`bk_wifi_scan_stop` - stop the scan
 - :cpp:func:`bk_wifi_scan_get_result` - get the scan result
 - :cpp:func:`bk_wifi_scan_dump_result` - dump the scan result
 - :cpp:func:`bk_wifi_scan_free_result` - dump the scan result
 - :cpp:func:`bk_wifi_filter_set_config` - set filter configuration
 - :cpp:func:`bk_wifi_filter_register_cb` - register the filter callback function

BK-RLK APIs:
 - :cpp:func:`bk_rlk_init` - init BK-RLK
 - :cpp:func:`bk_rlk_deinit` - deinit BK-RLK
 - :cpp:func:`bk_rlk_register_recv_cb` - register BK-RLK receive callback function
 - :cpp:func:`bk_rlk_ungister_recv_cb` - unregister BK-RLK receive callback function
 - :cpp:func:`bk_rlk_register_send_cb` - register BK-RLK send callback function
 - :cpp:func:`bk_rlk_unregister_send_cb` - unregister BK-RLK send callback function
 - :cpp:func:`bk_rlk_set_channel` - set the channel of BK-RLK
 - :cpp:func:`bk_rlk_send` - send BK-RLK frame
 - :cpp:func:`bk_rlk_send_ex` - send BK-RLK frame
 - :cpp:func:`bk_rlk_add_peer` - add a peer info to peer list
 - :cpp:func:`bk_rlk_del_peer` - delete a peer info from peer list
 - :cpp:func:`bk_rlk_get_peer` - get a peer info from peer list
 - :cpp:func:`bk_rlk_is_peer_exist` - check if a peer info or not exist peer list
 - :cpp:func:`bk_rlk_get_peer_num` - get the peers num connected to BK-RLK
 - :cpp:func:`bk_rlk_set_tx_ac` - set the BK-RLK TX AC
 - :cpp:func:`bk_rlk_set_tx_timeout_ms` - set the BK-RLK TX timeout
 - :cpp:func:`bk_rlk_set_tx_power` - set the BK-RLK TX power
 - :cpp:func:`bk_rlk_set_tx_rate` - set the BK-RLK TX rate
 - :cpp:func:`bk_rlk_set_tx_retry_cnt` - set the BK-RLK TX retry count
 - :cpp:func:`bk_rlk_sleep` - enable BK-RLK power management
 - :cpp:func:`bk_rlk_wakeup` - disable BK-RLK power management

**Compitability and Extension**
-------------------------------------

The WiFi APIs are flexible, easy to be extended and backward compatible. For most of the WiFi configurations, we put some reserved fields in the config struct for future extendence. The API users need to make sure the reserved fields are initialized to 0, otherwise the compatibility may be broken as more fields are added.

**Programing Principle**
-------------------------------

.. important::
  Here is some general principle for WiFi API users:
   - Always init the reserved fields of config stuct to 0
   - Use BK_ERR_CHECK to check the return value of the WiFi API
   - If you are not sure how to use WiFi APIs, study the WiFi example code first
   - If you are not sure how to initialize some fields of config struct, use the default configuration macro to use the config first and then set application specific fields, e.g. use WIFI_DEFAULT_INIT_CONFIG() to init wifi_config_t first.
   - Don't do too much work in WiFi event callback, relay the event to your own application task.

**User Development Model**
---------------------------------

Similar as most popular WiFi driver, the Beken WiFi driver is implemented as event driver. The application call WiFi APIs to operate the WiFi driver and get notified by WiFi event.

**API Reference**
-----------------------

.. include:: ../../_build/inc/wifi.inc
.. include:: ../../_build/inc/raw_link.inc

**API Typedefs**
--------------------

.. include:: ../../_build/inc/wifi_types.inc


