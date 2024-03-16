//
// Created by jeremi on 7/03/24.
//
#include <iostream>
#include <gtest/gtest.h>
#include "../src/System.h"
#include <fstream>
#include "../src/PrinterInput.h"
#include "../src/PrinterOutput.h"


class PrinterIn_OutputTest: public ::testing::Test {
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

bool DirectoryExists(const std::string dirname) {
    struct stat st;
    return stat(dirname.c_str(), &st) == 0;
}

bool FileCompare(const std::string leftFileName, const std::string rightFileName) {
    ifstream leftFile, rightFile;
    char leftRead, rightRead;
    bool result;

    // Open the two files.
    leftFile.open(leftFileName.c_str());
    if (!leftFile.is_open()) {
        return false;
    };
    rightFile.open(rightFileName.c_str());
    if (!rightFile.is_open()) {
        leftFile.close();
        return false;
    };

    result = true; // files exist and are open; assume equality unless a counterexamples shows up.
    while (result && leftFile.good() && rightFile.good()) {
        leftFile.get(leftRead);
        rightFile.get(rightRead);
        result = (leftRead == rightRead);
    };
    if (result) {
        // last read was still equal; are we at the end of both files ?
        result = (!leftFile.good()) && (!rightFile.good());
    };

    leftFile.close();
    rightFile.close();
    return result;
}


// Tests the input of the "happy day" scenario
TEST_F(PrinterIn_OutputTest, InputHappyDay) {
    ASSERT_TRUE(DirectoryExists("tests/inputTests"));
    //if directory doesn't exist then no need in proceeding with the test

    System system;

    load("./xml_files/Use_Case_1.1_Reading_printers_and_jobs.xml", system);

    EXPECT_TRUE(
            FileCompare("tests/inputTests/happy_day.txt", "in_output/inputError.txt"));
}

// Tests the error code given by an unrecognised element
TEST_F(PrinterIn_OutputTest, UnrecognisedElement) {
    ASSERT_TRUE(DirectoryExists("tests/inputTests"));
    //if directory doesn't exist then no need in proceeding with the test

    System system;

    load("./xml_files/Unrecognised_Element.xml", system);

    EXPECT_TRUE(
            FileCompare("tests/inputTests/unrecognised_element.txt", "in_output/inputError.txt"));

    // Device should still get added as the unrecognised doesnt impact it
    EXPECT_TRUE(system.getDevices().size() == 1);

    // Job should still get added as the unrecognised doesnt impact it
    EXPECT_TRUE(system.getJobs().size() == 1);
}

// Tests the error code given by an incorrect value
TEST_F(PrinterIn_OutputTest, IncorrectValue) {
    ASSERT_TRUE(DirectoryExists("tests/inputTests"));
    //if directory doesn't exist then no need in proceeding with the test

    System system;

    load("./xml_files/Incorrect_Value.xml", system);

    EXPECT_TRUE(
            FileCompare("tests/inputTests/incorrect_value.txt", "in_output/inputError.txt"));

    // Device has an incorrect value, so should not get added
    EXPECT_TRUE(system.getDevices().empty());

    // Job has an incorrect value, so should not get added
    EXPECT_TRUE(system.getJobs().empty());
}

// Tests the error code for a doomsday scenario
TEST_F(PrinterIn_OutputTest, Doomsday) {
    ASSERT_TRUE(DirectoryExists("tests/inputTests"));
    //if directory doesn't exist then no need in proceeding with the test

    System system;

    load("./xml_files/Doomsday.xml", system);

    EXPECT_TRUE(
            FileCompare("tests/inputTests/doomsday.txt", "in_output/inputError.txt"));

    // Device has an incorrect value, so should not get added
    EXPECT_TRUE(system.getDevices().empty());

    // Job has an incorrect value, so should not get added
    EXPECT_TRUE(system.getJobs().empty());
}

// Tests the output of the "happy day" scenario
TEST_F(PrinterIn_OutputTest, HappyDayOutput) {
    ASSERT_TRUE(DirectoryExists("./tests/outputTests"));
    ASSERT_TRUE(DirectoryExists("./in_output"));
    //if directory doesn't exist then no need in proceeding with the test

    System system1;

    load("./xml_files/Use_Case_1.1_Reading_printers_and_jobs.xml", system1);

    ofstream output("./in_output/output.txt");
    writeDeviceInfo(system1);

    EXPECT_TRUE(
            FileCompare("./tests/outputTests/happy_day_output.txt", "./in_output/output.txt")
            );
}

// Tests the output of the "incorrect value" scenario
TEST_F(PrinterIn_OutputTest, IncorrectValueOutput) {
    ASSERT_TRUE(DirectoryExists("./tests/outputTests"));
    ASSERT_TRUE(DirectoryExists("./in_output"));
    //if directory doesn't exist then no need in proceeding with the test

    System system1;

    load("./xml_files/Incorrect_Value.xml", system1);

    ofstream output("./in_output/output.txt");
    writeDeviceInfo(system1);

    EXPECT_TRUE(
            FileCompare("./tests/outputTests/incorrect_value_output.txt", "./in_output/output.txt")
    );
}

// Tests the output of the "unrecognised element" scenario
TEST_F(PrinterIn_OutputTest, UnrecognisedElementOutput) {
    ASSERT_TRUE(DirectoryExists("./tests/outputTests"));
    ASSERT_TRUE(DirectoryExists("./in_output"));
    //if directory doesn't exist then no need in proceeding with the test

    System system1;

    load("./xml_files/Unrecognised_Element.xml", system1);

    ofstream output("./in_output/output.txt");
    writeDeviceInfo(system1);

    EXPECT_TRUE(
            FileCompare("./tests/outputTests/unrecognised_element_output.txt", "./in_output/output.txt")
    );
}

// Tests the output of the "doomsday" scenario
TEST_F(PrinterIn_OutputTest, DoomsdayOutput) {
    ASSERT_TRUE(DirectoryExists("./tests/outputTests"));
    ASSERT_TRUE(DirectoryExists("./in_output"));
    //if directory doesn't exist then no need in proceeding with the test

    System system1;

    load("./xml_files/Doomsday.xml", system1);

    ofstream output("./in_output/output.txt");
    writeDeviceInfo(system1);

    EXPECT_TRUE(
            FileCompare("./tests/outputTests/doomsday_output.txt", "./in_output/output.txt")
    );
}

TEST_F(PrinterIn_OutputTest, ConsoleOutput) {
    ASSERT_TRUE(DirectoryExists("./tests/outputTests"));
    ASSERT_TRUE(DirectoryExists("./in_output"));
    //if directory doesn't exist then no need in proceeding with the test

    System system1;

    load("./xml_files/Use_Case_1.1_Reading_printers_and_jobs.xml", system1);

    ofstream output("./in_output/output.txt");
    writeDeviceInfo(system1);

    system1.automatic_run(150);


    EXPECT_TRUE(
            FileCompare("./tests/outputTests/console_test_output.txt", "./in_output/console_output.txt")
    );
}


TEST_F(PrinterIn_OutputTest, ConsoleDoomsdayOutput) {
    ASSERT_TRUE(DirectoryExists("./tests/outputTests"));
    ASSERT_TRUE(DirectoryExists("./in_output"));
    //if directory doesn't exist then no need in proceeding with the test

    System system1;

    load("./xml_files/Doomsday.xml", system1);

    ofstream output("./in_output/output.txt");
    writeDeviceInfo(system1);

    system1.automatic_run(150);


    EXPECT_TRUE(
            FileCompare("./tests/outputTests/console_doomsday_output.txt", "./in_output/console_output.txt")
    );
}


TEST_F(PrinterIn_OutputTest, ConsoleIncorrectValueOutput) {
    ASSERT_TRUE(DirectoryExists("./tests/outputTests"));
    ASSERT_TRUE(DirectoryExists("./in_output"));
    //if directory doesn't exist then no need in proceeding with the test

    System system1;

    load("./xml_files/Incorrect_Value.xml", system1);

    ofstream output("./in_output/output.txt");
    writeDeviceInfo(system1);

    system1.automatic_run(150);


    EXPECT_TRUE(
            FileCompare("./tests/outputTests/console_incorrect_value_output.txt", "./in_output/console_output.txt")
    );
}


TEST_F(PrinterIn_OutputTest, ConsoleUnrecognisedElementOutput) {
    ASSERT_TRUE(DirectoryExists("./tests/outputTests"));
    ASSERT_TRUE(DirectoryExists("./in_output"));
    //if directory doesn't exist then no need in proceeding with the test

    System system1;

    load("./xml_files/Unrecognised_Element.xml", system1);

    ofstream output("./in_output/output.txt");
    writeDeviceInfo(system1);

    system1.automatic_run(150);


    EXPECT_TRUE(
            FileCompare("./tests/outputTests/console_unrecognised_element_output.txt", "./in_output/console_output.txt")
    );
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
