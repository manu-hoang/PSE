#include <gtest/gtest.h>
#include <fstream>
#include "../src/System.h"
#include "TestUtils.h"
#include "../src/SystemImporter.h"
#include "../src/SystemExporter.h"
#include "climits"


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
TEST_F(FunctionalityTests, SystemConstructor) {
    ASSERT_TRUE(DirectoryExists("tests/functionalityTests"));
    //if directory doesn't exist then no need in proceeding with the test

    System system;

    // System should be properly initialized
    EXPECT_TRUE(system.properlyInitialized());

    // System should have no jobs, devices and compensations
    EXPECT_TRUE(system.getJobs().empty());
    EXPECT_TRUE(system.getDevices().empty());
    EXPECT_TRUE(system.getCompensations().empty());

    // System contract violations
    Job* mock_job = nullptr;
    EXPECT_DEATH(system.addJob(mock_job), "Cannot add nullptr as job to system");

    Device* mock_dev = nullptr;
    EXPECT_DEATH(system.addDevice(mock_dev), "Cannot add nullptr as device to system");

    Compensation* mock_comp = nullptr;
    EXPECT_DEATH(system.addCompensation(mock_comp), "Cannot add nullptr as compensation to system");
}

// Testing basic attributes and function of System.h
TEST_F(FunctionalityTests, DeviceConstructor) {
    ASSERT_TRUE(DirectoryExists("tests/functionalityTests"));
    //if directory doesn't exist then no need in proceeding with the test

    // Device(string name, int emissions, double speed, int cost);
    BlackWhitePrinter bw("name", 0, 0, 0);
    ColorPrinter color("name", 0, 0, 0);
    Scanner scan("name", 0, 0, 0);

    // Devices should be properly initialized
    EXPECT_TRUE(bw.properlyInitialized());
    EXPECT_TRUE(color.properlyInitialized());
    EXPECT_TRUE(scan.properlyInitialized());

    // Check for correct type enum
    EXPECT_EQ(bw.get_type(), bw_device);
    EXPECT_EQ(color.get_type(), color_device);
    EXPECT_EQ(scan.get_type(), scan_device);

    // Check jobs queue
    EXPECT_EQ(bw.getCurrentJob(), nullptr);
    EXPECT_TRUE(bw.get_queue().empty());
    EXPECT_EQ(bw.get_total_pages(), 0);

    Job* mock_job = nullptr;
    EXPECT_DEATH(bw.add_job(mock_job), "Cannot add nullptr as job to device");

    // Check current CO2 value of device
    EXPECT_EQ(bw.get_CO2(), 0);

    // Check emission limits                          //  Device type         CO2 limit
    EXPECT_TRUE(bw.exceeds_CO2_limit(9));       //  Black-and-white     8g CO2 per page
    EXPECT_TRUE(color.exceeds_CO2_limit(24));   //  Color               23g CO2 per page
    EXPECT_TRUE(scan.exceeds_CO2_limit(13));    //  Scanner             12g CO2 per page


}

// Testing basic attributes and function of System.h
TEST_F(FunctionalityTests, JobConstructor) {
    ASSERT_TRUE(DirectoryExists("tests/functionalityTests"));
    //if directory doesn't exist then no need in proceeding with the test

    // Job(int jobNumber, double pageCount, string userName);
    BlackWhiteJob bw(0,0,"name", 0);
    ColorJob color(0,0,"name", 0);
    ScanJob scan(0,0,"name", 0);

    // System should be properly initialized
    EXPECT_TRUE(bw.properlyInitialized());
    EXPECT_TRUE(color.properlyInitialized());
    EXPECT_TRUE(scan.properlyInitialized());

    // Check for correct type enum
    EXPECT_EQ(bw.get_type(), bw_job);
    EXPECT_EQ(color.get_type(), color_job);
    EXPECT_EQ(scan.get_type(), scan_job);

    BlackWhiteJob mock_job(12345,10,"name", 0);

    // Check page counts
    EXPECT_EQ(mock_job.getCurrentPageCount(), mock_job.getTotalPageCount());
    mock_job.printFullPage();
    EXPECT_EQ(mock_job.getCurrentPageCount(), mock_job.getTotalPageCount() - 1);

    EXPECT_FALSE(mock_job.getCompensated());
}

