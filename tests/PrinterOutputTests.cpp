#include <gtest/gtest.h>
#include <fstream>
#include "TestUtils.h"

#include "../src/System.h"


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


// Tests the compare files
TEST_F(PrinterOutputTest, FileCompare) {
    ASSERT_TRUE(DirectoryExists("tests/outputTests"));

    ofstream myfile;
    myfile.open("tests/outputTests/file1.txt");
    myfile.close();
    myfile.open("tests/outputTests/file2.txt");
    myfile.close();

    EXPECT_TRUE(FileExists("tests/outputTests/file1.txt"));
    EXPECT_TRUE(FileExists("tests/outputTests/file2.txt"));
    EXPECT_TRUE(FileIsEmpty("tests/outputTests/file1.txt"));
    EXPECT_TRUE(FileIsEmpty("tests/outputTests/file2.txt"));


    //compare 2 empty files
    // *** Beware: the following does not work with older versions of libstdc++
    // *** It doesn't work with gcc version 4.0.1 (Apple Inc. build 5465)
    // *** It does work with gcc version 4.2.1
    EXPECT_TRUE(FileCompare("tests/outputTests/file1.txt", "tests/outputTests/file2.txt"));
    EXPECT_TRUE(FileCompare("tests/outputTests/file2.txt", "tests/outputTests/file1.txt"));

    //compare an empty and a non-empty files
    myfile.open("tests/outputTests/file1.txt");
    myfile << "xxx" << endl << "yyy";
    myfile.close();
    EXPECT_TRUE(FileExists("tests/outputTests/file1.txt"));
    EXPECT_FALSE(FileIsEmpty("tests/outputTests/file1.txt"));
    EXPECT_FALSE(FileCompare("tests/outputTests/file1.txt", "tests/outputTests/file2.txt"));
    EXPECT_FALSE(FileCompare("tests/outputTests/file2.txt", "tests/outputTests/file1.txt"));

    //compare two equal files
    myfile.open("tests/outputTests/file2.txt");
    myfile << "xxx" << endl << "yyy";
    myfile.close();
    EXPECT_TRUE(FileExists("tests/outputTests/file2.txt"));
    EXPECT_FALSE(FileIsEmpty("tests/outputTests/file2.txt"));
    EXPECT_TRUE(FileCompare("tests/outputTests/file1.txt", "tests/outputTests/file2.txt"));
    EXPECT_TRUE(FileCompare("tests/outputTests/file2.txt", "tests/outputTests/file1.txt"));

    //compare 2 non-empty files which are off by a character in the middle
    myfile.open("tests/outputTests/file2.txt");
    myfile << "xxx" << endl << "xyy";
    myfile.close();
    EXPECT_FALSE(FileCompare("tests/outputTests/file1.txt", "tests/outputTests/file2.txt"));
    EXPECT_FALSE(FileCompare("tests/outputTests/file2.txt", "tests/outputTests/file1.txt"));

    //compare 2 non-empty files where one is one character shorter than the other
    myfile.open("tests/outputTests/file2.txt");
    myfile << "xxx" << endl << "yy";
    myfile.close();
    EXPECT_FALSE(FileCompare("tests/outputTests/file1.txt", "tests/outputTests/file2.txt"));
    EXPECT_FALSE(FileCompare("tests/outputTests/file2.txt", "tests/outputTests/file1.txt"));

    //compare existing against non existing file
    EXPECT_FALSE(
            FileCompare("tests/outputTests/file1.txt", "tests/outputTests/nonexisting.txt"));
    EXPECT_FALSE(
            FileCompare("tests/outputTests/nonexisting.txt", "tests/outputTests/file1.txt"));
}

TEST_F(PrinterOutputTest, OutputHappyDay) {
    ASSERT_TRUE(DirectoryExists("tests/outputTests"));
    //if directory doesn't exist then no need in proceeding with the test

    sys.automated_processing();

    ofstream myfile;
    myfile.open("testOutput/happyDayOut.txt");

/*    while (ttt_.notDone()) {
        ttt_.doMove();
        ttt_.writeOn(myfile);
    }*/

    myfile.close();
}