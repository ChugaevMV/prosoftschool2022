#include "connectionchannel.h"
#include "taskqueue.h"
#include <handlers/abstractaction.h>
#include <handlers/abstractmessagehandler.h>

#include <cassert>

#include <iostream>

namespace
{

struct SendMessageTask final : public AbstractTask
{
    SendMessageTask(std::string message, ConnectionChannel* channel) :
        m_message(std::move(message)), m_channel(channel) {}

    void operator()() final
    {
        auto* channel = dynamic_cast<ConnectionChannel*>(m_channel.data());
        if (channel)
        {
            //std::cout << "SendMessageTask: " << "Send Message = " << m_message << std::endl;
            channel->onMessageReceived(m_message);
        }
    }

private:
    std::string m_message;
    SafeObjectPointer m_channel;
};

struct DisconnectTask final : public AbstractTask
{
    DisconnectTask(ConnectionChannel* channel) :
        m_channel(channel) {}

    void operator()() final
    {
        auto* channel = dynamic_cast<ConnectionChannel*>(m_channel.data());
        if (channel)
            channel->onDisconnected();
    }

private:
    SafeObjectPointer m_channel;
};

} // namespace

ConnectionChannel::ConnectionChannel(TaskQueue& taskQueue, uint64_t peerId) :
    m_taskQueue(taskQueue), m_peerId(peerId)
{
}

ConnectionChannel::~ConnectionChannel()
{
    disconnectPeer();
}

void ConnectionChannel::sendMessage(const std::string& message)
{
    if (!connected())
        return;
    auto* peerChannel = dynamic_cast<ConnectionChannel*>(m_peerChannel.data());
    if (peerChannel && peerChannel->connected())
    {
        //std::cout << "ConnectionChannel::sendMessage: " << "Send Message = " << message << std::endl;
        m_taskQueue.scheduleTask(new SendMessageTask(message, peerChannel));
    }
}

void ConnectionChannel::connect(ConnectionChannel* peer)
{
    assert(!m_peerChannel && this != peer);
    m_peerChannel = peer;
    m_connected = true;
}

void ConnectionChannel::disconnect()
{
    if (!m_connected)
        return;
    m_connected = false;
    // NOTE: Сперва примем все сообщения, что остались в очереди,
    // затем вызовем обработчик
    m_taskQueue.scheduleTask(new DisconnectTask(this));
    disconnectPeer();
}

void ConnectionChannel::disconnectPeer()
{
    auto* peerChannel = dynamic_cast<ConnectionChannel*>(m_peerChannel.data());
    if (peerChannel)
        peerChannel->disconnect();
}

void ConnectionChannel::setMessageHandler(AbstractMessageHandler* handler)
{
    m_messageHandler = handler;
}

void ConnectionChannel::setDisconnectedHandler(AbstractAction* handler)
{
    m_disconnectedHandler = handler;
}

void ConnectionChannel::onMessageReceived(const std::string& message) const
{
    if (m_messageHandler)
        (*m_messageHandler)(message);
}

void ConnectionChannel::onDisconnected()
{
    if (m_disconnectedHandler)
        (*m_disconnectedHandler)();
}
