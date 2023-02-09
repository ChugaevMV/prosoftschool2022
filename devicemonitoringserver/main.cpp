#include "test_runner.h"
#include "tests.h"
#include <servermock/servertests.h>

#include <devicemock.h>

#include <iostream>
#include <string>
#include <sstream>

#include <MessageSerializer.h>
#include <ro3.h>
#include <mirror.h>
#include <multiply41.h>
#include <messageencoder.h>


#include <commandcenter.h>
#include <devicemonitoringserver.h>

using namespace std;
int main()
{
    TestRunner tr;
    RUN_TEST(tr, taskQueueTest);
    RUN_TEST(tr, safeObjectPointerTest);
    RUN_TEST(tr, connectionChannelTest);
    RUN_TEST(tr, clientServerTest);
    RUN_TEST(tr, monitoringServerTest1);

        //Проверка работы MessageSerializer
//    string Type1 = {"Meterage"}, Type2;
//    uint8_t Meterage1 = 82;
//    uint8_t Meterage2;
//    uint64_t Time1 = 5, Time2;
//    double Command = -31;
//    string Type_error = {"NoTimestamp"};

//    MessageSerialiser Message;


//    string Write1 = Message.serialize_Message(Meterage1,Time1);
//    string Write2 = Message.serialize_Message(Command);
//    string Write3 = Message.serialize_Message(Type_error);

    //cout << Write1 << endl;
    //cout << Write2 << endl;
//    cout << Write3 << endl;


//    cout << Message.GetTypeMessage(Write1) << endl;
//    cout << Message.GetMeterage(Write1) << endl;
//    cout << Message.GetTimeStamp(Write1) << endl;
//    cout << Message.GetTypeError(Write3) << endl;
//    cout << Message.GetCommand(Write2) << endl;




//   RO3 ro3;

//   RO3 *p_ro3 = &ro3;

//   BaseEncoderExecutor *p_U = reinterpret_cast <BaseEncoderExecutor*> (p_ro3);

//   MessageEncoder Encode;

//   Encode.registration_algorithm(p_U);

//   string M = Encode.encode(Write1);

//   string N = Encode.decode(M);

//   cout << "M= " << M << "     " << "N= " << N << endl;


   //Multiply41 multiply;

   //Multiply41 *p_multiply = &multiply;

   //BaseEncoderExecutor *p_U1 = reinterpret_cast <BaseEncoderExecutor*> (p_multiply);

   //MessageEncoder Encode;

   //Multiply41 multiply;

   //RO3 ro3;

   //Mirror mirror;

   //BaseEncoderExecutor *p_U1 = reinterpret_cast <BaseEncoderExecutor*> (&multiply);

   //string P1 = "Multiply41";

   //Encode.choice_algoithm(P1);

   //Encode.registration_algorithm(p_U1);

   //string M1 = Encode.encode(Write1);

   //cout << "M = " << M1 << endl;

   //string N1 = Encode.decode(M1);

   //cout << "N = " << N1 << endl;

   //cout << "M = " << M1 << " " << "N = " << N1 << endl;


    // TODO: собственные тесты



//    CommandCenter commandcenter;

//    //DeviceMonitoringServer devicemonitoringserver;

//    string MessageToCommandCenter = "TestMessage";

//    string MessageFromCommandCenter = "";

    //1 вариант: devicemonitoringserver.SendMessageToCommandCenter(commandcenter, MessageToCommandCenter, MessageFromCommandCenter);

    //commandcenter.GetCommandMessage(MessageToCommandCenter, MessageFromCommandCenter);


//    map <int, int> mp;

//    mp[1] = 4;
//    mp[2] = 3;

//    map <int, int>::iterator it = mp.begin();

//    it++;

/*    for (int i=0; it != mp.end(); it++, i++){
        if(it -> first == 1) cout << "already use" << endl;
        else
            cout << it->first << " " << it ->second << endl;

    }
*/

    //it->second = 5;

//    int g = it->second;

//    cout << g << endl;

//    g = 10;

//    it->second = g;

//    cout << it->second << endl;



//    cout << it->first << " " << it ->second << endl;

//    it = mp.find(3);

//        cout << it->first << " " << it ->second << endl;


//    uint8_t met = 5;
//    double com = -3;


//    double u_meterages = static_cast <double> (met);
//    u_meterages = u_meterages + com;

//    cout << u_meterages << endl;

    return 0;
}
