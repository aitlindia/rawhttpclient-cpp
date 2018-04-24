#include <iostream>

#include "HttpRequest.h"
#include "HttpException.h"

#include <stdio.h>
#include <string.h>
#include <string>

#include <RawHTTPClient.h>
#include <base64.h>
#include <json.hpp>

using namespace std;

//*********************************************
// Callbacks for processing the HTTP Response
//*********************************************
// for convenience
using namespace nlohmann;


int main()
{
    cout << "RAW HTTP GET Post Example!" << endl;

    const char *serverSIBPL = "sibpl.xtpl.co.in";
    const char *urlEndPointSIBPL = "/NECLDBService/common/saveRfqDataForFRPOST";;

    //sibpl.xtpl.co.in  // 192.168.1.69 // 115.111.231.107
    //HttpRequest request("sibpl.xtpl.co.in", 80); //aitlhttp.herokuapp.com//sibpl.xtpl.co.in

    const char *server = "aitlhttp.herokuapp.com";
    const char *urlEndPoint = "/httprequest/";
    const char *body = "{\"MacRegObject\": {\"rfidReaderId\": \"4\",\"rfidTag\": \"1234567890C622255125\",\"macAddress\": \"00:23:68:DB:0F:54\",\"event\": \"4\",\"timeStamp\": \"2018-01-24 18:59:38\",\"containerNo\": \"CAXU6442769\",\"rfidSeqNo\": \"20\"}}";
    char *urlParam = "macAddress=00:23:68:DB:0F:54&event=4&rfidTag=1234567890C622266125&rfidReaderId=4&timeStamp=2018-01-24%2018:59:38&containerNo=CAXU6442769&rfidSeqNo=20&WagonNo=RABCG";

    const char *key ="TkVDOk5FQ0AxMjM=";
    char resp[2048];
    char respMSGErr[2048];



    RawHTTPClient vHTTP;

    try
    {
        vHTTP.setHostURL(server);
        vHTTP.setAPIEndPoint(urlEndPoint);
        //vHTTP.setURLParam(urlParam);
        //vHTTP.setBodyParam(body);
        //vHTTP.setOauthKey(key);

        //vHTTP.get(resp,respMSGErr);
        //vHTTP.post(resp,respMSGErr);


        // create an empty structure (null)
        json j;

        // add a number that is stored as double (note the implicit conversion of j to an object)
        j["pi"] = 3.141;

        // add a Boolean that is stored as bool
        j["happy"] = true;

        // add a string that is stored as std::string
        j["name"] = "Niels";

        // add another null object by passing nullptr
        j["nothing"] = nullptr;

        // add an object inside the object
        j["answer"]["everything"] = 42;

        std::string sj = j.dump();

        vHTTP.setURLParam((const char *)sj.c_str());
        vHTTP.setBodyParam((const char *)sj.c_str());
        vHTTP.get(resp,respMSGErr);
        vHTTP.post(resp,respMSGErr);

        cout<<"Resp: "<< resp << " Erro Msg:"<<respMSGErr<<endl;

        cout<<"String Json: "<<sj<<endl;


    }
    catch(HttpException &e)
    {
        printf("Exception:\n%s\n", e.message());
    }


    return 0;
}
