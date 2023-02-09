#include "clientconnectionmock.h"
#include "connectionchannel.h"
#include "connectionservermock.h"
#include "taskqueue.h"
#include <handlers/abstractmessagehandler.h>

#include <unordered_map>

#include <iostream>

namespace
{

std::unordered_map<uint64_t, ClientConnectionMock*>& clientsMap()
{
    static std::unordered_map<uint64_t, ClientConnectionMock*> map;
    return map;
}

bool clientAlreadyRegistered(uint64_t id)
{
    return clientsMap().count(id) > 0;
}

void registerClient(uint64_t id, ClientConnectionMock* client)
{
    clientsMap().insert({ id, client });
}

void unregisterClient(uint64_t id)
{
    clientsMap().erase(id);
}

struct ConnectToServerTask final : public AbstractTask
{
    ConnectToServerTask(TaskQueue& taskQueue, uint64_t clientId, uint64_t serverId) :
        m_taskQueue(taskQueue), m_clientId(clientId), m_serverId(serverId) {}

    void operator()() final
    {
        auto* server = ConnectionServerMock::findServer(m_serverId);
        auto* client = ClientConnectionMock::findClient(m_clientId);
        if (server && client)
        {
            auto* serverChannel = new ConnectionChannel(m_taskQueue, m_clientId);
            auto* clientChannel = new ConnectionChannel(m_taskQueue, m_serverId);
            serverChannel->connect(clientChannel);
            clientChannel->connect(serverChannel);
            server->addChannel(serverChannel);
            client->setChannel(clientChannel);
        }
    }

private:
    TaskQueue& m_taskQueue;
    uint64_t m_clientId = 0;
    uint64_t m_serverId = 0;
};

} // namespace

ClientConnectionMock* ClientConnectionMock::findClient(uint64_t id)
{
    const auto& map = clientsMap();
    const auto it = map.find(id);
    return it != map.cend() ? it->second : nullptr;
}

ClientConnectionMock::ClientConnectionMock(TaskQueue& taskQueue) :
    m_taskQueue(taskQueue), m_disconnectedHandler(this)
{
}

ClientConnectionMock::~ClientConnectionMock()
{
    unregisterClient(m_clientId);
    delete m_channel;
    delete m_messageHandler;
    delete m_connectedHandler;
}

bool ClientConnectionMock::bind(uint64_t clientId)
{
    if (clientAlreadyRegistered(clientId) || m_channel || !clientId)
        return false;
    unregisterClient(m_clientId);
    m_clientId = clientId;
    registerClient(m_clientId, this);
    return true;
}

bool ClientConnectionMock::connectToHost(uint64_t serverId)
{
    if (!m_clientId || !serverId)
        return false;
    auto* task = new ConnectToServerTask(m_taskQueue, m_clientId, serverId);
    m_taskQueue.scheduleTask(task);
    return true;
}

void ClientConnectionMock::disconnect()
{
    if (m_channel)
        m_channel->disconnect();
}

uint64_t ClientConnectionMock::peerId() const
{
    return m_channel ? m_channel->peerId() : 0;
}

bool ClientConnectionMock::connected() const
{
    return m_channel && m_channel->connected();
}

void ClientConnectionMock::sendMessage(const std::string& message)
{

    if (m_channel)
    {
        //std::cout << 2 << "Send Message =  " << message << std::endl;
        m_channel->sendMessage(message);
    }

}

void ClientConnectionMock::setDisconnectedHandler(AbstractAction* handler)
{
    m_disconnectedHandler.setCustomDisconnectedHandler(handler);
}

void ClientConnectionMock::setConnectedHandler(AbstractAction* handler)
{
    delete m_connectedHandler;
    m_connectedHandler = handler;
}

void ClientConnectionMock::setMessageHandler(AbstractMessageHandler* handler)
{
    delete m_messageHandler;
    m_messageHandler = handler;
    if (m_channel)
        m_channel->setMessageHandler(m_messageHandler);
}

void ClientConnectionMock::setChannel(ConnectionChannel* channel)
{
    if (m_channel)
    {
        delete channel;
        return;
    }
    m_channel = channel;
    m_channel->setMessageHandler(m_messageHandler);
    m_channel->setDisconnectedHandler(&m_disconnectedHandler);
    if (m_connectedHandler)
        (*m_connectedHandler)();
}

void ClientConnectionMock::onDisconnected()
{
    delete m_channel;
    m_channel = nullptr;
}

void ClientConnectionMock::DisconnectedHandler::setCustomDisconnectedHandler(AbstractAction* handler)
{
    delete m_customDisconnectedHandler;
    m_customDisconnectedHandler = handler;
}

void ClientConnectionMock::DisconnectedHandler::operator()()
{
    if (m_customDisconnectedHandler)
        (*m_customDisconnectedHandler)();
    m_client->onDisconnected();
}
