#include <gtest/gtest.h>

#include <QSignalSpy>

#include "mission.h"

using namespace md::domain;

class MissionTest : public ::testing::Test
{
};

TEST_F(MissionTest, testMissionComplete)
{
    Mission mission("Type", "Name");
    QSignalSpy spy(&mission, &Mission::completeChanged);

    EXPECT_TRUE(mission.isComplete());
    EXPECT_EQ(spy.count(), 0);

    mission.setTotal(100);
    EXPECT_FALSE(mission.isComplete());
    EXPECT_EQ(spy.count(), 1);

    mission.setProgress(50);
    EXPECT_FALSE(mission.isComplete());
    EXPECT_EQ(spy.count(), 1);

    mission.setProgress(100);
    EXPECT_TRUE(mission.isComplete());
    EXPECT_EQ(spy.count(), 2);
}
