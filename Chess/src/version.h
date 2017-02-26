#ifndef VERSION_H
#define VERSION_H


#include <string>

#define V_MAJOR "0"
#define V_MINOR "1"
#define V_PATCH "0"

inline std::string getVersionString() {
    std::string version = "";
    version.append(V_MAJOR);
    version.append(".");
    version.append(V_MINOR);
    version.append(".");
    version.append(V_PATCH);
    return version;
}

#endif
