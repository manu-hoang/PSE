#include <iostream>
#include <gtest/gtest.h>
#include "../src/System.h"
#include "../src/Device.h"
#include "../src/Job.h"
#include "../src/PrinterInput.h"
#include "../src/PrinterOutput.h"


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

// Testing basic attributes and function of System.h
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

// Testing basic attributes and function of Device.h
TEST_F(FunctionalityTests, DeviceTests) {

    string device_name1;
    Device *device1 = new Device(device_name1,1,1);

    // All the getter should work
    EXPECT_TRUE(device1->getBusy() == false);
    EXPECT_TRUE(device1->getName() == device_name1);
    EXPECT_TRUE(device1->getEmissions() == 1);

    // Device should not have any jobs
    EXPECT_TRUE(device1->getJobs().empty());

    string user1;
    Job *job1 = new Job(1,1,user1);

    string user2;
    Job *job2 = new Job(2,2,user2);

    // Jobs gets added (setter)
    device1->add_job(job1);
    device1->add_job(job2);

    EXPECT_TRUE(device1->getJobs().size() == 2);
}

// Testing basic attributes and function of Job.h
TEST_F(FunctionalityTests, JobTests) {
    string user1;
    Job *job1 = new Job(1,1,user1);

    // All the getters and setters should work
    EXPECT_TRUE(job1->getJobNumber() == 1);
    EXPECT_TRUE(job1->getCurrentPageCount() == 1);
    EXPECT_TRUE(job1->getUserName() == user1);

    job1->setStartTime(200);
    EXPECT_TRUE(job1->getStartTime() == 200);
}

// Testing the Use Case 3.1: Manual Processing and Use Case 3.2: Automated Processing
// In- and Output get tested in PrinterIn_OutputTests.cpp
TEST_F(FunctionalityTests, UseCase3_1_2Processing) {

    System system;

    ofstream myfile;
    myfile.open("in_output/InputError.txt");
    SystemImporter::importSystem("./xml_files/Use_Case_1.1_Reading_printers_and_jobs.xml", myfile, system);
    myfile.close();

    // First job should be the current job
    EXPECT_TRUE(system.getDevices()[0]->getCurrentJob() == system.getJobs()[0]);

    // System did not run for long enough to pass the first job, so current job should stay the same
    system.automatic_run(2);
    EXPECT_TRUE(system.getDevices()[0]->getCurrentJob() == system.getJobs()[0]);

    // System had enough time to go to the next job but doesnt complete the next one
    system.automatic_run(3);
    EXPECT_TRUE(system.getDevices()[0]->getCurrentJob() == system.getJobs()[1]);

    // System finishes the job and there should be no current jobs left
    system.automatic_run(100);
    EXPECT_FALSE(system.getDevices()[0]->getCurrentJob());

}