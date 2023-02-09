#include "devicemonitoringserver.h"
#include <handlers/abstractaction.h>
#include <handlers/abstractmessagehandler.h>
#include <handlers/abstractnewconnectionhandler.h>
#include <server/abstractconnection.h>
#include <servermock/connectionservermock.h>

DeviceMonitoringServer::DeviceMonitoringServer(AbstractConnectionServer* connectionServer) :
    m_connectionServer(connectionServer)
{
    struct NewConnectionHandler : public AbstractNewConnectionHandler
    {
    public:
        NewConnectionHandler(DeviceMonitoringServer* server) :
            m_server(server) {}
        void operator()(AbstractConnection* conn) final
        {
            m_server->onNewIncomingConnection(conn);
        }

    private:
        DeviceMonitoringServer* m_server = nullptr;
    };
    m_connectionServer->setNewConnectionHandler(new NewConnectionHandler(this));

    auto* messageEncoder = new MessageEncoder;
    m_encoder = messageEncoder;

    auto* messageSerialiser = new MessageSerialiser;
    m_serial = messageSerialiser;

    auto* commandcenter = new CommandCenter;
    m_commandcenter = commandcenter;
}

DeviceMonitoringServer::~DeviceMonitoringServer()
{
    delete m_connectionServer;

    delete m_serial;
    delete m_commandcenter;
}

void DeviceMonitoringServer::setDeviceWorkSchedule(const DeviceWorkSchedule& Schedule)
{
    //TO DO
    DeviceWorkSchedule Schedule1 = Schedule;
    //m_commandcenter->RegisterDevice(m_this_deviceId);
    m_commandcenter->SetSchedule(Schedule1);
}

bool DeviceMonitoringServer::listen(uint64_t serverId)
{
    return m_connectionServer->listen(serverId);
}

void DeviceMonitoringServer::sendMessage(uint64_t deviceId, const std::string& message)
{
    auto* conn = m_connectionServer->connection(deviceId);
    if (conn)
        conn->sendMessage(message);
}

void DeviceMonitoringServer::onMessageReceived(uint64_t deviceId, const std::string& message)
{
    //TO DO

    std::cout << "DeviceMonitoringServer::onMessageReceived: " << "Send Message = " << message << std::endl;
    std::string Message = message;

    m_this_deviceId = deviceId;

    Message = m_encoder->decode(Message);

    std::cout << "DeviceMonitoringServer::onMessageReceived: " << "Send MessageDecode = " << Message << std::endl;

    std::string Messagefromserver = Message;
    //std::string Messagetoserver = "";

    std::string Message_from_ComCent = m_commandcenter->GetMessage(deviceId, Messagefromserver);

    std::cout << "DeviceMonitoringServer::onMessageReceived: " << "Send MessagefromComCent = " << Message_from_ComCent << std::endl;

    sendMessage(deviceId, Message_from_ComCent);
}

void DeviceMonitoringServer::setEncodingAlgoritm(BaseEncoderExecutor *EncodeAlgoritm)
{
    m_encoder->registration_algorithm(EncodeAlgoritm);
}

void DeviceMonitoringServer::onDisconnected(uint64_t /*clientId*/)
{
    // TODO, если нужен
}

void DeviceMonitoringServer::onNewIncomingConnection(AbstractConnection* conn)
{
    addMessageHandler(conn);
    addDisconnectedHandler(conn);
}

void DeviceMonitoringServer::addMessageHandler(AbstractConnection* conn)
{
    struct MessageHandler : public AbstractMessageHandler
    {
        MessageHandler(DeviceMonitoringServer* server, uint64_t clientId) :
            m_server(server), m_clientId(clientId) {}

    private:
        void operator()(const std::string& message) final
        {
            m_server->onMessageReceived(m_clientId, message);
        }

    private:
        DeviceMonitoringServer* m_server = nullptr;
        uint64_t m_clientId = 0;
    };
    const auto clientId = conn->peerId();
    conn->setMessageHandler(new MessageHandler(this, clientId));
}

void DeviceMonitoringServer::addDisconnectedHandler(AbstractConnection* conn)
{
    struct DisconnectedHandler : public AbstractAction
    {
        DisconnectedHandler(DeviceMonitoringServer* server, uint64_t clientId) :
            m_server(server), m_clientId(clientId) {}

    private:
        void operator()() final
        {
            m_server->onDisconnected(m_clientId);
        }

    private:
        DeviceMonitoringServer* m_server = nullptr;
        uint64_t m_clientId = 0;
    };
    const auto clientId = conn->peerId();
    conn->setDisconnectedHandler(new DisconnectedHandler(this, clientId));
}
