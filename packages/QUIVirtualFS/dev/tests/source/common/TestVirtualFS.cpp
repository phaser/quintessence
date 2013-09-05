// Copyright (C) 2012 Cristian Bidea
#include <gtest/gtest.h>
#include <qui/VirtualFS.h>
#include <string>

class VirtualFSTest : public testing::Test
{
 protected:
};

TEST_F(VirtualFSTest, TestRelativePaths)  // NOLINT
{
    qui::VirtualFS fs;
    std::string rp = fs.getRelativePath("passwd", false);
    EXPECT_FALSE(rp.find("/etc/passwd") != std::string::npos);

    fs.addRelativePath("/etc");
    rp = fs.getRelativePath("passwd", false);
    EXPECT_TRUE(rp.find("DIR##/etc/passwd") != std::string::npos);

    fs.removeRelativePath("/etc");
    rp = fs.getRelativePath("passwd", false);
    EXPECT_FALSE(rp.find("DIR##/etc/passwd") != std::string::npos);
}

TEST_F(VirtualFSTest, TestfileExists)  // NOLINT
{
    qui::VirtualFS fs;
    EXPECT_TRUE(fs.fileExists("/etc/passwd"));
    EXPECT_FALSE(fs.fileExists("some_shit_that_for_sure_doesn-t_exists"));
}

