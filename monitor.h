#ifndef VITAL_MONITOR_H
#define VITAL_MONITOR_H

#include <string>

struct VitalStatus {
    bool isOk;
    std::string message;
};

class IVitalAlert {
public:
    virtual void showAlert(const std::string& message) = 0;
    virtual ~IVitalAlert() = default;
};

class IAlertAnimation {
public:
    virtual void animate() = 0;
    virtual ~IAlertAnimation() = default;
};

class VitalChecker {
public:
    VitalStatus check(float temperature, float pulseRate, float spo2);
};

class VitalMonitor {
    IVitalAlert& alert;
    IAlertAnimation& animation;
    VitalChecker checker;

public:
    VitalMonitor(IVitalAlert& alertImpl, IAlertAnimation& animationImpl);
    bool monitor(float temperature, float pulseRate, float spo2);
};

#endif // VITAL_MONITOR_H
