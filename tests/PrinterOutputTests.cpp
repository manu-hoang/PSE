//
// Created by jeremi on 7/03/24.
//
#include <iostream>
#include <gtest/gtest.h>
#include "../src/System.h"
#include "../src/PrinterInput.cpp"
#include <fstream>


class PrinterOutputTest: public ::testing::Test {
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

// Tests the compare files
TEST_F(PrinterOutputTest, FileCompare) {
    ASSERT_TRUE(DirectoryExists("./tests"));
    ASSERT_TRUE(DirectoryExists("./src"));

    ofstream myfile;
    myfile.open("./src/output.txt");
    myfile.close();
    myfile.open("tests/outputTest.txt");
    myfile.close();

    //compare 2 empty files
// *** Beware: the following does not work with older versions of libstdc++
// *** It doesn't work with gcc version 4.0.1 (Apple Inc. build 5465)
// *** It does work with gcc version 4.2.1
    EXPECT_TRUE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
    EXPECT_TRUE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

    //compare an empty and a non-empty files
    myfile.open("testOutput/file1.txt");
    myfile << "xxx" << endl << "yyy";
    myfile.close();
    EXPECT_FALSE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
    EXPECT_FALSE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

    //compare two equal files
    myfile.open("testOutput/file2.txt");
    myfile << "xxx" << endl << "yyy";
    myfile.close();
    EXPECT_TRUE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
    EXPECT_TRUE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

    //compare 2 non-empty files which are off by a character in the middle
    myfile.open("testOutput/file2.txt");
    myfile << "xxx" << endl << "xyy";
    myfile.close();
    EXPECT_FALSE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
    EXPECT_FALSE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

    //compare 2 non-empty files where one is one character shorter than the other
    myfile.open("testOutput/file2.txt");
    myfile << "xxx" << endl << "yy";
    myfile.close();
    EXPECT_FALSE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
    EXPECT_FALSE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

    //compare existig against non existing file
    EXPECT_FALSE(
            FileCompare("testOutput/file1.txt", "testOutput/nonexisting.txt"));
    EXPECT_FALSE(
            FileCompare("testOutput/nonexisting.txt", "testOutput/file1.txt"));
}

// Tests the output of the "happy day" scenario
TEST_F(PrinterOutputTest, OutputHappyDay) {
    ASSERT_TRUE(DirectoryExists("testOutput"));
    //if directory doesn't exist then no need in proceeding with the test

    ofstream myfile;
    myfile.open("test.txt");
    while (ttt_.notDone()) {
        ttt_.doMove();
        ttt_.writeOn(myfile);
    };
    myfile.close();
    EXPECT_TRUE(
            FileCompare("testOutput/happyDayExpectedOut.txt", "testOutput/happyDayOut.txt"));
}
