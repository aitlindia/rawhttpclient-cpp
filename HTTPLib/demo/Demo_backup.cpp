// Copyright (c) 2013 Matt Hill
// Use of this source code is governed by The MIT License
// that can be found in the LICENSE file.

#include "HttpRequest.h"
#include "HttpException.h"

#include <stdio.h>
#include <string.h>


//*********************************************
// Callbacks for processing the HTTP Response
//*********************************************

int payloadSize = 0;

void headersReady(const HttpResponse *response, void *additionalParams)
{
  printf("HTTP Status: %d - %s\n", response->getStatus(), response->getReason());
  printf(".................... Data Start ....................\n");
  payloadSize = 0;
}

void receiveData(const HttpResponse *response, void *additionalParams, const unsigned char *data, int sizeOfData)
{
  fwrite(data, 1, sizeOfData, stdout);
  payloadSize += sizeOfData;
}

void responseComplete(const HttpResponse *response, void *additionalParams)
{
  printf("\n.................... Data End ......................\n");
  printf("Data Size: %d bytes\n\n", payloadSize);
}



//*********************************************
// Demo Requests
//*********************************************

void demoGet()
{
  printf("\n-------------------------- GET Request --------------------------\n");
  HttpRequest request("aitlhttp.herokuapp.com", 80); // aitlhttp.herokuapp.com
  request.initCallbacks(headersReady, receiveData, responseComplete, 0);
  request.sendRequest("GET", "/httprequest/", 0, 0, 0);


  while(request.responsesPending())
  {
    request.processRequest();
  }
}

/*
void demoGetSIBPL()
{
  string Request = "/NECLDBService/common/saveRfqDataForFR?";
  string Data = "macAddress=00:23:68:DB:0F:54&event=4&rfidTag=1234567890C622266125&rfidReaderId=4&timeStamp=2018-01-24 18:59:38&containerNo=CAXU6442769&rfidSeqNo=20&WagonNo=RABCG";
  string ReqData =Request+Data;

  const char * ReqParam = ReqData.c_str();

  str.c_str()
  printf("\n-------------------------- GET SIBPL Request --------------------------\n");
  //http://sibpl.xtpl.co.in/NECLDBService/common/saveRfqDataForFR
  HttpRequest request("sibpl.xtpl.co.in", 80); // aitlhttp.herokuapp.com
  request.sendRequest("GET", ReqParam, 0, 0, 0); // ReqParam "/NECLDBService/common/saveRfqDataForFR"


  while(request.responsesPending())
  {
    request.processRequest();
  }
}
*/

void demoPost()
{
  printf("\n-------------------------- POST Request -------------------------\n");
  const char *headers[] =
  {
    "Connection", "close",
    "Content-type", "application/json",
    "Accept", "json",
    "Authorization","Basic TkVDOk5FQ0AxMjM=",
    0  //null terminator
  };


  const char *body = "{\"MacRegObject\": {\"rfidReaderId\": \"4\",\"rfidTag\": \"1234567890C622255125\",\"macAddress\": \"00:23:68:DB:0F:54\",\"event\": \"4\",\"timeStamp\": \"2018-01-24 18:59:38\",\"containerNo\": \"CAXU6442769\",\"rfidSeqNo\": \"20\"}}";

  HttpRequest request("aitlhttp.herokuapp.com", 80); //aitlhttp.herokuapp.com
  request.initCallbacks(headersReady, receiveData, responseComplete, 0);
  request.sendRequest("POST", "/httprequest/", headers, (const unsigned char*)body, strlen(body));

  while(request.responsesPending())
  {
    request.processRequest();
  }
}

void demoPostAITL()
{
  printf("\n-------------------------- POST Request -------------------------\n");
  const char *headers[] =
  {
    "Connection", "close",
    "Content-type", "application/json",
    "Accept", "json",
    0  //null terminator
  };


  const char *body = "{\"MacRegObject\": {\"rfidReaderId\": \"4\",\"rfidTag\": \"1234567890C622255125\",\"macAddress\": \"00:23:68:DB:0F:54\",\"event\": \"4\",\"timeStamp\": \"2018-01-24 18:59:38\",\"containerNo\": \"CAXU6442769\",\"rfidSeqNo\": \"20\"}}";

  HttpRequest request("aitlhttp.herokuapp.com", 80); //aitlhttp.herokuapp.com
  request.initCallbacks(headersReady, receiveData, responseComplete, 0);
  request.sendRequest("POST", "/httprequest/", headers, (const unsigned char*)body, strlen(body));

  while(request.responsesPending())
  {
    request.processRequest();
  }
}


//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  try
  {
    demoGet();
    demoGetSIBPL();
    //demoPost();
    //demoPostAITL();
  }
  catch(HttpException &e)
  {
    printf("Exception:\n%s\n", e.message());
  }

  return 0;
}
