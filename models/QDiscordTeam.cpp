
// Copyright(c) 2022 by wad(wad@inbox.lv)

#include "stdafx.h"
#include "QDiscordTeam.h"


QSharedPointer<QDiscordTeamMember> QDiscordTeamMember::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordTeamMember> out(new QDiscordTeamMember());
	out->deserialize(object);
	return out;
}


QDiscordTeamMember::QDiscordTeamMember(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordTeamMember::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordTeamMember::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordTeam> QDiscordTeam::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordTeam> out(new QDiscordTeam());
	out->deserialize(object);
	return out;
}


QDiscordTeam::QDiscordTeam(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordTeam::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordTeam::serialize() const
{
	return serializeJson();
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QDiscordTeamMember::MembershipState& value, const QString& name)
{
	switch (action.data()[name].toInt(-1))
	{
	case 1:
		value = QDiscordTeamMember::MembershipState::INVITED;
		break;
	case 2:
		value = QDiscordTeamMember::MembershipState::ACCEPTED;
		break;
	default:
		value = QDiscordTeamMember::MembershipState::Unknown;
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QDiscordTeamMember::MembershipState& value, const QString& name)
{
	action.data().insert(name, static_cast<int>(value));
}


