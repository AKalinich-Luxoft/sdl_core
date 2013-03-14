#include "../src/../include/JSONHandler/RPC2Objects/NsRPC2Communication/VR/OnLanguageChange.h"
#include "../src/../include/JSONHandler/RPC2Objects/Marshaller.h"

/*
  interface	NsRPC2Communication::VR
  version	1.2
  generated at	Thu Jan 24 06:41:15 2013
  source stamp	Wed Jan 23 13:56:28 2013
  author	robok0der
*/

using namespace NsRPC2Communication::VR;


OnLanguageChange& OnLanguageChange::operator =(const OnLanguageChange& c)
{
  language=c.language;
  return *this;
}


OnLanguageChange::~OnLanguageChange(void)
{
}


OnLanguageChange::OnLanguageChange(void) : 
  RPC2Notification(Marshaller::METHOD_NSRPC2COMMUNICATION_VR__ONLANGUAGECHANGE)
{
}


OnLanguageChange::OnLanguageChange(const OnLanguageChange& c) : RPC2Notification(Marshaller::METHOD_NSRPC2COMMUNICATION_VR__ONLANGUAGECHANGE)
{
  *this=c;
}


const NsSmartDeviceLinkRPCV2::Language& OnLanguageChange::get_language(void)
{
  return language;
}

bool OnLanguageChange::set_language(const NsSmartDeviceLinkRPCV2::Language& language_)
{
  language=language_;
  return true;
}

bool OnLanguageChange::checkIntegrity(void)
{
  return OnLanguageChangeMarshaller::checkIntegrity(*this);
}
