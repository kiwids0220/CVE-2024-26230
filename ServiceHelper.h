#pragma once
#include <Windows.h>

class ServiceHelper {
private:
    SC_HANDLE scmHandle;
    SC_HANDLE serviceHandle;
    LPCWSTR serviceName;
    int32_t dwDesiredAccess;
    // Function to close service handles
    void Close();

public:
    //rule of the three

    ServiceHelper(std::wstring name, int32_t dwDesiredAccess);
    ~ServiceHelper();
    ServiceHelper(const ServiceHelper& other);
    ServiceHelper& operator=(const ServiceHelper& other);

    // Function to start the service
    bool StartTheDamnService();

    // Function to stop the service
    bool StopTheDamnService();
};
