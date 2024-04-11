#include "Header.h"

ServiceHelper::ServiceHelper(std::wstring service, int32_t DesiredAccess) : scmHandle(nullptr), serviceHandle(nullptr), serviceName(service.c_str()), dwDesiredAccess(DesiredAccess){
    scmHandle = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT | SC_MANAGER_ENUMERATE_SERVICE );
    if (scmHandle != NULL) {
        serviceHandle = OpenServiceW(scmHandle, L"Tapisrv", dwDesiredAccess);
        if (serviceHandle) { std::wcout << "Service" << serviceName << "successfully.\n" << std::endl; }
        else {
            std::cerr << "Failed to open service. Error: " << GetLastError() << std::endl;
        }
    }


}

ServiceHelper::~ServiceHelper() {
    Close();
}

ServiceHelper::ServiceHelper(const ServiceHelper& other) {
    serviceName = other.serviceName;
    scmHandle = other.scmHandle;
    serviceHandle = other.serviceHandle;
    dwDesiredAccess = other.dwDesiredAccess;
}

bool ServiceHelper::StartTheDamnService() {
    if (serviceHandle != NULL) {

        return StartServiceW(serviceHandle, 0, NULL);
    }
}

bool ServiceHelper::StopTheDamnService() {
    SERVICE_STATUS serviceStatus;
    if (!ControlService(serviceHandle, SERVICE_CONTROL_STOP, &serviceStatus)) {
        std::cerr << "Failed to stop service. Error: " << GetLastError() << std::endl;
        return false;
    }

    return true;
}

void ServiceHelper::Close() {
    if (serviceHandle != NULL) {
        CloseServiceHandle(serviceHandle);
        serviceHandle = NULL;
    }
    if (scmHandle != NULL) {
        CloseServiceHandle(scmHandle);
        scmHandle = NULL;
    }
}