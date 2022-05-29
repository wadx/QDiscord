
// Copyright(c) 2022 by wad(wad@inbox.lv)

#include "stdafx.h"
#include "QDiscordStageInstance.h"


QSharedPointer<QDiscordStageInstance> QDiscordStageInstance::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordStageInstance> out(new QDiscordStageInstance());
	out->deserialize(object);
	return out;
}


QDiscordStageInstance::QDiscordStageInstance(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordStageInstance::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordStageInstance::serialize() const
{
	return serializeJson();
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QDiscordStageInstance::PrivacyLevel& value, const QString& name)
{
	switch (action.data()[name].toInt(-1))
	{
	case 0:
		value = QDiscordStageInstance::PrivacyLevel::PUBLIC;
		break;
	case 1:
		value = QDiscordStageInstance::PrivacyLevel::GUILD_ONLY;
		break;
	default:
		value = QDiscordStageInstance::PrivacyLevel::Unknown;
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QDiscordStageInstance::PrivacyLevel& value, const QString& name)
{
	action.data().insert(name, static_cast<int>(value));
}


