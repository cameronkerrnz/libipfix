#include "lib/ipfix.h"
#include "lib/ipfix_col.h"

int netscaler_fallback_template_count = 29;

fallback_template_t netscaler_fallback_templates[] =
    { { 256
      , 23
      , {  {  0,     138,  4   }  /*  observationPointId                    */
        ,  {  0,     144,  4   }  /*  exportingProcessId                    */
        ,  {  0,     148,  8   }  /*  flowId                                */
        ,  {  5951,  129,  4   }  /*  netscaler_transaction_id              */
        ,  {  5951,  133,  4   }  /*  netscaler_connection_id               */
        ,  {  0,     60,   1   }  /*  ipVersion                             */
        ,  {  0,     4,    1   }  /*  protocolIdentifier                    */
        ,  {  0,     210,  2   }  /*  paddingOctets                         */
        ,  {  0,     8,    4   }  /*  sourceIPv4Address                     */
        ,  {  0,     12,   4   }  /*  destinationIPv4Address                */
        ,  {  0,     7,    2   }  /*  sourceTransportPort                   */
        ,  {  0,     11,   2   }  /*  destinationTransportPort              */
        ,  {  0,     2,    8   }  /*  packetDeltaCount                      */
        ,  {  0,     1,    8   }  /*  octetDeltaCount                       */
        ,  {  0,     6,    1   }  /*  tcpControlBits                        */
        ,  {  5951,  132,  8   }  /*  netscaler_flow_flags                  */
        ,  {  0,     154,  8   }  /*  flowStartMicroseconds                 */
        ,  {  0,     155,  8   }  /*  flowEndMicroseconds                   */
        ,  {  0,     10,   4   }  /*  ingressInterface                      */
        ,  {  0,     14,   4   }  /*  egressInterface                       */
        ,  {  5951,  151,  4   }  /*  netscaler_app_name_app_id             */
        ,  {  5951,  192,  16  }  /*  netscaler_connection_chain_id         */
        ,  {  5951,  193,  1   }  /*  netscaler_connection_chain_hop_count  */
        }
      }
    , { 257
      , 24
      , {  {  0,     138,  4   }  /*  observationPointId                    */
        ,  {  0,     144,  4   }  /*  exportingProcessId                    */
        ,  {  0,     148,  8   }  /*  flowId                                */
        ,  {  5951,  129,  4   }  /*  netscaler_transaction_id              */
        ,  {  5951,  133,  4   }  /*  netscaler_connection_id               */
        ,  {  0,     60,   1   }  /*  ipVersion                             */
        ,  {  0,     4,    1   }  /*  protocolIdentifier                    */
        ,  {  0,     210,  2   }  /*  paddingOctets                         */
        ,  {  0,     8,    4   }  /*  sourceIPv4Address                     */
        ,  {  0,     12,   4   }  /*  destinationIPv4Address                */
        ,  {  0,     7,    2   }  /*  sourceTransportPort                   */
        ,  {  0,     11,   2   }  /*  destinationTransportPort              */
        ,  {  0,     2,    8   }  /*  packetDeltaCount                      */
        ,  {  0,     1,    8   }  /*  octetDeltaCount                       */
        ,  {  0,     6,    1   }  /*  tcpControlBits                        */
        ,  {  5951,  132,  8   }  /*  netscaler_flow_flags                  */
        ,  {  0,     154,  8   }  /*  flowStartMicroseconds                 */
        ,  {  0,     155,  8   }  /*  flowEndMicroseconds                   */
        ,  {  5951,  128,  4   }  /*  netscaler_round_trip_time             */
        ,  {  0,     14,   4   }  /*  egressInterface                       */
        ,  {  0,     10,   4   }  /*  ingressInterface                      */
        ,  {  5951,  151,  4   }  /*  netscaler_app_name_app_id             */
        ,  {  5951,  192,  16  }  /*  netscaler_connection_chain_id         */
        ,  {  5951,  193,  1   }  /*  netscaler_connection_chain_hop_count  */
        }
      }
    , { 258
      , 38    /* version specific? see "unknown_bytes" IE below */
      , {  {  0,     138,  4      }  /*  observationPointId                    */
        ,  {  0,     144,  4      }  /*  exportingProcessId                    */
        ,  {  0,     148,  8      }  /*  flowId                                */
        ,  {  5951,  129,  4      }  /*  netscaler_transaction_id              */
        ,  {  5951,  133,  4      }  /*  netscaler_connection_id               */
        ,  {  5951,  999,  2      }  /*  unknown_bytes                         */
        ,  {  0,     60,   1      }  /*  ipVersion                             */
        ,  {  0,     4,    1      }  /*  protocolIdentifier                    */
        ,  {  0,     210,  2      }  /*  paddingOctets                         */
        ,  {  0,     8,    4      }  /*  sourceIPv4Address                     */
        ,  {  0,     12,   4      }  /*  destinationIPv4Address                */
        ,  {  0,     7,    2      }  /*  sourceTransportPort                   */
        ,  {  0,     11,   2      }  /*  destinationTransportPort              */
        ,  {  0,     2,    8      }  /*  packetDeltaCount                      */
        ,  {  0,     1,    8      }  /*  octetDeltaCount                       */
        ,  {  0,     6,    1      }  /*  tcpControlBits                        */
        ,  {  5951,  132,  8      }  /*  netscaler_flow_flags                  */
        ,  {  0,     154,  8      }  /*  flowStartMicroseconds                 */
        ,  {  0,     155,  8      }  /*  flowEndMicroseconds                   */
        ,  {  0,     10,   4      }  /*  ingressInterface                      */
        ,  {  0,     14,   4      }  /*  egressInterface                       */
        ,  {  5951,  151,  4      }  /*  netscaler_app_name_app_id             */
        ,  {  5951,  171,  4      }  /*  netscaler_app_unit_name_app_id        */
        ,  {  5951,  158,  8      }  /*  netscaler_http_res_forw_fb            */
        ,  {  5951,  170,  8      }  /*  netscaler_http_res_forw_lb            */
        ,  {  5951,  192,  16     }  /*  netscaler_connection_chain_id         */
        ,  {  5951,  193,  1      }  /*  netscaler_connection_chain_hop_count  */
     /* ,  {  5951,  205,  65535  }      netscaler_aaa_username                */
        ,  {  5951,  130,  65535  }  /*  netscaler_http_req_url                */
        ,  {  5951,  131,  65535  }  /*  netscaler_http_req_cookie             */
        ,  {  5951,  140,  65535  }  /*  netscaler_http_req_referer            */
        ,  {  5951,  141,  65535  }  /*  netscaler_http_req_method             */
        ,  {  5951,  142,  65535  }  /*  netscaler_http_req_host               */
        ,  {  5951,  143,  65535  }  /*  netscaler_http_req_user_agent         */
        ,  {  5951,  183,  65535  }  /*  netscaler_http_content_type           */
        ,  {  5951,  185,  65535  }  /*  netscaler_http_req_authorization      */
        ,  {  5951,  186,  65535  }  /*  netscaler_http_req_via                */
        ,  {  5951,  190,  65535  }  /*  netscaler_http_req_x_forwarded_for    */
        ,  {  5951,  267,  65535  }  /*  netscaler_http_domain_name            */
        }
      }
    , { 259 
      , 23
      , {  {  0,     138,  4   }  /*  observationPointId                    */
        ,  {  0,     144,  4   }  /*  exportingProcessId                    */
        ,  {  0,     148,  8   }  /*  flowId                                */
        ,  {  5951,  129,  4   }  /*  netscaler_transaction_id              */
        ,  {  5951,  133,  4   }  /*  netscaler_connection_id               */
        ,  {  0,     60,   1   }  /*  ipVersion                             */
        ,  {  0,     4,    1   }  /*  protocolIdentifier                    */
        ,  {  0,     210,  2   }  /*  paddingOctets                         */
        ,  {  0,     27,   16  }  /*  sourceIPv6Address                     */
        ,  {  0,     28,   16  }  /*  destinationIPv6Address                */
        ,  {  0,     7,    2   }  /*  sourceTransportPort                   */
        ,  {  0,     11,   2   }  /*  destinationTransportPort              */
        ,  {  0,     2,    8   }  /*  packetDeltaCount                      */
        ,  {  0,     1,    8   }  /*  octetDeltaCount                       */
        ,  {  0,     6,    1   }  /*  tcpControlBits                        */
        ,  {  5951,  132,  8   }  /*  netscaler_flow_flags                  */
        ,  {  0,     154,  8   }  /*  flowStartMicroseconds                 */
        ,  {  0,     155,  8   }  /*  flowEndMicroseconds                   */
        ,  {  0,     10,   4   }  /*  ingressInterface                      */
        ,  {  0,     14,   4   }  /*  egressInterface                       */
        ,  {  5951,  151,  4   }  /*  netscaler_app_name_app_id             */
        ,  {  5951,  192,  16  }  /*  netscaler_connection_chain_id         */
        ,  {  5951,  193,  1   }  /*  netscaler_connection_chain_hop_count  */
        }
      }
    , { 260 
      , 24
      , {  {  0,     138,  4   }  /*  observationPointId                    */
        ,  {  0,     144,  4   }  /*  exportingProcessId                    */
        ,  {  0,     148,  8   }  /*  flowId                                */
        ,  {  5951,  129,  4   }  /*  netscaler_transaction_id              */
        ,  {  5951,  133,  4   }  /*  netscaler_connection_id               */
        ,  {  0,     60,   1   }  /*  ipVersion                             */
        ,  {  0,     4,    1   }  /*  protocolIdentifier                    */
        ,  {  0,     210,  2   }  /*  paddingOctets                         */
        ,  {  0,     27,   16  }  /*  sourceIPv6Address                     */
        ,  {  0,     28,   16  }  /*  destinationIPv6Address                */
        ,  {  0,     7,    2   }  /*  sourceTransportPort                   */
        ,  {  0,     11,   2   }  /*  destinationTransportPort              */
        ,  {  0,     2,    8   }  /*  packetDeltaCount                      */
        ,  {  0,     1,    8   }  /*  octetDeltaCount                       */
        ,  {  0,     6,    1   }  /*  tcpControlBits                        */
        ,  {  5951,  132,  8   }  /*  netscaler_flow_flags                  */
        ,  {  0,     154,  8   }  /*  flowStartMicroseconds                 */
        ,  {  0,     155,  8   }  /*  flowEndMicroseconds                   */
        ,  {  5951,  128,  4   }  /*  netscaler_round_trip_time             */
        ,  {  0,     14,   4   }  /*  egressInterface                       */
        ,  {  0,     10,   4   }  /*  ingressInterface                      */
        ,  {  5951,  151,  4   }  /*  netscaler_app_name_app_id             */
        ,  {  5951,  192,  16  }  /*  netscaler_connection_chain_id         */
        ,  {  5951,  193,  1   }  /*  netscaler_connection_chain_hop_count  */
        }
      }
    , { 261
      , 40
      , {  {  0,     138,  4      }  /*  observationPointId                                      */
        ,  {  0,     144,  4      }  /*  exportingProcessId                                      */
        ,  {  0,     148,  8      }  /*  flowId                                                  */
        ,  {  5951,  129,  4      }  /*  netscaler_transaction_id                                */
        ,  {  5951,  133,  4      }  /*  netscaler_connection_id                                 */
        ,  {  0,     60,   1      }  /*  ipVersion                                               */
        ,  {  0,     4,    1      }  /*  protocolIdentifier                                      */
        ,  {  0,     210,  2      }  /*  paddingOctets                                           */
        ,  {  0,     27,   16     }  /*  sourceIPv6Address                                       */
        ,  {  0,     28,   16     }  /*  destinationIPv6Address                                  */
        ,  {  0,     7,    2      }  /*  sourceTransportPort                                     */
        ,  {  0,     11,   2      }  /*  destinationTransportPort                                */
        ,  {  0,     2,    8      }  /*  packetDeltaCount                                        */
        ,  {  0,     1,    8      }  /*  octetDeltaCount                                         */
        ,  {  0,     6,    1      }  /*  tcpControlBits                                          */
        ,  {  5951,  132,  8      }  /*  netscaler_flow_flags                                    */
        ,  {  0,     154,  8      }  /*  flowStartMicroseconds                                   */
        ,  {  0,     155,  8      }  /*  flowEndMicroseconds                                     */
        ,  {  0,     10,   4      }  /*  ingressInterface                                        */
        ,  {  0,     14,   4      }  /*  egressInterface                                         */
        ,  {  5951,  151,  4      }  /*  netscaler_app_name_app_id                               */
        ,  {  5951,  171,  4      }  /*  netscaler_app_unit_name_app_id                          */
        ,  {  5951,  158,  8      }  /*  netscaler_http_res_forw_fb                              */
        ,  {  5951,  170,  8      }  /*  netscaler_http_res_forw_lb                              */
        ,  {  5951,  192,  16     }  /*  netscaler_connection_chain_id                           */
        ,  {  5951,  193,  1      }  /*  netscaler_connection_chain_hop_count                    */
        ,  {  5951,  268,  4      }  /*  netscaler_cache_redir_client_connection_core_id         */
        ,  {  5951,  269,  4      }  /*  netscaler_cache_redir_client_connection_transaction_id  */
        ,  {  5951,  205,  65535  }  /*  netscaler_aaa_username                                  */
        ,  {  5951,  130,  65535  }  /*  netscaler_http_req_url                                  */
        ,  {  5951,  131,  65535  }  /*  netscaler_http_req_cookie                               */
        ,  {  5951,  140,  65535  }  /*  netscaler_http_req_referer                              */
        ,  {  5951,  141,  65535  }  /*  netscaler_http_req_method                               */
        ,  {  5951,  142,  65535  }  /*  netscaler_http_req_host                                 */
        ,  {  5951,  143,  65535  }  /*  netscaler_http_req_user_agent                           */
        ,  {  5951,  183,  65535  }  /*  netscaler_http_content_type                             */
        ,  {  5951,  185,  65535  }  /*  netscaler_http_req_authorization                        */
        ,  {  5951,  186,  65535  }  /*  netscaler_http_req_via                                  */
        ,  {  5951,  190,  65535  }  /*  netscaler_http_req_x_forwarded_for                      */
        ,  {  5951,  267,  65535  }  /*  netscaler_http_domain_name                              */
        }
      }
    , { 262
      , 39
      , {  {  0,     138,  4      }  /*  observationPointId              */
        ,  {  0,     144,  4      }  /*  exportingProcessId              */
        ,  {  0,     148,  8      }  /*  flowId                          */
        ,  {  5951,  129,  4      }  /*  netscaler_transaction_id        */
        ,  {  5951,  133,  4      }  /*  netscaler_connection_id         */
        ,  {  0,     60,   1      }  /*  ipVersion                       */
        ,  {  0,     4,    1      }  /*  protocolIdentifier              */
        ,  {  0,     210,  2      }  /*  paddingOctets                   */
        ,  {  0,     8,    4      }  /*  sourceIPv4Address               */
        ,  {  0,     12,   4      }  /*  destinationIPv4Address          */
        ,  {  0,     7,    2      }  /*  sourceTransportPort             */
        ,  {  0,     11,   2      }  /*  destinationTransportPort        */
        ,  {  0,     2,    8      }  /*  packetDeltaCount                */
        ,  {  0,     1,    8      }  /*  octetDeltaCount                 */
        ,  {  0,     6,    1      }  /*  tcpControlBits                  */
        ,  {  5951,  132,  8      }  /*  netscaler_flow_flags            */
        ,  {  0,     154,  8      }  /*  flowStartMicroseconds           */
        ,  {  0,     155,  8      }  /*  flowEndMicroseconds             */
        ,  {  0,     10,   4      }  /*  ingressInterface                */
        ,  {  0,     14,   4      }  /*  egressInterface                 */
        ,  {  5951,  144,  2      }  /*  netscaler_http_rsp_status       */
        ,  {  5951,  145,  8      }  /*  netscaler_http_rsp_len          */
        ,  {  5951,  146,  8      }  /*  netscaler_server_ttfb           */
        ,  {  5951,  147,  8      }  /*  netscaler_server_ttlb           */
        ,  {  5951,  151,  4      }  /*  netscaler_app_name_app_id       */
        ,  {  5951,  161,  4      }  /*  netscaler_main_page_id          */
        ,  {  5951,  162,  4      }  /*  netscaler_main_page_coreid      */
        ,  {  5951,  153,  8      }  /*  netscaler_http_req_rcv_fb       */
        ,  {  5951,  156,  8      }  /*  netscaler_http_req_forw_fb      */
        ,  {  5951,  157,  8      }  /*  netscaler_http_res_rcv_fb       */
        ,  {  5951,  159,  8      }  /*  netscaler_http_req_rcv_lb       */
        ,  {  5951,  160,  8      }  /*  netscaler_http_req_forw_lb      */
        ,  {  5951,  169,  8      }  /*  netscaler_http_res_rcv_lb       */
        ,  {  5951,  182,  4      }  /*  netscaler_client_rtt            */
        ,  {  5951,  205,  65535  }  /*  netscaler_aaa_username          */
        ,  {  5951,  183,  65535  }  /*  netscaler_http_content_type     */
        ,  {  5951,  187,  65535  }  /*  netscaler_http_res_location     */
        ,  {  5951,  188,  65535  }  /*  netscaler_http_res_set_cookie   */
        ,  {  5951,  189,  65535  }  /*  netscaler_http_res_set_cookie2  */
        }
      }
    , { 263
      , 39
      , {  {  0,     138,  4      }  /*  observationPointId              */
        ,  {  0,     144,  4      }  /*  exportingProcessId              */
        ,  {  0,     148,  8      }  /*  flowId                          */
        ,  {  5951,  129,  4      }  /*  netscaler_transaction_id        */
        ,  {  5951,  133,  4      }  /*  netscaler_connection_id         */
        ,  {  0,     60,   1      }  /*  ipVersion                       */
        ,  {  0,     4,    1      }  /*  protocolIdentifier              */
        ,  {  0,     210,  2      }  /*  paddingOctets                   */
        ,  {  0,     27,   16     }  /*  sourceIPv6Address               */
        ,  {  0,     28,   16     }  /*  destinationIPv6Address          */
        ,  {  0,     7,    2      }  /*  sourceTransportPort             */
        ,  {  0,     11,   2      }  /*  destinationTransportPort        */
        ,  {  0,     2,    8      }  /*  packetDeltaCount                */
        ,  {  0,     1,    8      }  /*  octetDeltaCount                 */
        ,  {  0,     6,    1      }  /*  tcpControlBits                  */
        ,  {  5951,  132,  8      }  /*  netscaler_flow_flags            */
        ,  {  0,     154,  8      }  /*  flowStartMicroseconds           */
        ,  {  0,     155,  8      }  /*  flowEndMicroseconds             */
        ,  {  0,     10,   4      }  /*  ingressInterface                */
        ,  {  0,     14,   4      }  /*  egressInterface                 */
        ,  {  5951,  144,  2      }  /*  netscaler_http_rsp_status       */
        ,  {  5951,  145,  8      }  /*  netscaler_http_rsp_len          */
        ,  {  5951,  146,  8      }  /*  netscaler_server_ttfb           */
        ,  {  5951,  147,  8      }  /*  netscaler_server_ttlb           */
        ,  {  5951,  151,  4      }  /*  netscaler_app_name_app_id       */
        ,  {  5951,  161,  4      }  /*  netscaler_main_page_id          */
        ,  {  5951,  162,  4      }  /*  netscaler_main_page_coreid      */
        ,  {  5951,  153,  8      }  /*  netscaler_http_req_rcv_fb       */
        ,  {  5951,  156,  8      }  /*  netscaler_http_req_forw_fb      */
        ,  {  5951,  157,  8      }  /*  netscaler_http_res_rcv_fb       */
        ,  {  5951,  159,  8      }  /*  netscaler_http_req_rcv_lb       */
        ,  {  5951,  160,  8      }  /*  netscaler_http_req_forw_lb      */
        ,  {  5951,  169,  8      }  /*  netscaler_http_res_rcv_lb       */
        ,  {  5951,  182,  4      }  /*  netscaler_client_rtt            */
        ,  {  5951,  205,  65535  }  /*  netscaler_aaa_username          */
        ,  {  5951,  183,  65535  }  /*  netscaler_http_content_type     */
        ,  {  5951,  187,  65535  }  /*  netscaler_http_res_location     */
        ,  {  5951,  188,  65535  }  /*  netscaler_http_res_set_cookie   */
        ,  {  5951,  189,  65535  }  /*  netscaler_http_res_set_cookie2  */
        }
      }
    , { 264 
      , 5
      , {  {  5951,  134,  1      }  /*  netscaler_syslog_priority   */
        ,  {  0,     210,  1      }  /*  paddingOctets               */
        ,  {  0,     210,  2      }  /*  paddingOctets               */
        ,  {  5951,  136,  4      }  /*  netscaler_syslog_timestamp  */
        ,  {  5951,  135,  65535  }  /*  netscaler_syslog_message    */
        }
      }
    , { 266
      , 4
      , {  {  0,     144,  4      }  /*  exportingProcessId                            */
        ,  {  5951,  129,  4      }  /*  netscaler_transaction_id                      */
        ,  {  5951,  168,  65535  }  /*  netscaler_http_client_interaction_end_time    */
        ,  {  5951,  163,  65535  }  /*  netscaler_http_client_interaction_start_time  */
        }
      }
    , { 267
      , 4
      , {  {  0,     144,  4      }  /*  exportingProcessId                       */
        ,  {  5951,  129,  4      }  /*  netscaler_transaction_id                 */
        ,  {  5951,  164,  65535  }  /*  netscaler_http_client_render_end_time    */
        ,  {  5951,  165,  65535  }  /*  netscaler_http_client_render_start_time  */
        }
      }
    , { 269
      , 25
      , {  {  0,     138,  4      }  /*  observationPointId          */
        ,  {  0,     144,  4      }  /*  exportingProcessId          */
        ,  {  0,     148,  8      }  /*  flowId                      */
        ,  {  5951,  129,  4      }  /*  netscaler_transaction_id    */
        ,  {  5951,  133,  4      }  /*  netscaler_connection_id     */
        ,  {  0,     60,   1      }  /*  ipVersion                   */
        ,  {  0,     61,   1      }  /*  flowDirection               */
        ,  {  0,     4,    1      }  /*  protocolIdentifier          */
        ,  {  0,     6,    1      }  /*  tcpControlBits              */
        ,  {  0,     8,    4      }  /*  sourceIPv4Address           */
        ,  {  0,     12,   4      }  /*  destinationIPv4Address      */
        ,  {  0,     7,    2      }  /*  sourceTransportPort         */
        ,  {  0,     11,   2      }  /*  destinationTransportPort    */
        ,  {  0,     2,    8      }  /*  packetDeltaCount            */
        ,  {  0,     1,    8      }  /*  octetDeltaCount             */
        ,  {  5951,  132,  8      }  /*  netscaler_flow_flags        */
        ,  {  0,     154,  8      }  /*  flowStartMicroseconds       */
        ,  {  0,     155,  8      }  /*  flowEndMicroseconds         */
        ,  {  0,     10,   4      }  /*  ingressInterface            */
        ,  {  0,     14,   4      }  /*  egressInterface             */
        ,  {  5951,  151,  4      }  /*  netscaler_app_name_app_id   */
        ,  {  5951,  174,  1      }  /*  netscaler_db_protocol_name  */
        ,  {  5951,  173,  1      }  /*  netscaler_db_req_type       */
        ,  {  0,     210,  2      }  /*  paddingOctets               */
        ,  {  5951,  178,  65535  }  /*  netscaler_db_req_string     */
        }
      }
    , { 270 
      , 29
      , {  {  0,     138,  4      }  /*  observationPointId               */
        ,  {  0,     144,  4      }  /*  exportingProcessId               */
        ,  {  0,     148,  8      }  /*  flowId                           */
        ,  {  5951,  129,  4      }  /*  netscaler_transaction_id         */
        ,  {  5951,  133,  4      }  /*  netscaler_connection_id          */
        ,  {  0,     60,   1      }  /*  ipVersion                        */
        ,  {  0,     61,   1      }  /*  flowDirection                    */
        ,  {  0,     4,    1      }  /*  protocolIdentifier               */
        ,  {  0,     6,    1      }  /*  tcpControlBits                   */
        ,  {  0,     8,    4      }  /*  sourceIPv4Address                */
        ,  {  0,     12,   4      }  /*  destinationIPv4Address           */
        ,  {  0,     7,    2      }  /*  sourceTransportPort              */
        ,  {  0,     11,   2      }  /*  destinationTransportPort         */
        ,  {  0,     2,    8      }  /*  packetDeltaCount                 */
        ,  {  0,     1,    8      }  /*  octetDeltaCount                  */
        ,  {  5951,  132,  8      }  /*  netscaler_flow_flags             */
        ,  {  0,     154,  8      }  /*  flowStartMicroseconds            */
        ,  {  0,     155,  8      }  /*  flowEndMicroseconds              */
        ,  {  0,     10,   4      }  /*  ingressInterface                 */
        ,  {  0,     14,   4      }  /*  egressInterface                  */
        ,  {  5951,  151,  4      }  /*  netscaler_app_name_app_id        */
        ,  {  5951,  146,  8      }  /*  netscaler_server_ttfb            */
        ,  {  5951,  147,  8      }  /*  netscaler_server_ttlb            */
        ,  {  5951,  174,  1      }  /*  netscaler_db_protocol_name       */
        ,  {  0,     210,  1      }  /*  paddingOctets                    */
        ,  {  0,     210,  2      }  /*  paddingOctets                    */
        ,  {  5951,  180,  8      }  /*  netscaler_db_resp_status         */
        ,  {  5951,  181,  8      }  /*  netscaler_db_resp_length         */
        ,  {  5951,  179,  65535  }  /*  netscaler_db_resp_status_string  */
        }
      }
    , { 271
      , 26
      , {  {  0,     138,  4      }  /*  observationPointId                    */
        ,  {  0,     144,  4      }  /*  exportingProcessId                    */
        ,  {  0,     148,  8      }  /*  flowId                                */
        ,  {  5951,  133,  4      }  /*  netscaler_connection_id               */
        ,  {  0,     60,   1      }  /*  ipVersion                             */
        ,  {  0,     4,    1      }  /*  protocolIdentifier                    */
        ,  {  0,     210,  2      }  /*  paddingOctets                         */
        ,  {  0,     8,    4      }  /*  sourceIPv4Address                     */
        ,  {  0,     12,   4      }  /*  destinationIPv4Address                */
        ,  {  0,     7,    2      }  /*  sourceTransportPort                   */
        ,  {  0,     11,   2      }  /*  destinationTransportPort              */
        ,  {  5951,  200,  16     }  /*  netscaler_ica_session_guid            */
        ,  {  5951,  247,  4      }  /*  netscaler_ica_device_serial_no        */
        ,  {  5951,  248,  16     }  /*  netscaler_msi_client_cookie           */
        ,  {  5951,  249,  8      }  /*  netscaler_ica_flags                   */
        ,  {  5951,  209,  4      }  /*  netscaler_ica_session_setup_time      */
        ,  {  5951,  203,  4      }  /*  netscaler_ica_client_ip               */
        ,  {  5951,  202,  2      }  /*  netscaler_ica_client_type             */
        ,  {  5951,  208,  2      }  /*  netscaler_ica_client_launcher         */
        ,  {  5951,  192,  16     }  /*  netscaler_connection_chain_id         */
        ,  {  5951,  193,  1      }  /*  netscaler_connection_chain_hop_count  */
        ,  {  5951,  201,  65535  }  /*  NETSCALE_ICA_CLIENT_VERSION           */
        ,  {  5951,  204,  65535  }  /*  netscaler_ica_client_hostname         */
        ,  {  5951,  250,  65535  }  /*  netscaler_ica_username                */
        ,  {  5951,  207,  65535  }  /*  netscaler_ica_domain_name             */
        ,  {  5951,  210,  65535  }  /*  netscaler_ica_server_name             */
        }
      }
    , { 272
      , 34
      , {  {  0,     138,  4   }  /*  observationPointId                            */
        ,  {  0,     144,  4   }  /*  exportingProcessId                            */
        ,  {  0,     148,  8   }  /*  flowId                                        */
        ,  {  5951,  133,  4   }  /*  netscaler_connection_id                       */
        ,  {  0,     60,   1   }  /*  ipVersion                                     */
        ,  {  0,     4,    1   }  /*  protocolIdentifier                            */
        ,  {  0,     210,  2   }  /*  paddingOctets                                 */
        ,  {  5951,  200,  16  }  /*  netscaler_ica_session_guid                    */
        ,  {  5951,  247,  4   }  /*  netscaler_ica_device_serial_no                */
        ,  {  5951,  248,  16  }  /*  netscaler_msi_client_cookie                   */
        ,  {  5951,  249,  8   }  /*  netscaler_ica_flags                           */
        ,  {  5951,  214,  1   }  /*  netscaler_ica_session_reconnects              */
        ,  {  5951,  215,  4   }  /*  netscaler_ica_rtt                             */
        ,  {  5951,  216,  4   }  /*  netscaler_ica_client_side_rx_bytes            */
        ,  {  5951,  217,  4   }  /*  netscaler_ica_client_side_tx_bytes            */
        ,  {  5951,  219,  2   }  /*  netscaler_ica_client_side_packets_retransmit  */
        ,  {  5951,  220,  2   }  /*  netscaler_ica_server_side_packets_retransmit  */
        ,  {  5951,  221,  4   }  /*  netscaler_ica_client_side_rtt                 */
        ,  {  5951,  222,  4   }  /*  netscaler_ica_server_side_rtt                 */
        ,  {  5951,  243,  4   }  /*  netscaler_ica_client_side_jitter              */
        ,  {  5951,  244,  4   }  /*  netscaler_ica_server_side_jitter              */
        ,  {  5951,  254,  4   }  /*  netscaler_ica_network_update_start_time       */
        ,  {  5951,  255,  4   }  /*  netscaler_ica_network_update_end_time         */
        ,  {  5951,  256,  4   }  /*  netscaler_ica_client_side_srtt                */
        ,  {  5951,  257,  4   }  /*  netscaler_ica_server_side_srtt                */
        ,  {  5951,  258,  4   }  /*  netscaler_ica_client_side_delay               */
        ,  {  5951,  259,  4   }  /*  netscaler_ica_server_side_delay               */
        ,  {  5951,  260,  4   }  /*  netscaler_ica_host_delay                      */
        ,  {  5951,  261,  2   }  /*  netscaler_ica_clientside_window_size          */
        ,  {  5951,  262,  2   }  /*  netscaler_ica_server_side_window_size         */
        ,  {  5951,  263,  2   }  /*  netscaler_ica_client_side_rto_count           */
        ,  {  5951,  264,  2   }  /*  netscaler_ica_server_side_rto_count           */
        ,  {  5951,  265,  4   }  /*  netscaler_ica_l7_client_latency               */
        ,  {  5951,  266,  4   }  /*  netscaler_ica_l7_server_latency               */
        }
      }
    , { 273 
      , 23
      , {  {  0,     138,  4   }  /*  observationPointId                      */
        ,  {  0,     144,  4   }  /*  exportingProcessId                      */
        ,  {  0,     148,  8   }  /*  flowId                                  */
        ,  {  5951,  133,  4   }  /*  netscaler_connection_id                 */
        ,  {  0,     60,   1   }  /*  ipVersion                               */
        ,  {  0,     4,    1   }  /*  protocolIdentifier                      */
        ,  {  0,     210,  2   }  /*  paddingOctets                           */
        ,  {  5951,  200,  16  }  /*  netscaler_ica_session_guid              */
        ,  {  5951,  247,  4   }  /*  netscaler_ica_device_serial_no          */
        ,  {  5951,  248,  16  }  /*  netscaler_msi_client_cookie             */
        ,  {  5951,  249,  8   }  /*  netscaler_ica_flags                     */
        ,  {  5951,  223,  4   }  /*  netscaler_ica_session_update_begin_sec  */
        ,  {  5951,  224,  4   }  /*  netscaler_ica_session_update_end_sec    */
        ,  {  5951,  225,  4   }  /*  netscaler_ica_channel_id_1              */
        ,  {  5951,  226,  4   }  /*  netscaler_ica_channel_id_1_bytes        */
        ,  {  5951,  227,  4   }  /*  netscaler_ica_channel_id_2              */
        ,  {  5951,  228,  4   }  /*  netscaler_ica_channel_id_2_bytes        */
        ,  {  5951,  229,  4   }  /*  netscaler_ica_channel_id_3              */
        ,  {  5951,  230,  4   }  /*  netscaler_ica_channel_id_3_bytes        */
        ,  {  5951,  231,  4   }  /*  netscaler_ica_channel_id_4              */
        ,  {  5951,  232,  4   }  /*  netscaler_ica_channel_id_4_bytes        */
        ,  {  5951,  233,  4   }  /*  netscaler_ica_channel_id_5              */
        ,  {  5951,  234,  4   }  /*  netscaler_ica_channel_id_5_bytes        */
        }
      }
    , { 274 
      , 22
      , {  {  0,     138,  4      }  /*  observationPointId                      */
        ,  {  0,     144,  4      }  /*  exportingProcessId                      */
        ,  {  0,     148,  8      }  /*  flowId                                  */
        ,  {  5951,  133,  4      }  /*  netscaler_connection_id                 */
        ,  {  0,     60,   1      }  /*  ipVersion                               */
        ,  {  0,     4,    1      }  /*  protocolIdentifier                      */
        ,  {  0,     210,  2      }  /*  paddingOctets                           */
        ,  {  0,     8,    4      }  /*  sourceIPv4Address                       */
        ,  {  0,     12,   4      }  /*  destinationIPv4Address                  */
        ,  {  0,     7,    2      }  /*  sourceTransportPort                     */
        ,  {  0,     11,   2      }  /*  destinationTransportPort                */
        ,  {  5951,  200,  16     }  /*  netscaler_ica_session_guid              */
        ,  {  5951,  247,  4      }  /*  netscaler_ica_device_serial_no          */
        ,  {  5951,  248,  16     }  /*  netscaler_msi_client_cookie             */
        ,  {  5951,  249,  8      }  /*  netscaler_ica_flags                     */
        ,  {  5951,  235,  2      }  /*  netscaler_ica_connection_priority       */
        ,  {  5951,  236,  4      }  /*  netscaler_application_startup_duration  */
        ,  {  5951,  237,  2      }  /*  netscaler_ica_launch_mechanism          */
        ,  {  5951,  239,  4      }  /*  netscaler_application_startup_time      */
        ,  {  5951,  245,  4      }  /*  netscaler_ica_app_process_id            */
        ,  {  5951,  238,  65535  }  /*  netscaler_ica_application_name          */
        ,  {  5951,  246,  65535  }  /*  netscaler_ica_app_module_path           */
        }
      }
    , { 275 
      , 14
      , {  {  0,     138,  4   }  /*  observationPointId                          */
        ,  {  0,     144,  4   }  /*  exportingProcessId                          */
        ,  {  0,     148,  8   }  /*  flowId                                      */
        ,  {  5951,  133,  4   }  /*  netscaler_connection_id                     */
        ,  {  0,     60,   1   }  /*  ipVersion                                   */
        ,  {  0,     4,    1   }  /*  protocolIdentifier                          */
        ,  {  0,     210,  2   }  /*  paddingOctets                               */
        ,  {  5951,  200,  16  }  /*  netscaler_ica_session_guid                  */
        ,  {  5951,  247,  4   }  /*  netscaler_ica_device_serial_no              */
        ,  {  5951,  248,  16  }  /*  netscaler_msi_client_cookie                 */
        ,  {  5951,  249,  8   }  /*  netscaler_ica_flags                         */
        ,  {  5951,  240,  2   }  /*  netscaler_ica_application_termination_type  */
        ,  {  5951,  245,  4   }  /*  netscaler_ica_app_process_id                */
        ,  {  5951,  241,  4   }  /*  netscaler_ica_application_termination_time  */
        }
      }
    , { 276 
      , 12
      , {  {  0,     138,  4   }  /*  observationPointId              */
        ,  {  0,     144,  4   }  /*  exportingProcessId              */
        ,  {  0,     148,  8   }  /*  flowId                          */
        ,  {  5951,  133,  4   }  /*  netscaler_connection_id         */
        ,  {  0,     60,   1   }  /*  ipVersion                       */
        ,  {  0,     4,    1   }  /*  protocolIdentifier              */
        ,  {  0,     210,  2   }  /*  paddingOctets                   */
        ,  {  5951,  200,  16  }  /*  netscaler_ica_session_guid      */
        ,  {  5951,  247,  4   }  /*  netscaler_ica_device_serial_no  */
        ,  {  5951,  248,  16  }  /*  netscaler_msi_client_cookie     */
        ,  {  5951,  249,  8   }  /*  netscaler_ica_flags             */
        ,  {  5951,  242,  4   }  /*  netscaler_ica_session_end_time  */
        }
      }
    , { 277 
      , 5
      , {  {  0,     138,  4  }  /*  observationPointId                  */
        ,  {  0,     144,  4  }  /*  exportingProcessId                  */
        ,  {  5951,  251,  1  }  /*  netscaler_license_type              */
        ,  {  5951,  252,  8  }  /*  netscaler_max_license_count         */
        ,  {  5951,  253,  8  }  /*  netscaler_current_license_consumed  */
        }
      }
    , { 278 
      , 24
      , {  {  0,     138,  4      }  /*  observationPointId                    */
        ,  {  0,     144,  4      }  /*  exportingProcessId                    */
        ,  {  0,     148,  8      }  /*  flowId                                */
        ,  {  5951,  129,  4      }  /*  netscaler_transaction_id              */
        ,  {  5951,  133,  4      }  /*  netscaler_connection_id               */
        ,  {  0,     60,   1      }  /*  ipVersion                             */
        ,  {  0,     4,    1      }  /*  protocolIdentifier                    */
        ,  {  0,     210,  2      }  /*  paddingOctets                         */
        ,  {  0,     8,    4      }  /*  sourceIPv4Address                     */
        ,  {  0,     12,   4      }  /*  destinationIPv4Address                */
        ,  {  0,     7,    2      }  /*  sourceTransportPort                   */
        ,  {  0,     11,   2      }  /*  destinationTransportPort              */
        ,  {  0,     2,    8      }  /*  packetDeltaCount                      */
        ,  {  0,     1,    8      }  /*  octetDeltaCount                       */
        ,  {  0,     6,    1      }  /*  tcpControlBits                        */
        ,  {  5951,  132,  8      }  /*  netscaler_flow_flags                  */
        ,  {  0,     154,  8      }  /*  flowStartMicroseconds                 */
        ,  {  0,     155,  8      }  /*  flowEndMicroseconds                   */
        ,  {  0,     10,   4      }  /*  ingressInterface                      */
        ,  {  0,     14,   4      }  /*  egressInterface                       */
        ,  {  5951,  151,  4      }  /*  netscaler_app_name_app_id             */
        ,  {  5951,  192,  16     }  /*  netscaler_connection_chain_id         */
        ,  {  5951,  193,  1      }  /*  netscaler_connection_chain_hop_count  */
        ,  {  5951,  205,  65535  }  /*  netscaler_aaa_username                */
        }
      }
    , { 279
      , 24
      , {  {  0,     138,  4      }  /*  observationPointId                    */
        ,  {  0,     144,  4      }  /*  exportingProcessId                    */
        ,  {  0,     148,  8      }  /*  flowId                                */
        ,  {  5951,  129,  4      }  /*  netscaler_transaction_id              */
        ,  {  5951,  133,  4      }  /*  netscaler_connection_id               */
        ,  {  0,     60,   1      }  /*  ipVersion                             */
        ,  {  0,     4,    1      }  /*  protocolIdentifier                    */
        ,  {  0,     210,  2      }  /*  paddingOctets                         */
        ,  {  0,     27,   16     }  /*  sourceIPv6Address                     */
        ,  {  0,     28,   16     }  /*  destinationIPv6Address                */
        ,  {  0,     7,    2      }  /*  sourceTransportPort                   */
        ,  {  0,     11,   2      }  /*  destinationTransportPort              */
        ,  {  0,     2,    8      }  /*  packetDeltaCount                      */
        ,  {  0,     1,    8      }  /*  octetDeltaCount                       */
        ,  {  0,     6,    1      }  /*  tcpControlBits                        */
        ,  {  5951,  132,  8      }  /*  netscaler_flow_flags                  */
        ,  {  0,     154,  8      }  /*  flowStartMicroseconds                 */
        ,  {  0,     155,  8      }  /*  flowEndMicroseconds                   */
        ,  {  0,     10,   4      }  /*  ingressInterface                      */
        ,  {  0,     14,   4      }  /*  egressInterface                       */
        ,  {  5951,  151,  4      }  /*  netscaler_app_name_app_id             */
        ,  {  5951,  192,  16     }  /*  netscaler_connection_chain_id         */
        ,  {  5951,  193,  1      }  /*  netscaler_connection_chain_hop_count  */
        ,  {  5951,  205,  65535  }  /*  netscaler_aaa_username                */
        }
      }
    , { 280 
      , 24
      , {  {  0,     138,  4  }  /*  observationPointId        */
        ,  {  0,     144,  4  }  /*  exportingProcessId        */
        ,  {  5951,  129,  4  }  /*  netscaler_transaction_id  */
        ,  {  5951,  132,  8  }  /*  netscaler_flow_flags      */
        }
      }
    , { 281 
      , 40
      , {  {  0,     138,  4      }  /*  observationPointId                    */
        ,  {  0,     144,  4      }  /*  exportingProcessId                    */
        ,  {  0,     148,  8      }  /*  flowId                                */
        ,  {  5951,  129,  4      }  /*  netscaler_transaction_id              */
        ,  {  5951,  133,  4      }  /*  netscaler_connection_id               */
        ,  {  0,     60,   1      }  /*  ipVersion                             */
        ,  {  0,     4,    1      }  /*  protocolIdentifier                    */
        ,  {  0,     210,  2      }  /*  paddingOctets                         */
        ,  {  0,     8,    4      }  /*  sourceIPv4Address                     */
        ,  {  0,     12,   4      }  /*  destinationIPv4Address                */
        ,  {  0,     7,    2      }  /*  sourceTransportPort                   */
        ,  {  0,     11,   2      }  /*  destinationTransportPort              */
        ,  {  0,     2,    8      }  /*  packetDeltaCount                      */
        ,  {  0,     1,    8      }  /*  octetDeltaCount                       */
        ,  {  0,     6,    1      }  /*  tcpControlBits                        */
        ,  {  5951,  132,  8      }  /*  netscaler_flow_flags                  */
        ,  {  0,     154,  8      }  /*  flowStartMicroseconds                 */
        ,  {  0,     155,  8      }  /*  flowEndMicroseconds                   */
        ,  {  5951,  128,  4      }  /*  netscaler_round_trip_time             */
        ,  {  0,     14,   4      }  /*  egressInterface                       */
        ,  {  0,     10,   4      }  /*  ingressInterface                      */
        ,  {  5951,  151,  4      }  /*  netscaler_app_name_app_id             */
        ,  {  5951,  192,  16     }  /*  netscaler_connection_chain_id         */
        ,  {  5951,  193,  1      }  /*  netscaler_connection_chain_hop_count  */
        ,  {  5951,  144,  2      }  /*  netscaler_http_rsp_status             */
        ,  {  5951,  145,  8      }  /*  netscaler_http_rsp_len                */
        ,  {  5951,  161,  4      }  /*  netscaler_main_page_id                */
        ,  {  5951,  162,  4      }  /*  netscaler_main_page_coreid            */
        ,  {  5951,  153,  8      }  /*  netscaler_http_req_rcv_fb             */
        ,  {  5951,  156,  8      }  /*  netscaler_http_req_forw_fb            */
        ,  {  5951,  157,  8      }  /*  netscaler_http_res_rcv_fb             */
        ,  {  5951,  159,  8      }  /*  netscaler_http_req_rcv_lb             */
        ,  {  5951,  160,  8      }  /*  netscaler_http_req_forw_lb            */
        ,  {  5951,  169,  8      }  /*  netscaler_http_res_rcv_lb             */
        ,  {  5951,  182,  4      }  /*  netscaler_client_rtt                  */
        ,  {  5951,  205,  65535  }  /*  netscaler_aaa_username                */
        ,  {  5951,  183,  65535  }  /*  netscaler_http_content_type           */
        ,  {  5951,  187,  65535  }  /*  netscaler_http_res_location           */
        ,  {  5951,  188,  65535  }  /*  netscaler_http_res_set_cookie         */
        ,  {  5951,  189,  65535  }  /*  netscaler_http_res_set_cookie2        */
        }
      }
    , { 282 
      , 46
      , {  {  0,     138,  4  }  /*  observationPointId        */
        ,  {  0,     144,  4  }  /*  exportingProcessId        */
        ,  {  5951,  129,  4  }  /*  netscaler_transaction_id  */
        ,  {  5951,  270,  4  }  /*  5951_270                  */
        ,  {  5951,  271,  4  }  /*  5951_271                  */
        ,  {  5951,  272,  4  }  /*  5951_272                  */
        ,  {  5951,  273,  4  }  /*  5951_273                  */
        ,  {  5951,  274,  4  }  /*  5951_274                  */
        ,  {  5951,  275,  4  }  /*  5951_275                  */
        ,  {  5951,  276,  4  }  /*  5951_276                  */
        ,  {  5951,  277,  4  }  /*  5951_277                  */
        ,  {  5951,  278,  4  }  /*  5951_278                  */
        ,  {  5951,  279,  4  }  /*  5951_279                  */
        ,  {  5951,  280,  4  }  /*  5951_280                  */
        ,  {  5951,  281,  4  }  /*  5951_281                  */
        ,  {  5951,  282,  4  }  /*  5951_282                  */
        ,  {  5951,  283,  4  }  /*  5951_283                  */
        ,  {  5951,  284,  4  }  /*  5951_284                  */
        ,  {  5951,  285,  4  }  /*  5951_285                  */
        ,  {  5951,  286,  4  }  /*  5951_286                  */
        ,  {  5951,  287,  4  }  /*  5951_287                  */
        ,  {  5951,  288,  4  }  /*  5951_288                  */
        ,  {  5951,  289,  4  }  /*  5951_289                  */
        ,  {  5951,  290,  4  }  /*  5951_290                  */
        ,  {  5951,  291,  4  }  /*  5951_291                  */
        ,  {  5951,  292,  4  }  /*  5951_292                  */
        ,  {  5951,  293,  4  }  /*  5951_293                  */
        ,  {  5951,  294,  4  }  /*  5951_294                  */
        ,  {  5951,  295,  4  }  /*  5951_295                  */
        ,  {  5951,  296,  4  }  /*  5951_296                  */
        ,  {  5951,  297,  4  }  /*  5951_297                  */
        ,  {  5951,  298,  4  }  /*  5951_298                  */
        ,  {  5951,  299,  4  }  /*  5951_299                  */
        ,  {  5951,  300,  4  }  /*  5951_300                  */
        ,  {  5951,  301,  4  }  /*  5951_301                  */
        ,  {  5951,  302,  4  }  /*  5951_302                  */
        ,  {  5951,  303,  4  }  /*  5951_303                  */
        ,  {  5951,  304,  4  }  /*  5951_304                  */
        ,  {  5951,  305,  4  }  /*  5951_305                  */
        ,  {  5951,  306,  4  }  /*  5951_306                  */
        ,  {  5951,  307,  4  }  /*  5951_307                  */
        ,  {  5951,  308,  4  }  /*  5951_308                  */
        ,  {  5951,  309,  4  }  /*  5951_309                  */
        ,  {  5951,  310,  4  }  /*  5951_310                  */
        ,  {  5951,  311,  4  }  /*  5951_311                  */
        ,  {  5951,  312,  4  }  /*  5951_312                  */
        }
      }
    , { 283 
      , 7
      , {  {  0,     138,  4      }  /*  observationPointId        */
        ,  {  0,     144,  4      }  /*  exportingProcessId        */
        ,  {  5951,  129,  4      }  /*  netscaler_transaction_id  */
        ,  {  5951,  315,  4      }  /*  5951_315                  */
        ,  {  5951,  313,  4      }  /*  5951_313                  */
        ,  {  5951,  314,  4      }  /*  5951_314                  */
        ,  {  5951,  316,  65535  }  /*  5951_316                  */
        }
      }
    , { 284 
      , 1
      , {  {  5951,  319,  8  }  /*  5951_319  */
        }
      }
    , { 285
      , 3
      , {  {  0,     138,  4  }  /*  observationPointId                                      */
        ,  {  5951,  268,  4  }  /*  netscaler_cache_redir_client_connection_core_id         */
        ,  {  5951,  269,  4  }  /*  netscaler_cache_redir_client_connection_transaction_id  */
        }
      }
    , { 286 
      , 5
      , {  {   0,     138,  4  }   /*  observationPointId        */
        ,  {   0,     144,  4  }   /*  exportingProcessId        */
        ,  {   5951,  129,  4  }   /*  netscaler_transaction_id  */
        ,  {   5951,  317,  4  }   /*  5951_317                  */
        ,  {   5951,  318,  4  }   /*  5951_318                  */
        }
      }
    };

