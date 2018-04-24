#ifndef VARAHTTP_H
#define VARAHTTP_H

#include "HttpRequest.h"
#include "HttpException.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

class RawHTTPClient
{
public:
    //int payloadSize;
    //int statusCode = 0;

    char hostserver[2048];
    char apiEndpoint[10480];
    char urlParams[10480];
    char bodyParams[10480];
    int serverPort = 80;
    bool isBasicAuthEnabled = false;
    char outhKey[10240];


    RawHTTPClient();
    virtual ~RawHTTPClient();

    void static headersReady(const HttpResponse *response, void *additionalParams);
    void static receiveData(const HttpResponse *response, void *additionalParams, const unsigned char *data, int sizeOfData);
    void static responseComplete(const HttpResponse *response, void *additionalParams);

    int get(char *resp,char *errorMsg);
    int post(char *resp,char *errorMsg);

    void setHostURL(const char* server);
    void setAPIEndPoint(const char* urlEndPoint);
    void setURLParam(const char* urlparam);
    void setBodyParam(const char* params);
    void setOauthKey(const char* params);


protected:


private:
};

#endif // VARAHTTP_H
