#include <iostream>

#include "RawHTTPClient.h"
#include "HttpRequest.h"
#include "HttpException.h"
#include <string>
#include <string.h>


static int statusCode;
static int payloadSize;
static char dataReceived[2048];
static char statusCodeMessage[10240];

RawHTTPClient::RawHTTPClient()
{
    //ctor
    //setOauthKey("");
}

RawHTTPClient::~RawHTTPClient()
{
    //dtor
}

void RawHTTPClient::setHostURL(const char* server)
{
    strcpy(hostserver,server);
}

void RawHTTPClient::setAPIEndPoint(const char* urlEndPoint)
{
    strcpy(apiEndpoint,urlEndPoint);
}

void RawHTTPClient::setURLParam(const char* urlparam)
{
    strcpy(urlParams,"?");
    strcat(urlParams,urlparam);
}

void RawHTTPClient::setBodyParam(const char* params)
{
    strcpy(bodyParams,params);
}

void RawHTTPClient::setOauthKey(const char* key)
{
    strcpy(outhKey,"Basic ");
    strcat(outhKey,key);
    isBasicAuthEnabled = true;
}


void RawHTTPClient::headersReady(const HttpResponse *response, void *additionalParams)
{
    //printf("HTTP Status: %d - %s\n", response->getStatus(), response->getReason());
    statusCode = response->getStatus();
    sprintf(statusCodeMessage,(const char *)response->getReason());
    printf(".................... Data Start ....................\n");
    payloadSize = 0;
}

void RawHTTPClient::receiveData(const HttpResponse *response, void *additionalParams, const unsigned char *data, int sizeOfData)
{
    //fwrite(data, 1, sizeOfData, stdout);
    sprintf(dataReceived,(const char *)data);
    //printf("receiveDa=%d and data=%s",sizeOfData,dataReceived);
    payloadSize += sizeOfData;
}

void RawHTTPClient::responseComplete(const HttpResponse *response, void *additionalParams)
{
    printf("\n.................... Data End ......................\n");
    printf("Data Size: %d bytes\n\n", payloadSize);
}

int RawHTTPClient::get(char *resp,char *errorMsg)
{

    printf("\n-------------------------- GET Request --------------------------\n");


    const char *headers[] =
    {
        "Connection", "close",
        "Content-type", "application/json",
        //"Accept", "json",
        "Authorization",outhKey,
        0  //null terminator
    };

    const char *headerdefault[] =
    {
        "Connection", "close",
        "Content-type", "application/json",
        "Accept", "json",
        0  //null terminator
    };

    char ReqParam[512];
    strcpy(ReqParam,apiEndpoint);
    strcat(ReqParam,urlParams);
    //printf("ReqParam=%s",ReqParam);

    HttpRequest request(hostserver, serverPort); // aitlhttp.herokuapp.com
    request.initCallbacks(headersReady, receiveData, responseComplete, 0);
    if(isBasicAuthEnabled)
    {
        request.sendRequest("GET", ReqParam, headers, 0, 0); // ReqParam "/NECLDBService/common/saveRfqDataForFR"
    }
    else
    {
        request.sendRequest("GET", ReqParam,headerdefault, 0, 0); // ReqParam "/NECLDBService/common/saveRfqDataForFR"
    }



    while(request.responsesPending())
    {
        request.processRequest();
    }

    memcpy(resp,dataReceived,strlen(dataReceived));
    memcpy(errorMsg,statusCodeMessage,strlen(statusCodeMessage));

    return statusCode;

}

int RawHTTPClient::post(char *resp,char *errorMsg)
{
    printf("\n------------------------- POST Request -------------------------\n");


    const char *headers[] =
    {
        "Connection", "close",
        "Content-type", "application/json",
        //"Accept", "json",
        "Authorization",outhKey,
        0  //null terminator
    };
    const char *headerdefault[] =
    {
        "Connection", "close",
        "Content-type", "application/json",
        "Accept", "json",
        0  //null terminator
    };


    char ReqParam[512];
    strcpy(ReqParam,apiEndpoint);
    //strcat(ReqParam,urlParams);

    HttpRequest request(hostserver, serverPort); //aitlhttp.herokuapp.com//sibpl.xtpl.co.in
    request.initCallbacks(headersReady, receiveData, responseComplete, 0);
    if(isBasicAuthEnabled)
    {
        request.sendRequest("POST", ReqParam, headers, (const unsigned char*)bodyParams, strlen(bodyParams));
    }
    else
    {
        request.sendRequest("POST", ReqParam, headerdefault, (const unsigned char*)bodyParams, strlen(bodyParams));
    }


    while(request.responsesPending())
    {
        request.processRequest();
    }

    memcpy(resp,dataReceived,strlen(dataReceived));
    memcpy(errorMsg,statusCodeMessage,strlen(statusCodeMessage));

    return statusCode;
}

