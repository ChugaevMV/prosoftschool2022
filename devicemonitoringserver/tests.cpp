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

    const uint64_t deviceId = 111;
    const uint64_t serverId = 11;

    std::vector<uint8_t> meterages {1};
    std::vector<Phase> phases {{0,1}};
    DeviceWorkSchedule schedule {deviceId,phases};




    ASSERT(device.bind(deviceId));
    ASSERT(server.listen(serverId));
    ASSERT(device.connectToServer(serverId));
    // device.setMeterages(  );
    // device.startMeterageSending();
    while (taskQueue.processTask())
        ;

    // ASSERT_EQUAL(device.responces(), expected);
}
