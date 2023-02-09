#include "devicemock.h"
#include <handlers/abstractaction.h>
#include <handlers/abstractmessagehandler.h>
#include <server/abstractclientconnection.h>

static std::string respond;

DeviceMock::DeviceMock(AbstractClientConnection* clientConnection) :
    m_clientConnection(clientConnection)
{
    struct ConnectedHandler : public AbstractAction
    {
    public:
        ConnectedHandler(DeviceMock* client) :
            m_client(client) {}
        void operator()() final
        {
            m_client->onConnected();
        }

    private:
        DeviceMock* m_client = nullptr;
    };
    m_clientConnection->setConnectedHandler(new ConnectedHandler(this));

    struct DisconnectedHandler : public AbstractAction
    {
    public:
        DisconnectedHandler(DeviceMock* client) :
            m_client(client) {}
        void operator()() final
        {
            m_client->onDisconnected();
        }

    private:
        DeviceMock* m_client = nullptr;
    };
    m_clientConnection->setDisconnectedHandler(new DisconnectedHandler(this));

    struct MessageHandler : public AbstractMessageHandler
    {
        MessageHandler(DeviceMock* client) :
            m_client(client) {}

    private:
        void operator()(const std::string& message) final
        {
            m_client->onMessageReceived(message);
        }

    private:
        DeviceMock* m_client = nullptr;
    };
    m_clientConnection->setMessageHandler(new MessageHandler(this));

    auto* messageSerialiser = new MessageSerialiser;
    m_serial = messageSerialiser;

    auto* messageEncoder = new MessageEncoder;
    m_encoder = messageEncoder;
}

DeviceMock::~DeviceMock()
{
    delete m_clientConnection;

    delete m_serial;
    delete m_encoder;
}

bool DeviceMock::bind(uint64_t deviceId)
{
    return m_clientConnection->bind(deviceId);
}

bool DeviceMock::connectToServer(uint64_t serverId)
{
    return m_clientConnection->connectToHost(serverId);
}

void DeviceMock::sendMessage(const std::string& message) const
{
    std::cout << "sendMessage: " << "Send Message = " << message << std::endl;
    m_clientConnection->sendMessage(message);

}

void DeviceMock::onMessageReceived(const std::string& message)
{
    // TODO: Разобрать std::string, прочитать команду,
    // записать ее в список полученных комманд

    std::string BufferMessage = message;

    std::string Message = m_encoder->decode(BufferMessage);
    std::string TypeOfMessage = m_serial->GetTypeMessage(Message);

    if (TypeOfMessage == "Error")
    {
        std::cout << "This is Error: " << m_serial->GetTypeError(Message);
    }

    if (TypeOfMessage == "Command")
    {
        m_CommandFromServer.push_back(m_serial->GetCommand(Message));

        double u_buffermeterages = static_cast <double> (m_meterages.back());

        u_buffermeterages = u_buffermeterages + m_CommandFromServer.back();

        m_meterages.back() = static_cast <uint8_t> (u_buffermeterages);
    }

    respond = message;

    std::cout << "DeviceMock::onMessageReceived: " << "DecodeMessagefromServer = " << respond << std::endl;

    sendNextMeterage(); // Отправляем следующее измерение

}

void DeviceMock::onConnected()
{
    // TODO, если нужно
}

void DeviceMock::onDisconnected()
{
    // TODO, если нужно
}

void DeviceMock::setMeterages(std::vector<uint8_t> meterages)
{
    m_meterages = std::move(meterages);
}

void DeviceMock::startMeterageSending()
{
    sendNextMeterage();
}

void DeviceMock::sendNextMeterage()
{
    if (m_timeStamp >= m_meterages.size())
        return;
    const auto meterage = m_meterages.at(m_timeStamp);
    (void)meterage;
    auto timeStamp = m_timeStamp;
    ++m_timeStamp;
    // TODO: Сформировать std::string и передать в sendMessage

    std::string Message = m_serial->serialize_Message(meterage,timeStamp);

//    RO3 ro3;
//    BaseEncoderExecutor *p_U1 = reinterpret_cast <BaseEncoderExecutor*> (&ro3);
//    m_encoder->registration_algorithm(p_U1);

    //m_encoder->choice_algoithm("RO3");


    Message = m_encoder->encode(Message);
    std::cout << "sendNextMeterage: " << "Send Message = " << Message << std::endl;
    sendMessage(Message);


}

void DeviceMock::setEncodingAlgoritm(BaseEncoderExecutor* EncodeAlgoritm)
{
    m_encoder->registration_algorithm(EncodeAlgoritm);
}

