#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <QSignalSpy>

#include "missions_service.h"

using namespace md::domain;

class MissionFactoryMock : public IMissionFactory
{
public:
    MOCK_METHOD(Mission*, createMission, (), (override));
};

class MissionServiceTest : public ::testing::Test
{
public:
    MissionServiceTest()
    {
    }

    MissionsService service;
};

TEST_F(MissionServiceTest, testCreateMissionWithNoType)
{
    QSignalSpy addSpy(&service, &MissionsService::missionAdded);
    QSignalSpy erroredSpy(&service, &MissionsService::errored);

    service.createMission("invalid type");

    EXPECT_TRUE(service.missions().isEmpty());
    EXPECT_EQ(addSpy.count(), 0);
    EXPECT_EQ(erroredSpy.count(), 1);
}

TEST_F(MissionServiceTest, testAddTypeAndCreateMission)
{
    QSignalSpy addSpy(&service, &MissionsService::missionAdded);
    QSignalSpy removeSpy(&service, &MissionsService::missionRemoved);
    QSignalSpy erroredSpy(&service, &MissionsService::errored);

    MissionFactoryMock mock;
    service.registerMissionType("test type", &mock);

    Mission* mission = new Mission("type", "Test Mission");
    EXPECT_CALL(mock, createMission()).WillOnce(::testing::Return(mission));

    service.createMission("test type");

    EXPECT_EQ(service.missions().count(), 1);
    EXPECT_TRUE(service.missions().contains(mission));
    EXPECT_EQ(mission->parent(), &service);
    EXPECT_EQ(addSpy.count(), 1);
    EXPECT_EQ(erroredSpy.count(), 0);

    service.removeMission(mission);

    EXPECT_EQ(service.missions().count(), 0);
    EXPECT_FALSE(service.missions().contains(mission));
    EXPECT_EQ(removeSpy.count(), 1);
}
