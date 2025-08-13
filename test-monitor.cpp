#include "vital_monitor.h"
#include <cassert>
#include <vector>
#include <string>
#include <iostream>

class MockAlert : public IVitalAlert {
public:
    std::string lastMessage;
    void showAlert(const std::string& message) override {
        lastMessage = message;
    }
};

class MockAnimation : public IAlertAnimation {
public:
    bool animated = false;
    void animate() override {
        animated = true;
    }
};

void testVitalsNormal() {
    MockAlert alert;
    MockAnimation animation;
    VitalMonitor monitor(alert, animation);

    bool result = monitor.monitor(98.6, 72, 95);
    assert(result == true);
    assert(alert.lastMessage.empty());
    assert(animation.animated == false);
}

void testTemperatureCritical() {
    MockAlert alert;
    MockAnimation animation;
    VitalMonitor monitor(alert, animation);

    bool result = monitor.monitor(103.0, 72, 95);
    assert(result == false);
    assert(alert.lastMessage == "Temperature is critical!");
    assert(animation.animated == true);
}

void testPulseRateOutOfRange() {
    MockAlert alert;
    MockAnimation animation;
    VitalMonitor monitor(alert, animation);

    bool result = monitor.monitor(98.6, 50, 95);
    assert(result == false);
    assert(alert.lastMessage == "Pulse Rate is out of range!");
    assert(animation.animated == true);
}

void testSpo2Low() {
    MockAlert alert;
    MockAnimation animation;
    VitalMonitor monitor(alert, animation);

    bool result = monitor.monitor(98.6, 72, 85);
    assert(result == false);
    assert(alert.lastMessage == "Oxygen Saturation out of range!");
    assert(animation.animated == true);
}

int main() {
    testVitalsNormal();
    testTemperatureCritical();
    testPulseRateOutOfRange();
    testSpo2Low();
    std::cout << "All tests passed!\n";
    return 0;
}
