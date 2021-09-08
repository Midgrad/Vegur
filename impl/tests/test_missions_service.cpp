#include <gtest/gtest.h>

#include <QSignalSpy>

#include "missions_service.h"

using namespace md::domain;

class MissionServiceTest : public ::testing::Test
{
public:
    MissionServiceTest()
    {
    }

    MissionsService service;
};

TEST_F(MissionServiceTest, testAddMission)
{
    QSignalSpy addSpy(&service, &MissionsService::missionAdded);

    auto mission = new Mission();
    service.addMission(mission);

    EXPECT_TRUE(service.missions().contains(mission));
    EXPECT_EQ(addSpy.count(), 1);
}

TEST_F(MissionServiceTest, testRemoveMission)
{
    Mission mission;
    service.addMission(&mission);

    QSignalSpy removeSpy(&service, &MissionsService::missionRemoved);

    service.removeMission(&mission);

    EXPECT_FALSE(service.missions().contains(&mission));
    EXPECT_EQ(removeSpy.count(), 1);
}
