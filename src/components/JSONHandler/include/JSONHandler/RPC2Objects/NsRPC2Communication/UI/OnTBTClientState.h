#ifndef NSRPC2COMMUNICATION_UI_ONTBTCLIENTSTATE_INCLUDE
#define NSRPC2COMMUNICATION_UI_ONTBTCLIENTSTATE_INCLUDE

#include "JSONHandler/RPC2Notification.h"

#include "../include/JSONHandler/SDLRPCObjects/V2/TBTState.h"

/*
  interface	NsRPC2Communication::UI
  version	1.2
  generated at	Thu Jan 24 06:41:15 2013
  source stamp	Wed Jan 23 13:56:28 2013
  author	robok0der
*/

namespace NsRPC2Communication
{
  namespace UI
  {

    class OnTBTClientState : public ::NsRPC2Communication::RPC2Notification
    {
    public:

      OnTBTClientState(const OnTBTClientState& c);
      OnTBTClientState(void);

      OnTBTClientState& operator =(const OnTBTClientState&);

      virtual ~OnTBTClientState(void);

      bool checkIntegrity(void);

// getters
      const NsSmartDeviceLinkRPCV2::TBTState& get_state(void);
      int get_appId(void);

// setters
      bool set_state(const NsSmartDeviceLinkRPCV2::TBTState& state);
      bool set_appId(int appId);

    private:
      friend class OnTBTClientStateMarshaller;

      NsSmartDeviceLinkRPCV2::TBTState state;
      int appId;

    };
  }
}

#endif
