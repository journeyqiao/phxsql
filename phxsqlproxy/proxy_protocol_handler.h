/*
	Tencent is pleased to support the open source community by making PhxSQL available.
	Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.
	Licensed under the GNU General Public License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at
	
	https://opensource.org/licenses/GPL-2.0
	
	Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
*/

#pragma once

#include <string>
#include <sys/socket.h>

#include "phxsqlproxyconfig.h"
#include "group_status_cache.h"

namespace phxsqlproxy {

struct ProxyHdr;

class ProxyProtocolHandler {
 public:
    ProxyProtocolHandler(PHXSqlProxyConfig * config,
                         WorkerConfig_t    * worker_config,
                         GroupStatusCache  * group_status_cache);

    virtual ~ProxyProtocolHandler();

    void SetReqUniqID(uint64_t req_uniq_id);

    void Clear();

 public:
    int ProcessProxyHeader(int fd);

    int SendProxyHeader(int fd);

 private:
    int GetAddrFromFD(int fd);

    int IsProxyHeaderNeed();

    int ParseProxyHeaderV1(const char * hdr, int read_size);

    int ParseProxyHeaderV2(const ProxyHdr & hdr, int read_size);

    int MakeProxyHeaderV1(std::string & header);

    int MakeProxyHeaderV2(std::string & header);

 private:
    uint64_t req_uniq_id_;

    PHXSqlProxyConfig * config_;
    WorkerConfig_t    * worker_config_;
    GroupStatusCache  * group_status_cache_;

    struct sockaddr_storage src_addr_;
    struct sockaddr_storage dst_addr_;
};

}