// Use Case 3.3: Manual processing met type (new)
TEST_F(FunctionalityTests, ManualProcessing) {
    ASSERT_TRUE(DirectoryExists("tests/functionalityTests"));
    //if directory doesn't exist then no need in proceeding with the test

    BlackWhitePrinter mock_device("name", 0, 1, 0);
    BlackWhiteJob mock_job(0,1,"name", 0);

    mock_device.add_job(&mock_job);

    ofstream myfile;
    myfile.open("tests/functionalityTests/manualProcessingOutput.txt");
    sys.manual_processing(myfile, &mock_device);
    myfile.close();

    EXPECT_TRUE(mock_job.getFinished());
    EXPECT_TRUE(FileCompare("tests/functionalityTests/manualProcessingOutput.txt",
                            "tests/functionalityTests/manualProcessingExpected.txt"));
}

// Use Case 3.4: Automated processing with type (new)
TEST_F(FunctionalityTests, AutomatedProcessing) {
    ASSERT_TRUE(DirectoryExists("tests/functionalityTests"));
    //if directory doesn't exist then no need in proceeding with the test

    ColorPrinter mock_color_device("Library Printer 5", 0, 1, 0);
    BlackWhitePrinter mock_bw_device("Library Printer 5", 0, 1, 0);
    Scanner mock_scanner("Brand new scanner", 0, 1, 0);

    ColorJob mock_color_job(13989,3,"John Doe", 0);
    BlackWhiteJob mock_bw_job(132,60,"New User", 0);
    ScanJob mock_scan_job(368,5,"Serge Demeyer", 0);

    sys.addDevice(&mock_color_device);
    sys.addDevice(&mock_bw_device);
    sys.addDevice(&mock_scanner);

    sys.addJob(&mock_color_job);
    sys.addJob(&mock_bw_job);
    sys.addJob(&mock_scan_job);

    ofstream myfile;
    myfile.open("tests/functionalityTests/automaticProcessingOutput.txt");
    sys.automated_processing(myfile);
    myfile.close();

    EXPECT_TRUE(FileCompare("tests/functionalityTests/automaticProcessingOutput.txt",
                            "tests/functionalityTests/automaticProcessingExpected.txt"));
}

// Use Case 3.5: Multiple devices with the same type
TEST_F(FunctionalityTests, MultipleDevices) {
    ASSERT_TRUE(DirectoryExists("tests/functionalityTests"));
    //if directory doesn't exist then no need in proceeding with the test

    // Set up 2 devices (one will contain a large job, the other will contain multiple snaller jobs)
    BlackWhitePrinter mock_bw_device1("Device 1", 0, 1, 0);
    sys.addDevice(&mock_bw_device1);

    BlackWhitePrinter mock_bw_device2("Device 2", 0, 1, 0);
    sys.addDevice(&mock_bw_device2);

    // Fill device 1 with large job
    BlackWhiteJob mock_bw_job(132,INT_MAX,"Big Job", 0);
    mock_bw_device1.add_job(&mock_bw_job);

    BlackWhiteJob small_job1(1,1,"Small Job", 0);
    BlackWhiteJob small_job2(2,1,"Small Job", 0);
    BlackWhiteJob small_job3(3,1,"Small Job", 0);
    BlackWhiteJob small_job4(4,1,"Small Job", 0);

    sys.addJob(&small_job1); sys.addJob(&small_job2);
    sys.addJob(&small_job3); sys.addJob(&small_job4);

    ofstream myfile;
    myfile.open("tests/functionalityTests/MultipleDevicesOutput.txt");
    sys.automated_processing(myfile);
    myfile.close();

    EXPECT_TRUE(FileCompare("tests/functionalityTests/MultipleDevicesOutput.txt",
                            "tests/functionalityTests/MultipleDevicesExpected.txt"));
}

