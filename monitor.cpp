#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <thread>
#include <chrono>

using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::this_thread::sleep_for;
using std::chrono::seconds;

struct VitalStatus {
    bool isOk;
    string message;
};

class IVitalAlert {
public:
    virtual void showAlert(const string& message) = 0;
    virtual ~IVitalAlert() = default;
};

class ConsoleAlert : public IVitalAlert {
public:
    void showAlert(const string& message) override {
        std::cout << message << "\n";
    }
};

class IAlertAnimation {
public:
    virtual void animate() = 0;
    virtual ~IAlertAnimation() = default;
};

class BlinkingAnimation : public IAlertAnimation {
public:
    void animate() override {
        for (int i = 0; i < 6; ++i) {
            std::cout << "\r* " << std::flush;
            sleep_for(seconds(1));
            std::cout << "\r *" << std::flush;
            sleep_for(seconds(1));
        }
        std::cout << "\n";
    }
};

class VitalChecker {
public:
    VitalStatus check(float temperature, float pulseRate, float spo2) {
        if (temperature > 102 || temperature < 95) {
            return {false, "Temperature is critical!"};
        }
        if (pulseRate < 60 || pulseRate > 100) {
            return {false, "Pulse Rate is out of range!"};
        }
        if (spo2 < 90) {
            return {false, "Oxygen Saturation out of range!"};
        }
        return {true, "Vitals are normal."};
    }
};

class VitalMonitor {
    IVitalAlert& alert;
    IAlertAnimation& animation;
    VitalChecker checker;

public:
    VitalMonitor(IVitalAlert& alertImpl, IAlertAnimation& animationImpl)
        : alert(alertImpl), animation(animationImpl) {}

    bool monitor(float temperature, float pulseRate, float spo2) {
        VitalStatus status = checker.check(temperature, pulseRate, spo2);
        if (!status.isOk) {
            alert.showAlert(status.message);
            animation.animate();
        }
        return status.isOk;
    }
};
