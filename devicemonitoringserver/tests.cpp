#include "tests.h"
#include "devicemock.h"
#include "devicemonitoringserver.h"
#include "test_runner.h"
#include <servermock/clientconnectionmock.h>
#include <servermock/connectionservermock.h>
#include <servermock/taskqueue.h>

#include "deviceworkschedule.h"

void monitoringServerTest1()
{
    // TODO: дописать тест
    TaskQueue taskQueue;
    DeviceMock device(new ClientConnectionMock(taskQueue));
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

    const uint64_t deviceId = 1;
    const uint64_t serverId = 13;

    ASSERT(device.bind(deviceId));
    ASSERT(server.listen(serverId));
    ASSERT(device.connectToServer(serverId));

    std::vector<uint8_t> meterages {32,5,150};
    std::vector<Phase> phases {{0,1},{1,5},{2,250}};
    DeviceWorkSchedule schedule {deviceId,phases};

    server.setDeviceWorkSchedule(schedule);

    device.setMeterages(meterages);

    RO3 ro3;
    BaseEncoderExecutor* p_ro3 = reinterpret_cast <BaseEncoderExecutor*> (&ro3);

    device.setEncodingAlgoritm(p_ro3);
    server.setEncodingAlgoritm(p_ro3);

    while (taskQueue.processTask())
        ;

    device.startMeterageSending();

    for (int i = 0; i < meterages.size()*2 + 2; i++)
            taskQueue.processTask();



    //ASSERT_EQUAL ()



    // ASSERT_EQUAL(device.responces(), expected);
}

