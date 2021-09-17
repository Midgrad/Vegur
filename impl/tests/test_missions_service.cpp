#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <QSignalSpy>

#include "missions_service.h"

using namespace ::testing;
using namespace md::domain;

class MissionFactoryMock : public IMissionFactory
{
public:
    MOCK_METHOD(Mission*, createMission, (const QString&), (override));
};

class JsonGatewayMock : public md::data_source::IJsonGateway
{
public:
    MOCK_METHOD(QVariantList, selectIds, (), (const, override));
    MOCK_METHOD(QList<QJsonObject>, readAll, (), (const, override));
    MOCK_METHOD(QJsonObject, read, (const QVariant&), (const, override));

    MOCK_METHOD(void, save, (const QVariant&, const QJsonObject&), (override));
    MOCK_METHOD(void, remove, (const QVariant&), (override));
};

class MissionServiceTest : public Test
{
public:
    MissionServiceTest() : service(new JsonGatewayMock())
    {
    }

    MissionsService service;
};

TEST_F(MissionServiceTest, testCreateMissionWithNoType)
{
    QSignalSpy addSpy(&service, &MissionsService::missionAdded);

    service.createMission("invalid type");

    EXPECT_TRUE(service.missions().isEmpty());
    EXPECT_EQ(addSpy.count(), 0);
}

TEST_F(MissionServiceTest, testAddTypeAndCreateMission)
{
    QSignalSpy addSpy(&service, &MissionsService::missionAdded);
    QSignalSpy removeSpy(&service, &MissionsService::missionRemoved);

    MissionFactoryMock mock;
    service.registerMissionType("test type", &mock);

    Mission* mission = new Mission("type", "test_mission_1", "Test Mission 1");
    EXPECT_CALL(mock, createMission(_)).WillOnce(::testing::Return(mission));

    service.createMission("test type");

    EXPECT_EQ(service.missions().count(), 1);
    EXPECT_TRUE(service.missions().contains(mission));
    EXPECT_EQ(mission->parent(), &service);
    EXPECT_EQ(addSpy.count(), 1);

    service.removeMission(mission);

    EXPECT_EQ(service.missions().count(), 0);
    EXPECT_FALSE(service.missions().contains(mission));
    EXPECT_EQ(removeSpy.count(), 1);
}
