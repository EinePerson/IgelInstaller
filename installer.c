#define CURL_STATICLIB
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
//ABC
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "downloader.h"
#include "tinyfiledialogs.h"

#ifdef _DEBUG
#    pragma comment (lib,"D:/libs/curl-8.1.2/builds/libcurl-vc15-x64-debug-static-ipv6-sspi-schannel/lib/libcurl_a_debug.lib")
#else
#    pragma comment (lib,"D:/libs/curl-8.1.2/builds/libcurl-vc15-x64-release-static-ipv6-sspi-schannel/lib/libcurl_a.lib")
#endif

#define BUFFER_SIZE 1024

size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream);

//char* add(char* str1, char* str2);

char* replace_char(char* str, char find, char replace);

char* selectFile(char name[],char txt[],char* path);

int  WinMain(int argc , char * argv[])
{
    const char name[1024] = "SnakeInformatik";
    const char* launcherH = "http://localhost:81/src/output.jar";
    const char* depsH = "http://localhost:81/src/output.deps";
    const char* loaderH = "http://localhost:81/src/depsload.jar";

    char* dPath;
    _dupenv_s(&dPath,0,"APPDATA");

    if (dPath == 0) {
        printf("Could not find Appdata path");
        return 1;
    }

    
    char quesTxt[1024] = "Install in default directory: ";
    strcat(quesTxt,dPath);
    strcat(quesTxt, " ?");

    char sName[1024];
    strcpy(sName, name);
    strcat(sName, " Installer");
    dPath = selectFile(sName, quesTxt, dPath);
    while (!dPath)
    {
        dPath = selectFile(sName, quesTxt, dPath);
    }

    dPath = replace_char(dPath, (char)92, '/');
    char ndPath[1024];
    strcpy(ndPath, dPath);
    strcat(ndPath, "/");
    strcat(ndPath, name);
    strcat(ndPath, "/");

    if(mkdir(ndPath))printf("Could not create directory: %s \n",ndPath);
    char launcher[1024];
    strcpy(launcher, ndPath);
    strcat(launcher, "launcher.exe");
    downloadFile(launcherH, launcher);
    char deps[1024];
    strcpy(deps, ndPath);
    strcat(deps, "dependencies.txt");
    downloadFile(depsH, deps);
    char depsLoad[1024];
    strcpy(depsLoad, ndPath);
    strcat(depsLoad, "loader.jar");
    downloadFile(depsH, depsLoad);

    return 0;

}



size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

/*char* add(char* str1, char* str2) {
    printf("A    A");
    printf(str2);
    size_t i = strlen(str1);
    size_t j = strlen(str2);

    for (int k = 0; k < j; k++) {
        str1[i + k] = &str2[k];
        printf(str1);
    }
    printf(str1);
    printf("B   B");
    return str1;
}*/

char* replace_char(char* str, char find, char replace) {
    char* current_pos = strchr(str, find);
    while (current_pos) {
        *current_pos = replace;
        current_pos = strchr(current_pos, find);
    }
    return str;
}

char* selectFile(char name[], char txt[], char* path) {
    int lIntValue;
    char* dPath = "";
    lIntValue = tinyfd_messageBox(name, txt, "yesnocancel", "question", 1);

    if (lIntValue == 0)exit(0);
    else if (lIntValue == 1)return path;
    else if (lIntValue == 2) dPath = tinyfd_selectFolderDialog("Select Installation folder", dPath);
    if (!dPath) tinyfd_messageBox("Error", "Invalid Folder", "ok", "error", 1);
    return dPath;
}