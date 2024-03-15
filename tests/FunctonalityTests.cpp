#include <iostream>
#include <gtest/gtest.h>
#include "../src/System.h"
#include "../src/Device.h"
#include "../src/Job.h"


class FunctionalityTests: public ::testing::Test {
protected:
    // You should make the members protected s.t. they can be
    // accessed from sub-classes.

    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the variables.
    // Otherwise, this can be skipped.
    virtual void SetUp() {
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    virtual void TearDown() {
    }

    // Declares the variables your tests want to use.
    System sys;
};

// Testing attributes and function of System.h
TEST_F(FunctionalityTests, SystemTest) {

    System system1;

    string user1;
    Job *job1 = new Job(1,1,user1);

    string device_name1;
    Device *device1 = new Device(device_name1,1,1);

    // System should have no jobs and devices
    EXPECT_TRUE(system1.getJobs().empty());
    EXPECT_TRUE(system1.getDevices().empty());

    // System should be able to add jobs and devices
    system1.addJob(job1);
    system1.addDevice(device1);

    EXPECT_TRUE(system1.getJobs().size() == 1);
    EXPECT_TRUE(system1.getDevices().size() == 1);

    // System should be able to link jobs to the right device
    system1.link_jobs();

    EXPECT_TRUE(system1.getDevices()[0]->getCurrentJob() == job1);

    // System should be properly initialized
    EXPECT_TRUE(system1.properlyInitialized());
}