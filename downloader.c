#define CURL_STATICLIB
#define _CRT_SECURE_NO_WARNINGS
//ABC
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "downloader.h"

#ifdef _DEBUG
#    pragma comment (lib,"D:/libs/curl-8.1.2/builds/libcurl-vc15-x64-debug-static-ipv6-sspi-schannel/lib/libcurl_a_debug.lib")
#else
#    pragma comment (lib,"D:/libs/curl-8.1.2/builds/libcurl-vc15-x64-release-static-ipv6-sspi-schannel/lib/libcurl_a.lib")
#endif

#include <curl/curl.h>

/*Windows Specific Additional Depenedencies*/
#pragma comment (lib,"Normaliz.lib")
#pragma comment (lib,"Ws2_32.lib")
#pragma comment (lib,"Wldap32.lib")
#pragma comment (lib,"Crypt32.lib")
#pragma comment (lib,"advapi32.lib")

int downloadFile(char* host, char* file) {
    CURL* curl;
    FILE* fp;
    CURLcode res;

    curl = curl_easy_init();
    if (curl)
    {
        errno_t err;
        if ((err = fopen_s(&fp, file, "wb")) != 0) {
            printf("Could not open: %s due to %s \n", file, strerror(err));
        }
        else {

            curl_easy_setopt(curl, CURLOPT_URL, host);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            res = curl_easy_perform(curl);
            fclose(fp);
        }
        curl_easy_cleanup(curl);
    }
}