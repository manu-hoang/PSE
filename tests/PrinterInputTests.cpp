#include <gtest/gtest.h>
#include <fstream>
#include "TestUtils.h"

#include "../src/System.h"
#include "../src/SystemImporter.h"
#include "../src/SystemExporter.h"


class PrinterInputTest: public ::testing::Test {
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

// Tests the input of the "happy day" scenario
TEST_F(PrinterInputTest, InputHappyDay) {
    ASSERT_TRUE(DirectoryExists("tests/inputTests"));
    //if directory doesn't exist then no need in proceeding with the test

    ofstream myfile;
    SuccessEnum importResult;

    myfile.open("tests/inputTests/HappyDayOutput.txt");
    importResult = SystemImporter::importSystem("tests/inputTests/HappyDay.xml", myfile, sys);
    myfile.close();

    EXPECT_TRUE(importResult == Success);

    EXPECT_TRUE(sys.properlyInitialized());

    EXPECT_FALSE(sys.getDevices().empty());
    EXPECT_FALSE(sys.getJobs().empty());
    EXPECT_FALSE(sys.getCompensations().empty());

    EXPECT_TRUE(FileIsEmpty("tests/inputTests/SingleDeviceOutput.txt"));
}

// Tests the input of a singular device
TEST_F(PrinterInputTest, SingleDevice) {
    ASSERT_TRUE(DirectoryExists("tests/inputTests"));
    //if directory doesn't exist then no need in proceeding with the test

    ofstream myfile;
    SuccessEnum importResult;

    myfile.open("tests/inputTests/SingleDeviceOutput.txt");
    importResult = SystemImporter::importSystem("tests/inputTests/SingleDevice.xml", myfile, sys);
    myfile.close();

    EXPECT_TRUE(importResult == Success);

    EXPECT_TRUE(sys.properlyInitialized());

    EXPECT_FALSE(sys.getDevices().empty());
    EXPECT_TRUE(sys.getJobs().empty());
    EXPECT_TRUE(sys.getCompensations().empty());

    EXPECT_TRUE(FileIsEmpty("tests/inputTests/SingleDeviceOutput.txt"));
}

// Tests the input of a singular job
TEST_F(PrinterInputTest, SingleJob) {
    ASSERT_TRUE(DirectoryExists("tests/inputTests"));
    //if directory doesn't exist then no need in proceeding with the test

    ofstream myfile;
    SuccessEnum importResult;

    myfile.open("tests/inputTests/SingleJobOutput.txt");
    importResult = SystemImporter::importSystem("tests/inputTests/SingleJob.xml", myfile, sys);
    myfile.close();

    EXPECT_TRUE(importResult == Success);

    EXPECT_TRUE(sys.properlyInitialized());

    EXPECT_TRUE(sys.getDevices().empty());
    EXPECT_FALSE(sys.getJobs().empty());
    EXPECT_TRUE(sys.getCompensations().empty());

    EXPECT_TRUE(FileIsEmpty("tests/inputTests/SingleJobOutput.txt"));
}

// Tests the input of a singular device
TEST_F(PrinterInputTest, SingleCompensation) {
    ASSERT_TRUE(DirectoryExists("tests/inputTests"));
    //if directory doesn't exist then no need in proceeding with the test

    ofstream myfile;
    SuccessEnum importResult;

    myfile.open("tests/inputTests/SingleCompensationOutput.txt");
    importResult = SystemImporter::importSystem("tests/inputTests/SingleCompensation.xml", myfile, sys);
    myfile.close();

    EXPECT_TRUE(importResult == Success);

    EXPECT_TRUE(sys.properlyInitialized());

    EXPECT_TRUE(sys.getDevices().empty());
    EXPECT_TRUE(sys.getJobs().empty());
    EXPECT_FALSE(sys.getCompensations().empty());

    EXPECT_TRUE(FileIsEmpty("tests/inputTests/SingleDeviceOutput.txt"));
}

// Tests the input of multiple devices (Also tests for all three device types)
TEST_F(PrinterInputTest, MultipleDevices) {
    ASSERT_TRUE(DirectoryExists("tests/inputTests"));
    //if directory doesn't exist then no need in proceeding with the test

    ofstream myfile;
    SuccessEnum importResult;

    myfile.open("tests/inputTests/MultipleDevicesOutput.txt");
    importResult = SystemImporter::importSystem("tests/inputTests/MultipleDevices.xml", myfile, sys);
    myfile.close();

    EXPECT_TRUE(importResult == Success);

    EXPECT_TRUE(sys.properlyInitialized());

    EXPECT_FALSE(sys.getDevices().empty());
    EXPECT_TRUE(sys.getJobs().empty());
    EXPECT_TRUE(sys.getCompensations().empty());

    EXPECT_TRUE(FileIsEmpty("tests/inputTests/MultipleDevicesOutput.txt"));
}

// Tests the input of multiple jobs (Also tests for all three job types)
TEST_F(PrinterInputTest, MultipleJobs) {
    ASSERT_TRUE(DirectoryExists("tests/inputTests"));
    //if directory doesn't exist then no need in proceeding with the test

    ofstream myfile;
    SuccessEnum importResult;

    myfile.open("tests/inputTests/MultipleJobsOutput.txt");
    importResult = SystemImporter::importSystem("tests/inputTests/MultipleJobs.xml", myfile, sys);
    myfile.close();

    EXPECT_TRUE(importResult == Success);

    EXPECT_TRUE(sys.properlyInitialized());

    EXPECT_TRUE(sys.getDevices().empty());
    EXPECT_FALSE(sys.getJobs().empty());
    EXPECT_TRUE(sys.getCompensations().empty());

    EXPECT_TRUE(FileIsEmpty("tests/inputTests/MultipleJobsOutput.txt"));
}

// Tests the input of multiple compensations
TEST_F(PrinterInputTest, MultipleCompensations) {
    ASSERT_TRUE(DirectoryExists("tests/inputTests"));
    //if directory doesn't exist then no need in proceeding with the test

    ofstream myfile;
    SuccessEnum importResult;

    myfile.open("tests/inputTests/MultipleCompensationsOutput.txt");
    importResult = SystemImporter::importSystem("tests/inputTests/MultipleCompensations.xml", myfile, sys);
    myfile.close();

    EXPECT_TRUE(importResult == Success);

    EXPECT_TRUE(sys.properlyInitialized());

    EXPECT_TRUE(sys.getDevices().empty());
    EXPECT_TRUE(sys.getJobs().empty());
    EXPECT_FALSE(sys.getCompensations().empty());

    EXPECT_TRUE(FileIsEmpty("tests/inputTests/MultipleCompensations.txt"));
}

// Use Case 1.4: Reading printing costs
TEST_F(PrinterInputTest, ReadingPrintingCosts) {
    ASSERT_TRUE(DirectoryExists("tests/inputTests"));
    //if directory doesn't exist then no need in proceeding with the test

    ofstream myfile;
    SuccessEnum importResult;

    myfile.open("tests/inputTests/ReadingPrintingCostsOutput.txt");
    importResult = SystemImporter::importSystem("tests/inputTests/ReadingPrintingCosts.xml", myfile, sys);
    myfile.close();

    EXPECT_TRUE(importResult == Success);

    int cost = sys.getDevices().front()->getCosts();
    EXPECT_EQ(cost, 20);

    EXPECT_TRUE(FileIsEmpty("tests/inputTests/ReadingPrintingCostsOutput.txt"));
}


TEST_F(PrinterInputTest, XMLSyntaxErrorALL) {
    ASSERT_TRUE(DirectoryExists("tests/inputTests"));
    //if directory doesn't exist then no need in proceeding with the test

    ofstream myfile;
    SuccessEnum importResult;

    int fileCounter = 1;
    string fileName = "tests/inputTests/XMLSyntaxError" + to_string(fileCounter) + ".xml";
    string errorfileName;

    while (FileExists (fileName)) {
        myfile.open("tests/inputTests/XMLSyntaxErrorOutput.txt");
        importResult = SystemImporter::importSystem(fileName.c_str(), myfile, sys);
        myfile.close();

        EXPECT_TRUE(importResult == ImportAborted);

        errorfileName = "tests/inputTests/XMLSyntaxError" + to_string(fileCounter) + ".txt";
        EXPECT_TRUE(FileCompare("tests/inputTests/XMLSyntaxErrorOutput.txt", errorfileName));

        fileCounter = fileCounter + 1;
        fileName = "tests/inputTests/XMLSyntaxError" + to_string(fileCounter) + ".xml";
    }

    EXPECT_TRUE(fileCounter == 5);
}

// The opening tag is missing a '>'
TEST_F(PrinterInputTest, XMLSyntaxError1) {
    ASSERT_TRUE(DirectoryExists("tests/inputTests"));
    //if directory doesn't exist then no need in proceeding with the test

    ofstream myfile;
    SuccessEnum importResult;

    myfile.open("tests/inputTests/XMLSyntaxErrorOutput.txt");
    importResult = SystemImporter::importSystem("tests/inputTests/XMLSyntaxError1.xml", myfile, sys);
    myfile.close();

    EXPECT_TRUE(importResult == ImportAborted);

    EXPECT_TRUE(FileCompare("tests/inputTests/XMLSyntaxErrorOutput.txt", "tests/inputTests/XMLSyntaxError1.txt"));
}

// The closing tag is missing a '/'
TEST_F(PrinterInputTest, XMLSyntaxError2) {
    ASSERT_TRUE(DirectoryExists("tests/inputTests"));
    //if directory doesn't exist then no need in proceeding with the test

    ofstream myfile;
    SuccessEnum importResult;

    myfile.open("tests/inputTests/XMLSyntaxErrorOutput.txt");
    importResult = SystemImporter::importSystem("tests/inputTests/XMLSyntaxError2.xml", myfile, sys);
    myfile.close();

    EXPECT_TRUE(importResult == ImportAborted);

    EXPECT_TRUE(FileCompare("tests/inputTests/XMLSyntaxErrorOutput.txt", "tests/inputTests/XMLSyntaxError2.txt"));
}

// The opening tag is starting with a '/'
TEST_F(PrinterInputTest, XMLSyntaxError3) {
    ASSERT_TRUE(DirectoryExists("tests/inputTests"));
    //if directory doesn't exist then no need in proceeding with the test

    ofstream myfile;
    SuccessEnum importResult;

    myfile.open("tests/inputTests/XMLSyntaxErrorOutput.txt");
    importResult = SystemImporter::importSystem("tests/inputTests/XMLSyntaxError3.xml", myfile, sys);
    myfile.close();

    EXPECT_TRUE(importResult == ImportAborted);

    EXPECT_TRUE(FileCompare("tests/inputTests/XMLSyntaxErrorOutput.txt", "tests/inputTests/XMLSyntaxError3.txt"));
}

// The opening tag and closing tag do not match
TEST_F(PrinterInputTest, XMLSyntaxError4) {
    ASSERT_TRUE(DirectoryExists("tests/inputTests"));
    //if directory doesn't exist then no need in proceeding with the test

    ofstream myfile;
    SuccessEnum importResult;

    myfile.open("tests/inputTests/XMLSyntaxErrorOutput.txt");
    importResult = SystemImporter::importSystem("tests/inputTests/XMLSyntaxError4.xml", myfile, sys);
    myfile.close();

    EXPECT_TRUE(importResult == ImportAborted);

    EXPECT_TRUE(FileCompare("tests/inputTests/XMLSyntaxErrorOutput.txt", "tests/inputTests/XMLSyntaxError4.txt"));
}



// Negative Emission value
TEST_F(PrinterInputTest, InvalidInput1) {
    ASSERT_TRUE(DirectoryExists("tests/inputTests"));
    //if directory doesn't exist then no need in proceeding with the test

    ofstream myfile;

    myfile.open("tests/inputTests/InvalidInputOutput.txt");

    EXPECT_DEATH(SystemImporter::importSystem("tests/inputTests/InvalidInput1.xml", myfile, sys),
                 "Emissions value must be greater or equal than 0");

    myfile.close();
}

// Negative Speed value
TEST_F(PrinterInputTest, InvalidInput2) {
    ASSERT_TRUE(DirectoryExists("tests/inputTests"));
    //if directory doesn't exist then no need in proceeding with the test

    ofstream myfile;

    myfile.open("tests/inputTests/InvalidInputOutput.txt");

    EXPECT_DEATH(SystemImporter::importSystem("tests/inputTests/InvalidInput2.xml", myfile, sys),
                 "Speed value must be greater or equal than 0");

    myfile.close();
}

// Negative Cost value
TEST_F(PrinterInputTest, InvalidInput3) {
    ASSERT_TRUE(DirectoryExists("tests/inputTests"));
    //if directory doesn't exist then no need in proceeding with the test

    ofstream myfile;

    myfile.open("tests/inputTests/InvalidInputOutput.txt");

    EXPECT_DEATH(SystemImporter::importSystem("tests/inputTests/InvalidInput3.xml", myfile, sys),
                 "Cost value must be greater or equal than 0");

    myfile.close();
}

// Negative Job number
TEST_F(PrinterInputTest, InvalidInput4) {
    ASSERT_TRUE(DirectoryExists("tests/inputTests"));
    //if directory doesn't exist then no need in proceeding with the test

    ofstream myfile;

    myfile.open("tests/inputTests/InvalidInputOutput.txt");

    EXPECT_DEATH(SystemImporter::importSystem("tests/inputTests/InvalidInput4.xml", myfile, sys),
                 "Job id number must be a positive integer");

    myfile.close();
}

// Negative page count
TEST_F(PrinterInputTest, InvalidInput5) {
    ASSERT_TRUE(DirectoryExists("tests/inputTests"));
    //if directory doesn't exist then no need in proceeding with the test

    ofstream myfile;

    myfile.open("tests/inputTests/InvalidInputOutput.txt");

    EXPECT_DEATH(SystemImporter::importSystem("tests/inputTests/InvalidInput5.xml", myfile, sys),
                 "Page count must be a positive integer");

    myfile.close();
}

// Negative Compensation number (job)
TEST_F(PrinterInputTest, InvalidInput6) {
    ASSERT_TRUE(DirectoryExists("tests/inputTests"));
    //if directory doesn't exist then no need in proceeding with the test

    ofstream myfile;

    myfile.open("tests/inputTests/InvalidInputOutput.txt");

    EXPECT_DEATH(SystemImporter::importSystem("tests/inputTests/InvalidInput6.xml", myfile, sys),
                 "Compensation number must be a positive integer");

    myfile.close();
}

// Negative Compensation number (Compensation)
TEST_F(PrinterInputTest, InvalidInput7) {
    ASSERT_TRUE(DirectoryExists("tests/inputTests"));
    //if directory doesn't exist then no need in proceeding with the test

    ofstream myfile;

    myfile.open("tests/inputTests/InvalidInputOutput.txt");

    EXPECT_DEATH(SystemImporter::importSystem("tests/inputTests/InvalidInput7.xml", myfile, sys),
                 "Compensation number must be a positive integer");

    myfile.close();
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
