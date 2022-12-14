#define __CL_ENABLE_EXCEPTIONS
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120

#include <iostream>
#include <boost/format.hpp>
#include <boost/log/trivial.hpp>
#include <cl/opencl.hpp>

using namespace cl;

void displayPlatformInfo(const Platform& platform,
                         cl_platform_info param,
                         std::string paramName) {
    std::string result;
    platform.getInfo<string>(param, &result);
    //BOOST_LOG_TRIVIAL(info) << boost::format("%1%: %2%") % paramName % result;
    std::cout << boost::format("%1%: %2%") % paramName % result << std::endl;
}

void displayDeviceDetails(const Device& device,
                          cl_platform_info param,
                          std::string paramName);

void displayDeviceInfo(const Platform& platform) {
    vector<Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

    vector<Device>::iterator it;

    std::cout << boost::format("Number of detected OpenCL devices: %1%") % devices.size() << std::endl;

    for (it = devices.begin(); it != devices.end(); it++) {
        displayDeviceDetails( *it, CL_DEVICE_TYPE, "CL_DEVICE_TYPE" );
        displayDeviceDetails( *it, CL_DEVICE_NAME, "CL_DEVICE_NAME" );
        displayDeviceDetails( *it, CL_DEVICE_VENDOR, "CL_DEVICE_VENDOR" );
        displayDeviceDetails( *it, CL_DEVICE_VENDOR_ID, "CL_DEVICE_VENDOR_ID" );
        displayDeviceDetails( *it, CL_DEVICE_MAX_MEM_ALLOC_SIZE, "CL_DEVICE_MAX_MEM_ALLOC_SIZE" );
        displayDeviceDetails( *it, CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE, "CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE" );
        displayDeviceDetails( *it, CL_DEVICE_GLOBAL_MEM_SIZE, "CL_DEVICE_GLOBAL_MEM_SIZE" );
        displayDeviceDetails( *it, CL_DEVICE_MAX_COMPUTE_UNITS, "CL_DEVICE_MAX_COMPUTE_UNITS" );
        displayDeviceDetails( *it, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, "CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS" );
        displayDeviceDetails( *it, CL_DEVICE_MAX_WORK_ITEM_SIZES, "CL_DEVICE_MAX_WORK_ITEM_SIZES" );
        displayDeviceDetails( *it, CL_DEVICE_MAX_WORK_GROUP_SIZE, "CL_DEVICE_MAX_WORK_GROUP_SIZE" );

    }
}

void displayDeviceDetails(const Device& device,
                          cl_platform_info param,
                          std::string paramName) {
    switch (param) {
        case CL_DEVICE_TYPE: {
            cl_device_type deviceType;
            device.getInfo(param, &deviceType);
            switch (deviceType) {
                case CL_DEVICE_TYPE_CPU:
                    std::cout << boost::format("CPU Detected") << std::endl;
                    break;
                case CL_DEVICE_TYPE_GPU:
                    std::cout << boost::format("GPU Detected") << std::endl;
                    break;
            }
        } break;
        case CL_DEVICE_VENDOR_ID :
        case CL_DEVICE_MAX_COMPUTE_UNITS :
        case CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS : {
            cl_uint result = 0;
            device.getInfo(param, &result);
            switch (param) {
                case CL_DEVICE_VENDOR_ID:
                    std::cout << '\t' << boost::format("VENDOR ID: %1$#x") % result << std::endl;
                    break;
                case CL_DEVICE_MAX_COMPUTE_UNITS:
                    std::cout << '\t' << boost::format("Maximum number of parallel compute units: %1%") % result << std::endl;
                    break;
                case CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS:
                    std::cout << '\t' << boost::format("Maximum dimensions for global/local work-item IDs: %1%") % result << std::endl;
                    break;
            }
        } break;
        case CL_DEVICE_NAME :
        case CL_DEVICE_VENDOR : {
            std::string result;
            device.getInfo(param, &result);
            switch (param) {
                case CL_DEVICE_NAME:
                    std::cout << '\t' << boost::format("Device name is %1%") % result << std::endl;
                    break;
                case CL_DEVICE_VENDOR:
                    std::cout << '\t' << boost::format("Device vendor is %1%") % result << std::endl;
                    break;
            }
        } break;

    }
}

int main() {

    try {
        vector<Platform> platforms;
        Platform::get(&platforms);

        vector<Platform>::iterator it;
        int i = 0;
        for (it = platforms.begin(); it != platforms.end(); it++, i++ ) {
            displayPlatformInfo( *it, CL_PLATFORM_PROFILE, "CL_PLATFORM_PROFILE" );
            displayPlatformInfo( *it, CL_PLATFORM_VERSION, "CL_PLATFORM_VERSION" );
            displayPlatformInfo( *it, CL_PLATFORM_NAME,    "CL_PLATFORM_NAME" );
            displayPlatformInfo( *it, CL_PLATFORM_VENDOR,  "CL_PLATFORM_VENDOR" );
            displayPlatformInfo( *it, CL_PLATFORM_EXTENSIONS, "CL_PLATFORM_EXTENSIONS" );
            displayDeviceInfo(*it);
        }
    }
    catch (Error& err) {
        BOOST_LOG_TRIVIAL(error) << boost::format("Error %1% - %2%") % err.err() % err.what();
        return EXIT_FAILURE;
    }


    int* i = new int[16];

    return EXIT_SUCCESS;
}
