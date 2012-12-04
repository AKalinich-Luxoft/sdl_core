#include "AppMgr/ConnectionHandler.h"
#include "LoggerHelper.hpp"

namespace NsAppManager
{
    log4cplus::Logger ConnectionHandler::mLogger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("ConnectionHandler"));

    /**
     * \brief Returning class instance
     * \return class instance
     */
    ConnectionHandler &ConnectionHandler::getInstance()
    {
        static ConnectionHandler instance;
        return instance;
    }

    /**
     * \brief Sets connection handler instance
     * \param handler connection handler
     */
    void ConnectionHandler::setConnectionHandler(NsConnectionHandler::CConnectionHandler *handler)
    {
        if(!handler)
        {
            LOG4CPLUS_ERROR_EXT(mLogger, "A null pointer is being assigned - is this the intent?");
            return;
        }
        mConnectionHandler = handler;
    }

    /**
     * \brief Gets connection handler instance
     * \return connection handler
     */
    NsConnectionHandler::CConnectionHandler *ConnectionHandler::getConnectionHandler() const
    {
        if(!mConnectionHandler)
        {
            LOG4CPLUS_ERROR_EXT(mLogger, "Connection handler hasn't yet been assigned, but an attempt to retrieve it has been made! Face a core dump soon...(((");
        }
        return mConnectionHandler;
    }

    /**
     * \brief Default class constructor
     */
    ConnectionHandler::ConnectionHandler()
        :mConnectionHandler(0)
    {
    }

    /**
     * \brief Copy constructor
     */
    ConnectionHandler::ConnectionHandler(const ConnectionHandler &)
        :mConnectionHandler(0)
    {
    }

}
