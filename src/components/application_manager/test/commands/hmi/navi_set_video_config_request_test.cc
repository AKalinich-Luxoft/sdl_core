/*
 * Copyright (c) 2017 Xevo Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of the Ford Motor Company nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "application_manager/commands/hmi/navi_set_video_config_request.h"

#include "gtest/gtest.h"
#include "utils/shared_ptr.h"
#include "smart_objects/smart_object.h"
#include "application_manager/smart_object_keys.h"
#include "application_manager/commands/command_request_test.h"
#include "application_manager/mock_application_manager.h"
#include "application_manager/hmi_interfaces.h"
#include "application_manager/mock_hmi_interface.h"
#include "application_manager/event_engine/event.h"

namespace test {
namespace components {
namespace commands_test {
namespace hmi_commands_test {
namespace navi_set_video_config_request {

using ::testing::_;
using ::testing::ReturnRef;
namespace am = ::application_manager;
using am::commands::MessageSharedPtr;
using am::commands::NaviSetVideoConfigRequest;
using am::event_engine::Event;

namespace {
const hmi_apis::FunctionID::eType kEventID =
    hmi_apis::FunctionID::Navigation_SetVideoConfig;
}  // namespace

typedef SharedPtr<NaviSetVideoConfigRequest> NaviSetVideoConfigRequestPtr;

class NaviSetVideoConfigRequestTest
    : public CommandRequestTest<CommandsTestMocks::kIsNice> {
 public:
  NaviSetVideoConfigRequestTest() {
    mock_app_ptr_ = CreateMockApp();
    ON_CALL(app_mngr_, hmi_interfaces())
        .WillByDefault(ReturnRef(mock_hmi_interfaces_));
    ON_CALL(app_mngr_, application_by_hmi_app(_))
        .WillByDefault(Return(mock_app_ptr_));
  }

  MOCK(am::MockHmiInterfaces) mock_hmi_interfaces_;
  MockAppPtr mock_app_ptr_;
};

TEST_F(NaviSetVideoConfigRequestTest, OnEvent_SUCCESS) {
  NaviSetVideoConfigRequestPtr command =
      CreateCommand<NaviSetVideoConfigRequest>();

  MessageSharedPtr event_msg = CreateMessage();
  (*event_msg)[am::strings::params][am::hmi_response::code] =
      hmi_apis::Common_Result::SUCCESS;
  Event event(kEventID);
  event.set_smart_object(*event_msg);

  std::vector<std::string> empty;
  EXPECT_CALL(*mock_app_ptr_, OnNaviSetVideoConfigDone(true, empty)).Times(1);

  command->on_event(event);
}

static bool ValidateList(std::vector<std::string>& expected,
                         std::vector<std::string>& actual) {
  if (expected.size() != actual.size()) {
    return false;
  }
  for (unsigned int i = 0; i < expected.size(); i++) {
    std::string& param = expected[i];
    unsigned int j;
    for (j = 0; j < actual.size(); j++) {
      if (param == actual[j]) {
        break;
      }
    }
    if (j == actual.size()) {
      // not found
      return false;
    }
  }
  return true;
}

TEST_F(NaviSetVideoConfigRequestTest, OnEvent_FAILURE) {
  MessageSharedPtr request_msg = CreateMessage();
  (*request_msg)[am::strings::msg_params][am::strings::config] =
      smart_objects::SmartObject(smart_objects::SmartType_Array);
  (*request_msg)[am::strings::msg_params][am::strings::config]
                [am::strings::protocol] =
                    hmi_apis::Common_VideoStreamingProtocol::RTP;
  (*request_msg)[am::strings::msg_params][am::strings::config]
                [am::strings::codec] =
                    hmi_apis::Common_VideoStreamingCodec::H265;
  (*request_msg)[am::strings::msg_params][am::strings::config]
                [am::strings::height] = 640;
  (*request_msg)[am::strings::msg_params][am::strings::config]
                [am::strings::width] = 480;

  NaviSetVideoConfigRequestPtr command =
      CreateCommand<NaviSetVideoConfigRequest>(request_msg);

  MessageSharedPtr event_msg = CreateMessage();
  (*event_msg)[am::strings::params][am::hmi_response::code] =
      hmi_apis::Common_Result::REJECTED;

  (*event_msg)[am::strings::msg_params]["rejectedParams"] =
      smart_objects::SmartObject(smart_objects::SmartType_Array);
  (*event_msg)[am::strings::msg_params]["rejectedParams"][0] = "codec";
  (*event_msg)[am::strings::msg_params]["rejectedParams"][1] = "protocol";
  Event event(kEventID);
  event.set_smart_object(*event_msg);

  std::vector<std::string> rejected_params;
  EXPECT_CALL(*mock_app_ptr_, OnNaviSetVideoConfigDone(false, _))
      .WillOnce(SaveArg<1>(&rejected_params));

  command->on_event(event);

  ASSERT_EQ(2u, rejected_params.size());
  std::vector<std::string> expected_list;
  expected_list.push_back(std::string("protocol"));
  expected_list.push_back(std::string("codec"));
  ASSERT_TRUE(ValidateList(expected_list, rejected_params));
}

TEST_F(NaviSetVideoConfigRequestTest, OnEvent_FAILURE_WithoutParams) {
  NaviSetVideoConfigRequestPtr command =
      CreateCommand<NaviSetVideoConfigRequest>();

  MessageSharedPtr event_msg = CreateMessage();
  (*event_msg)[am::strings::params][am::hmi_response::code] =
      hmi_apis::Common_Result::REJECTED;

  Event event(kEventID);
  event.set_smart_object(*event_msg);

  std::vector<std::string> empty;
  EXPECT_CALL(*mock_app_ptr_, OnNaviSetVideoConfigDone(false, empty)).Times(1);

  command->on_event(event);
}

TEST_F(NaviSetVideoConfigRequestTest, OnTimeout) {
  NaviSetVideoConfigRequestPtr command =
      CreateCommand<NaviSetVideoConfigRequest>();

  std::vector<std::string> empty;
  EXPECT_CALL(*mock_app_ptr_, OnNaviSetVideoConfigDone(false, empty)).Times(1);

  EXPECT_CALL(app_mngr_, TerminateRequest(_, _, _)).Times(1);

  command->onTimeOut();
}

}  // namespace navi_set_video_config_request
}  // namespace hmi_commands_test
}  // namespace commands_test
}  // namespace components
}  // namespace test