// Use Case 3.6: CO2-friendly job scheduling
TEST_F(FunctionalityTests, CO2JobScheduling) {
    ASSERT_TRUE(DirectoryExists("tests/functionalityTests"));
    //if directory doesn't exist then no need in proceeding with the test

    // Set up 2 devices (one will contain a large job, the other will contain multiple snaller jobs)
    BlackWhitePrinter mock_device1("Device 1", 0, 1, 0);
    sys.addDevice(&mock_device1);

    BlackWhitePrinter mock_device2("Device 2", 0, 1, 0);
    sys.addDevice(&mock_device2);

    // Exceed device 1 CO2 limit
    mock_device1.set_CO2(100);

    BlackWhiteJob small_job1(1,1,"Small Job", 0);
    BlackWhiteJob small_job2(2,1,"Small Job", 0);
    BlackWhiteJob small_job3(3,1,"Small Job", 0);
    BlackWhiteJob small_job4(4,1,"Small Job", 0);

    sys.addJob(&small_job1); sys.addJob(&small_job2);
    sys.addJob(&small_job3); sys.addJob(&small_job4);

    ofstream myfile;
    myfile.open("tests/functionalityTests/CO2JobSchedulingOutput.txt");
    sys.automated_processing(myfile);
    myfile.close();

    EXPECT_TRUE(FileCompare("tests/functionalityTests/CO2JobSchedulingOutput.txt",
                            "tests/functionalityTests/CO2JobSchedulingExpected.txt"));
}

// Use Case 3.7: Tracking CO2 emissions
TEST_F(FunctionalityTests, TrackingCO2Emissions) {
    ASSERT_TRUE(DirectoryExists("tests/functionalityTests"));
    //if directory doesn't exist then no need in proceeding with the test

    BlackWhitePrinter mock_device("Device", 1, 1, 0); // 1 gram of CO2 per page
    sys.addDevice(&mock_device);

    BlackWhiteJob small_job1(1,1,"Small Job", 0);
    BlackWhiteJob small_job2(2,1,"Small Job", 0);
    BlackWhiteJob small_job3(3,1,"Small Job", 0);
    BlackWhiteJob small_job4(4,1,"Small Job", 0);

    sys.addJob(&small_job1); sys.addJob(&small_job2);
    sys.addJob(&small_job3); sys.addJob(&small_job4);

    ofstream myfile;
    myfile.open("tests/functionalityTests/TrackingCO2EmissionsOutput.txt");
    sys.automated_processing(myfile);
    myfile.close();

    EXPECT_EQ(sys.getTotalEmissions(), 4); // 4 grams of CO2 for 4 pages
}

// Use Case 3.8: CO2 compensation
TEST_F(FunctionalityTests, CO2Compensation) {
    ASSERT_TRUE(DirectoryExists("tests/functionalityTests"));
    //if directory doesn't exist then no need in proceeding with the test

    BlackWhiteJob mock_job(1,1,"Job", 1111);

    Compensation mock_comp(1111 ,"Compensation");

    sys.addCompensation(&mock_comp);

    EXPECT_TRUE(sys.find_compensation(&mock_job));
}

// Use Case 3.9: Statistical calculations
TEST_F(FunctionalityTests, StatisticalCalculations) {
    ASSERT_TRUE(DirectoryExists("tests/functionalityTests"));
    //if directory doesn't exist then no need in proceeding with the test

    SystemExporter exporter;

    // input parser
    ofstream myfile;
    myfile.open("in_output/InputError.txt");
    SystemImporter::importSystem("xml_files/CompleteInput.xml", myfile, sys);
    myfile.close();

    int seconds = 2; // total run time of the program
    sys.divideJobs(); // divide all jobs to respective devices queue before loop (prevents multiple unnecessary divisions)

    exporter.documentStart(myfile);
    for (int i = 0; i <= seconds; ++i) {
        sys.tick();
        exporter.advanced_textual_output(myfile, sys);
    }
    exporter.documentEnd(myfile);

    // simple output
    myfile.open("tests/functionalityTests/StatisticalCalculationsOutput.txt");
    exporter.documentStart(myfile);
    exporter.statistics_output(myfile, sys);
    exporter.documentEnd(myfile);
    myfile.close();

    EXPECT_TRUE(FileCompare("tests/functionalityTests/StatisticalCalculationsOutput.txt",
                            "tests/functionalityTests/StatisticalCalculationsExpected.txt"));
}